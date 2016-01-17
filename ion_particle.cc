#include <iostream>
#include "particle.h"
#include "random_number.h"
#include "iedf_to_distribution.h"

#include "ion_particle.h"
using namespace std;

//==  入射エネルギーに対して etch yield を返す ==
//    yield の係数β = C(√E - √Eth): C = 0.77, Eth = 20.0 
//    *: 0.77 * sqrt(20.0) = 3.44354468534968

inline double yield_beta_oxy(double incident_energy)
{
  double  tmp ;
  tmp = 0.353 * (sqrt(incident_energy) - sqrt(Eth_SiO2)) ;

  if(tmp > 0.0)
    return tmp ;
  else 
    return 0.0 ;
}

inline double yield_beta_oxy(double incident_energy, double reflected_energy)
{
  double  tmp ;
  tmp = 0.353 *(sqrt(incident_energy - reflected_energy) - sqrt(Eth_SiO2));
   
  if(tmp > 0.0)
    return tmp ;
  else 
    return 0.0 ;
}

inline double yield_beta(double incident_energy, double reflected_energy)
{
  double  tmp ;
  tmp = 0.353 *(sqrt(incident_energy - reflected_energy) - sqrt(Eth_Si));
   
  if(tmp > 0.0)
    return tmp ;
  else 
    return 0.0 ;
}

//======================================

Ion_class::Ion_class() 
{
}

Ion_class::Ion_class(double mass_input,  int flag_boundary_input,
		     int n_adf_input ) 
  : Particle_class(mass_input, flag_boundary_input) 
{
  n_adf_array = n_adf_input ;

  angular_df           =  new double[n_adf_array] ;
  angle_array_degree   =  new double[n_adf_array] ;

  flag_contact    = false ;
  flag_desorb_Si  = false ;
  flag_reflection = false ;
  ctr_reflection  = 0 ;
  velocity_file.open(NULL);//== 散乱後の速度を記録 ==

  i_x_etch = 0; i_z_etch = 0 ;
  energy_etch = 0.0 ;
}

Ion_class::~Ion_class() 
{
  delete [] angular_df  ;
  delete [] angle_array_degree ;
  velocity_file.close();
}

//--==================================================
void Ion_class::inject_iadf(double v )
{
  flag_contact   = false ; 
  flag_desorb_Si = false ;

  double v_xx, v_yy, v_zz ;

  // randomized_distribution   (long int 乱数の種, int 作りだす乱数の数,
  //   double[] エネルギー  ,double[] 分布,
  //   -> 出力  double[] (元の乱数), double[] 得られた乱数) 
  
  // -- 動的確保！
  double *dummy_array_angle ;

  double *randomized_angle_array ;
  
  dummy_array_angle      = new double[1] ;
  randomized_angle_array = new double[1] ;

  randomized_distribution(RANDOM_NUMBER_SEED,
			   1 ,
			   angle_array_degree , 0.0,
			   angular_df, 
			   dummy_array_angle,
			   randomized_angle_array) ;

  //cout << "randomized_angle_array[0]: " << randomized_angle_array[0] << "\n";

  // X座標は乱数によって決定する
  pos_v.x = RAN0() * SYSTEM_WIDTH_X ; 
  pos_v.y = 0.0 ;
  pos_v.z = 0.0 ;
  
  // --- 入射角はこの時点で決定している(randomized_angle_array)
  // が、y 軸周りの回転角は乱数で作る 
  // 入射角ψ、回転角θとすると z = v cosψ, x = v sinψcosθ, y = v sinψsinθ
      
  // randomized_energy は eV の単位なので Q_ELEMENTAL をかけてVolt 単位にする

  pos_v.v_r     =  v ; // <--- Absolute velocity

  pos_v.v_theta =  2.0 * PI * RAN0() ; //0.0 ;// 
     
  pos_v.v_psi   = 
    PI * randomized_angle_array[0] / 180.0 ; // degree -> radへ換算 
  
  //----
  v_xx = pos_v.v_r * sin(pos_v.v_psi) * cos(pos_v.v_theta) ;//0.0 ;
  v_yy = pos_v.v_r * sin(pos_v.v_psi) * sin(pos_v.v_theta) ;
  v_zz = pos_v.v_r * cos(pos_v.v_psi) ;
 
  //incident angle
  pos_v.v_x = v_xx * cos(PI * INCIDENT_ANGLE /180.0) - v_zz * sin(PI * INCIDENT_ANGLE /180.0) ;
  pos_v.v_y = v_yy ;
  pos_v.v_z = v_xx * sin(PI * INCIDENT_ANGLE /180.0) + v_zz * cos(PI * INCIDENT_ANGLE /180.0) ;

   //cout << pos_v.v_x << "\t" << pos_v.v_y << "\t"
     //<< pos_v.v_z << "\n" ;

  delete [] dummy_array_angle ;
  delete [] randomized_angle_array ;

  //== エッチング用変数初期化 ==
  i_x_etch = 0; i_z_etch = 0 ;   energy_etch = 0.0 ;
  pos_v_etch = pos_v ; 

}// --- End of inject_ion


//==  
void Ion_class::record_desorption(Particle_location_velocity_struct pos_v_recorded,
				  int input_n_oxygen) 
{
  flag_desorb_Si  = true ;
  n_oxy_desorb_Si = input_n_oxygen ;

  position_at_desorption  = pos_v_recorded ;
}


//イオンの衝突によるエッチング処理
void Ion_class::
ion_enhanced_etch(class  Shape_trim_class *Shape_trim,
		  double incident_energy, double reflected_energy,
		  Particle_location_velocity_struct pos_v_recorded,
		  int i_x, int i_z ) 
{
  double tmp_beta = 0.0;
  
  if(Shape_trim->n_oxygen[i_x][i_z] >= 1 )
    {
		//(3rd paper)酸素が吸着することによる形状不安定を防ぐため
		//エッチング収率を分散させる。nearest-neighborのセルに含まれる酸素の数を合計し
		//6 で割ってcoverageΘとする。
		//収率は Y = Θ Y(SiO2) + (1 - Θ)Y(Si)
		if(FLAG_DISPERSE_OXIDATION == true)
		{
	      int ctr_oxygen = 0;
	      
	      if(i_x > 0  &&  i_x < N_CELL_X - 1 && i_z > 0  &&  i_z < N_CELL_Z - 1 )
	      ctr_oxygen = Shape_trim->n_oxygen[i_x][i_z] 
		  +          Shape_trim->n_oxygen[i_x + 1][i_z] + Shape_trim->n_oxygen[i_x - 1][i_z] 
		  +          Shape_trim->n_oxygen[i_x][i_z + 1] + Shape_trim->n_oxygen[i_x][i_z - 1] ;
	      
	      else
	      ctr_oxygen = Shape_trim->n_oxygen[i_x][i_z] ;
	      
	      tmp_beta = yield_beta_oxy(incident_energy, reflected_energy) * etch_yield_disperse_oxidation
	      (Shape_trim->get_incident_angle(i_x, i_z, pos_v_recorded.v_x, pos_v_recorded.v_z ), ctr_oxygen );
	    }
	    
	    //DEFAULT:(2nd paper)
	    else
	    {
			//== 酸素の数による区別 ==
			if( Shape_trim->n_oxygen[i_x][i_z] == 1 )
				tmp_beta = SELECTIVITY_SiO * yield_beta_oxy(incident_energy) 
				* etch_yield_angle(Shape_trim->get_incident_angle(i_x, i_z, pos_v_recorded.v_x, pos_v_recorded.v_z ) ) ;
			else if( Shape_trim->n_oxygen[i_x][i_z] == 2 )
				tmp_beta = SELECTIVITY_SiO2 * yield_beta_oxy(incident_energy) 
				* etch_yield_angle(Shape_trim->get_incident_angle(i_x, i_z, pos_v_recorded.v_x, pos_v_recorded.v_z ) ) ;
	    }
    }
  
  //酸素が含まれない場合
  else
    {
      tmp_beta = yield_beta(incident_energy, reflected_energy);
    }
  
  
  if(RAN0() < tmp_beta / YIELD_MAX) //仮想粒子を確率的に扱う
    {
      if (FLAG_ION_REACTIVE_ETCH == true){
        Shape_trim->desorb_Si(i_x, i_z);
        record_desorption(pos_v_recorded, Shape_trim->n_oxygen[i_x][i_z]);
      }
      else {
        if(Shape_trim->shape_matrix[i_x][i_z] == SHAPE_Si && Shape_trim->n_Clbond[i_x][i_z] + 2 * Shape_trim->n_oxygen[i_x][i_z] >= NMAX_ADATOM){
          Shape_trim->cntr_desorbed_Si++ ;
        }
        record_desorption(pos_v_recorded, Shape_trim->n_oxygen[i_x][i_z]);    
      }
    }
}



//前方散乱の衝突過程
bool Ion_class::
impact_scattering(class  Shape_trim_class *Shape_trim,
		  bool  flag_mask_erosion) 
{
  int i_x, i_z, i_x_particle, i_z_particle ;
  double p_impact_parameter ;
  double incident_energy ;
  incident_energy = mass * pos_v.v_r * pos_v.v_r /(2.0 * Q_ELEMENTAL) ;
  
  
  //当セルがSi or Hardmask
  if(Shape_trim->put_shape_matrix(pos_v.x, pos_v.z, &i_x, &i_z) != SHAPE_SPACE )
    {
      //エネルギーがある値を下回っていたら stop
      if(incident_energy <= ENERGY_ION_STOPPING)
	{
	  //stopした時点で事後的にエッチングの処理を行う
	  ion_enhanced_etch(Shape_trim, energy_etch, 0.0, pos_v_etch, i_x_etch, i_z_etch) ;
	  return true ;
	}
      if(flag_contact == false)
	{
	  record_etch_position(i_x, i_z, incident_energy);
	  flag_contact = true ; 
	}
      
      // impact parameter は乱数Xで決定：
      // p = (L/2)√X  where  L は原子間距離
      p_impact_parameter = (L_INTER_ATOMIC / 2.0) * sqrt(RAN0());
      
      // -- collision --
      //collision_with_solid_atom( p_impact_parameter );
      collision_accurate3D( (i_x + 0.5) * L_INTER_ATOMIC,
			    0.5         * L_INTER_ATOMIC,
			    (i_z + 0.5) * L_INTER_ATOMIC,
			    &incident_energy );
    }
  
  //隣接セルが Si の場合
  else if( Shape_trim->find_solid_nearest_neighbor
	   (pos_v.x,    pos_v.z ,
	    pos_v.v_x,  pos_v.v_z ,
	    &i_x, &i_z, &i_x_particle, &i_z_particle) == SHAPE_Si )
    {
      if(flag_contact == false)
	  {
	   record_etch_position(i_x, i_z, incident_energy);
	   flag_contact = true ; 
	  }
      // -- collision （周期境界条件を考慮）
      if(i_x_particle == 0 && i_x == N_CELL_X - 1)
	collision_accurate3D( (- 0.5)     * L_INTER_ATOMIC,
			      0.5         * L_INTER_ATOMIC,
			      (i_z + 0.5) * L_INTER_ATOMIC,
	 		    &incident_energy );
      else if(i_x_particle == N_CELL_X - 1 && i_x == 0)
	collision_accurate3D( (N_CELL_X + 0.5) * L_INTER_ATOMIC,
			      0.5         * L_INTER_ATOMIC,
			      (i_z + 0.5) * L_INTER_ATOMIC,
			    &incident_energy );
      else
	collision_accurate3D( (i_x + 0.5) * L_INTER_ATOMIC,
			      0.5         * L_INTER_ATOMIC,
			      (i_z + 0.5) * L_INTER_ATOMIC,
			      &incident_energy );
    }
  
  //隣接セルが hardmask の場合
  else if(Shape_trim->find_solid_nearest_neighbor
	  (pos_v.x,    pos_v.z ,
	   pos_v.v_x,  pos_v.v_z ,
	   &i_x, &i_z, &i_x_particle, &i_z_particle) == HARD_MASK )
    {
       if(flag_contact == false)
       {
		if(flag_mask_erosion == true)
		hardmask_sputter(Shape_trim, incident_energy, 0.0, pos_v, i_x, i_z); //<-added
		flag_contact = true ; 
	   }
       // -- collision （周期境界条件を考慮）
       if(i_x_particle == 0 && i_x == N_CELL_X - 1)
	 collision_accurate3D( (- 0.5)     * L_INTER_ATOMIC,
			       0.5         * L_INTER_ATOMIC,
			       (i_z + 0.5) * L_INTER_ATOMIC,
			       &incident_energy );
       else if(i_x_particle == N_CELL_X - 1 && i_x == 0)
	 collision_accurate3D( (N_CELL_X + 0.5) * L_INTER_ATOMIC,
			       0.5         * L_INTER_ATOMIC,
			       (i_z + 0.5) * L_INTER_ATOMIC,
			        &incident_energy );
       else
	 collision_accurate3D( (i_x + 0.5) * L_INTER_ATOMIC,
			       0.5         * L_INTER_ATOMIC,
			       (i_z + 0.5) * L_INTER_ATOMIC,
			       &incident_energy );
    }
  
  //隣接セルが Balk の場合
  else if( Shape_trim->find_solid_nearest_neighbor
	   (pos_v.x,    pos_v.z ,
	    pos_v.v_x,  pos_v.v_z ,
	    &i_x, &i_z, &i_x_particle, &i_z_particle) == SHAPE_SPACE )
    {
	  //イオンが表面で反射後気相に戻る場合
      if(flag_contact    == true) //固体部分に接触状態 -> detachしたことを意味する
      {
		flag_reflection = true ; //前方散乱が起こったことを記録
		
		//イオンがreflectionを起こした場合も事後的にエッチング処理
		ion_enhanced_etch(Shape_trim, energy_etch, incident_energy, pos_v_etch, i_x_etch, i_z_etch) ;
		/*収率はエネルギー変化分(エッチング衝突時−現在のEi)による
		  energy_etch は record_etch_position() で得られる*/
	  }
      flag_contact    = false ;
    }
  
  return false ;
}


void Ion_class::
hardmask_sputter(class  Shape_trim_class *Shape_trim,
		 double incident_energy, double reflected_energy,
		 Particle_location_velocity_struct pos_v_recorded,
		 int i_x, int i_z ) 
{
  double tmp_beta ;
 
  tmp_beta = SELECTIVITY_HARDMASK * 
    yield_beta(incident_energy, reflected_energy) * 
    etch_yield_angle(Shape_trim->get_incident_angle(i_x, i_z, pos_v_recorded.v_x, pos_v_recorded.v_z) ) ;
 
  if(RAN0() < tmp_beta / YIELD_MAX) //仮想粒子を確率的に扱う
    {
      Shape_trim->desorb_mask(i_x, i_z);
      record_desorption(pos_v_recorded, Shape_trim->n_oxygen[i_x][i_z]) ; 
    }
}


//前方散乱でないときの衝突過程
bool Ion_class::
impact_on_surface(class  Shape_trim_class *Shape_trim)
{
  int i_x, i_z , i_x_particle, i_z_particle ;
  
  if( Shape_trim->find_solid_nearest_neighbor
      (pos_v.x,    pos_v.z ,
       pos_v.v_x,  pos_v.v_z ,
       &i_x, &i_z, &i_x_particle, &i_z_particle ) == SHAPE_Si )
    {
      double p_impact_parameter ;
      double incident_energy ;
      
      incident_energy = mass * pos_v.v_r * pos_v.v_r /(2.0 * Q_ELEMENTAL) ;
      
      if(incident_energy <= ENERGY_ION_STOPPING)
      	return true ;
      
      
      //最表面におけるエッチング過程
      if(flag_contact == false)
	{
	  ion_enhanced_etch(Shape_trim, incident_energy, 0.0,  pos_v, i_x, i_z ) ;
	  flag_contact = true ; //固体内部でのエッチングはなし
	}
		  
      // impact parameter は乱数Xで決定：
      // p = (L/2)√X  where  L は原子間距離
      p_impact_parameter = (L_INTER_ATOMIC / 2.0) * sqrt(RAN0());
		  
      // -- collision
      collision_with_solid_atom( p_impact_parameter );
    }
    
    //マスクであれば、break
    else if(Shape_trim->put_shape_matrix(pos_v.x, pos_v.z , &i_x, &i_z) == HARD_MASK )
    {
      flag_inside = false ;
      return true ;
    }
  
  return false ;
}


