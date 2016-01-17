// == main_deposition.cc ==
// 


// -- simplified Monte Carlo simulation of 
//    low energy ion penetration into solids
// 
// p-109�� �򻲾�

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <ctime>

#include "atom_struct.h"

#include "etch_products.h"
#include "random_number.h"
#include "fileio_particle.h"

#include "particle.h"
#include "neutral_particle.h"
#include "ion_particle.h"
#include "shape_trim.h"
#include "rotating_matrix.h"
#include "integration_angle.h"
#include "common_utils.h"
using namespace std;

//------------
//-- reduced energy ����Ϥ���
// ���ϡ����ͥ����󡢥������åȸ��Ρ����ͥ��ͥ륮��(eV)


//--------------------------
int main()
{

  time_t	computing_start,  computing_current;
  time(&computing_start);

  sgenrand(RANDOM_NUMBER_SEED) ;
  srand( time(NULL) );
  
  
  //== ���饹������ ===
  class Ion_class         Cl_ion(CL_MASS, 0, N_IADF_ARRAY ) ;
  class Neutral_class     Cl_neutral(CL_MASS, 0 ) ;
  class Shape_trim_class  Shape(FLAG_OPEN_SPACE)  ;

  //***************************************
  //--- ���ǤΥ��󥹥��󥹤����
  // -- Si�λ����ν����� Shape_trim ���饹�Υ��ФǹԤ��Τ�
  // ���Τ�����ä˿��������饹�Ϻ��ʤ�
  
  class Neutral_class   Oxygen_atom(O_MASS, 0) ;
  
  //***************************************
  //--- Etch product�Υ��󥹥��󥹤����
  
  class Etch_product_class  SiCl4_neutral  (CL_MASS, 0, 4, 0,
					   SiCl4_DEPOSITION_PROBABILITY	 ) ;
  class Etch_product_class  SiCl2_neutral  (CL_MASS, 0, 2, 0,
					   SiCl2_DEPOSITION_PROBABILITY	 ) ;
  class Etch_product_class  SiOCl2_neutral (CL_MASS, 0, 2, 1,
					   SiOCl2_DEPOSITION_PROBABILITY ) ;
  class Etch_product_class  SiO2_neutral   (CL_MASS, 0, 0, 2,
					   SiOCl2_DEPOSITION_PROBABILITY ) ;
  
  if(FLAG_OPEN_SPACE == true)//== ��¦ open space�ξ��
    {
      Cl_ion.set_flag_boundary(SPECULAR_REFLECT) ;
      Cl_neutral.set_flag_boundary(SPECULAR_REFLECT);  
      SiCl4_neutral.set_flag_boundary(SPECULAR_REFLECT) ;
      SiCl2_neutral.set_flag_boundary(SPECULAR_REFLECT) ;
      SiOCl2_neutral.set_flag_boundary(SPECULAR_REFLECT) ;
      Oxygen_atom.set_flag_boundary(SPECULAR_REFLECT) ;
   }

 //== flux count ==
  class Shape_counter_class Ion_counter ;
  class Shape_counter_class Neutral_counter ;
  if(FLAG_FLUX_COUNT == true)
    {
      Ion_counter.allocate_memory(); //== ������� ==
      Neutral_counter.allocate_memory();
    }

  if( ION_INJECT_FLAG == 3 ) //== IADF �ɤ߹���
    Cl_ion.read_angular_df(IADF_FILE) ; 

  if(FLAG_INPUT_PROFILE == true) //== �����ɤ߹��� ===
    Shape.input_profile(SI_INPUT_FILE, CL_INPUT_FILE ) ;

  //== ���Ū�˻��Ѥ����ѿ�
  
  bool   tmp_flag ;
  int    i_x, i_z ;
  bool    flag_deposition  ;
  
  //�����
  i_x = 0; i_z = 0;
  tmp_flag = false ;
  flag_deposition = false ;
 
  
  //== �׻����ε�Ͽ������
  ofstream  condition_file(CONDITION_FILE) ;
  ofstream  log_file(YIELD_FILE) ;
  
  ofstream ion_trajectory_file("ion_trajectory.txt") ;
  
  cout << "First Pattern width(nm): " << L_INTER_ATOMIC * (N_RIGHT_MASK - N_LEFT_MASK) * 1.0e+9
       << "\nMask thickness(nm): " << N_MASK * L_INTER_ATOMIC * 1.0e+9
       << "\nSi_1 thickness(nm): " << N_Si * L_INTER_ATOMIC * 1.0e+9
       << "\nSi_2 thickness(nm): " << N_Si_2 * L_INTER_ATOMIC * 1.0e+9
       << "\nRange from Si bottom to SiO2 layer top(nm): " << N_from_Si_bottom_to_SiO2_layer_top * L_INTER_ATOMIC * 1.0e+9
       << "\nSiO2 layer thickness(nm): " << N_SiO2_layer * L_INTER_ATOMIC * 1.0e+9
       << "\nUnder Si layer thickness(nm): " << N_under_Si_layer * L_INTER_ATOMIC * 1.0e+9
       << "\n\nMask angle(nm): "           << SLOPE_ANGLE_SIDEWALL * 180.0 / PI
       << "\nSidewall_1 angle(degree): "   << SLOPE_ANGLE_SIDEWALL_Si * 180.0 / PI
       << "\nSidewall_2 angle(degree): "   << SLOPE_ANGLE_SIDEWALL_Si_2 * 180.0 / PI
       << "\n\nNumber of ions to be injected: " << N_ION_INJECT
       << "\nNumber of ion trajectory: "      << ION_TRAJECTORY_COUNT
       << "\nReal time of evolution: "        << REAL_ELAPSED_TIME 
       << "\nInterval time of evolution: "    << REAL_ELAPSED_TIME / (N_ION_INJECT/INTERVAL_FILE_OUTPUT)
       << "\nInterval for file output: "      << INTERVAL_FILE_OUTPUT 
       << "\n\nflag of ion reactive etch: " << FLAG_ION_REACTIVE_ETCH
       << "\nIon flux(/m2 s): " << ION_FLUX
       << "\nIon flux(/cm2 s): "  << ION_FLUX * 1.0e-4
       << "\nIon incident mode(ION_INJECT_FLAG): "  << ION_INJECT_FLAG
       << "\nIon incident energy(eV): "       << INCIDENT_ENERGY_ION
       << "\nIon incident angle(degree): "    << INCIDENT_ANGLE
       << "\nIon Beam width(cell): "          << BEAM_WIDTH
       << "\nIon stoping energy(eV): "        << ENERGY_ION_STOPPING
       << "\nSi Threshold Energy:  "          << Eth_Si
       << "\nSiO2 Threshold Energy:  "        << Eth_SiO2
       << "\nYield Max:  "                    << YIELD_MAX
       << "\nNeutral incident energy(eV): "   << INCIDENT_ENERGY_NEUTRAL
       << "\nNeutral to ion flux ratio: "     << NEUTRAL_ION_RATIO
       << "\n\nflag of chemical etching: "    << FLAG_CHEMICAL_ETCH
       << "\nSubstrate temperature(K): "      << T_SUBSTRATE
       << "\nGas temperature(K): "            << T_GAS
       << "\nDopant density(cm-3): "          << N_DOPANT 
       << "\nYield for chemical etching: "    << YIELD_CHEMICAL
       << "\nSaturated surface:  "            << FLAG_SATURATED_SURFACE
       << "\nSaturated surface oxygen:  "     << FLAG_SATURATED_SURFACE_OXYGEN
       << "\n\nflag of forward scattering: "  << FLAG_FORWARD_SCATTER
       << "\nflag of mask erosion: "          << FLAG_MASK_EROSION
       << "\nSiO/Si Selectivity: "            << SELECTIVITY_SiO
       << "\nSiO2/Si Selectiity: "            << SELECTIVITY_SiO2
       << "\nHardmask/Si Selectivity: "       << SELECTIVITY_HARDMASK
       << "\nslope angle of mask: "           << SLOPE_ANGLE_SIDEWALL
       << "\nflag of one sided open space: "  << FLAG_OPEN_SPACE
       << "\n\n" << endl ;
  
  condition_file 
       << "First Pattern width(nm): " << L_INTER_ATOMIC * (N_RIGHT_MASK - N_LEFT_MASK) * 1.0e+9
       << "\nMask thickness(nm): " << N_MASK * L_INTER_ATOMIC * 1.0e+9
       << "\nSi_1 thickness(nm): " << N_Si * L_INTER_ATOMIC * 1.0e+9
       << "\nSi_2 thickness(nm): " << N_Si_2 * L_INTER_ATOMIC * 1.0e+9
       << "\nRange from Si bottom to SiO2 layer top(nm): " << N_from_Si_bottom_to_SiO2_layer_top * L_INTER_ATOMIC * 1.0e+9
       << "\nSiO2 layer thickness(nm): " << N_SiO2_layer * L_INTER_ATOMIC * 1.0e+9
       << "\nUnder Si layer thickness(nm): " << N_under_Si_layer * L_INTER_ATOMIC * 1.0e+9
       << "\n\nMask angle(nm): "           << SLOPE_ANGLE_SIDEWALL * 180.0 / PI
       << "\nSidewall_1 angle(degree): "   << SLOPE_ANGLE_SIDEWALL_Si * 180.0 / PI
       << "\nSidewall_2 angle(degree): "   << SLOPE_ANGLE_SIDEWALL_Si_2 * 180.0 / PI
       << "\n\nNumber of ions to be injected: " << N_ION_INJECT
       << "\nNumber of ion trajectory: "      << ION_TRAJECTORY_COUNT
       << "\nReal time of evolution: "        << REAL_ELAPSED_TIME 
       << "\nInterval time of evolution: "    << REAL_ELAPSED_TIME / (N_ION_INJECT/INTERVAL_FILE_OUTPUT)
       << "\nInterval for file output: "      << INTERVAL_FILE_OUTPUT 
       << "\n\nflag of ion reactive etch: " << FLAG_ION_REACTIVE_ETCH
       << "\nIon flux(/m2 s): " << ION_FLUX
       << "\nIon flux(/cm2 s): "  << ION_FLUX * 1.0e-4
       << "\nIon incident mode(ION_INJECT_FLAG): "  << ION_INJECT_FLAG
       << "\nIon incident energy(eV): "       << INCIDENT_ENERGY_ION
       << "\nIon incident angle(degree): "    << INCIDENT_ANGLE
       << "\nIon Beam width(cell): "            << BEAM_WIDTH
       << "\nIon stoping energy(eV): "        << ENERGY_ION_STOPPING
       << "\nSi Threshold Energy:  "          << Eth_Si
       << "\nSiO2 Threshold Energy:  "        << Eth_SiO2
       << "\nYield Max:  "                    << YIELD_MAX
       << "\nNeutral incident energy(eV): "   << INCIDENT_ENERGY_NEUTRAL
       << "\nNeutral to ion flux ratio: "     << NEUTRAL_ION_RATIO
       << "\n\nflag of chemical etching: "    << FLAG_CHEMICAL_ETCH
       << "\nSubstrate temperature(K): "      << T_SUBSTRATE
       << "\nGas temperature(K): "            << T_GAS
       << "\nDopant density(cm-3): "          << N_DOPANT 
       << "\nYield for chemical etching: "    << YIELD_CHEMICAL
       << "\nSaturated surface:  "            << FLAG_SATURATED_SURFACE
       << "\nSaturated surface oxygen:  "     << FLAG_SATURATED_SURFACE_OXYGEN
       << "\n\nflag of forward scattering: "  << FLAG_FORWARD_SCATTER
       << "\nflag of mask erosion: "          << FLAG_MASK_EROSION
       << "\nSiO/Si Selectivity: "            << SELECTIVITY_SiO
       << "\nSiO2/Si Selectiity: "            << SELECTIVITY_SiO2
       << "\nHardmask/Si Selectivity: "       << SELECTIVITY_HARDMASK
       << "\nslope angle of mask: "           << SLOPE_ANGLE_SIDEWALL
       << "\nflag of one sided open space: "  << FLAG_OPEN_SPACE
       << "\n\n" << endl ;


  #ifdef _INCLUDE_PRODUCT_SiCl4_
      cout           << "sticking probability of SiCl4: " <<  SiCl4_DEPOSITION_PROBABILITY << endl ;
      condition_file << "sticking probability of SiCl4: " <<  SiCl4_DEPOSITION_PROBABILITY << endl ;
  #endif
  
  
  #ifdef _INCLUDE_PRODUCT_SiCl2_
    {
      cout           << "SiCl2 reincidence probability: " << SiCl2_REINCIDENCE_PROBABILITY 	    
		     << "\nsticking probability of SiCl2: " << SiCl2_DEPOSITION_PROBABILITY << endl ;
      condition_file << "\nSiCl2 reincidence probability: " << SiCl2_REINCIDENCE_PROBABILITY 		 
		     << "\nsticking probability of SiCl2: " << SiCl2_DEPOSITION_PROBABILITY << endl ;
    }
  #endif
  ofstream file_SiCl2("file_SiCl2.dat");
  
  
  #ifdef _INCLUDE_PRODUCT_SiOCl4_
      cout           << "SiOCl2 reincidence probability: " << SiOCl2_REINCIDENCE_PROBABILITY 
		     << "\nsticking probability of SiOCl2: " << SiOCl2_DEPOSITION_PROBABILITY << endl ;
      condition_file << "\nSiOCl2 reincidence probability: " << SiOCl2_REINCIDENCE_PROBABILITY 
		     << "\nsticking probability of SiOCl2: " << SiOCl2_DEPOSITION_PROBABILITY << endl ;
  #endif
  ofstream file_SiOCl2("file_SiOCl2.dat");

 
  #ifdef _INJECT_O_RADICAL_
      cout           << "oxygen to ion flux ratio: " << OXYGEN_ION_RATIO 
		     << "\netch rate ratio SiO/Si: " << SELECTIVITY_SiO 
		     << "\netch rate ratio SiO2/Si: " << SELECTIVITY_SiO2 << endl ;
      condition_file << "\noxygen to ion flux ratio: " << OXYGEN_ION_RATIO 
		     << "\netch rate ratio SiO/Si: " << SELECTIVITY_SiO 
		     << "\netch rate ratio SiO2/Si: " << SELECTIVITY_SiO2 << endl ;
  #endif

  
  cout << "-------------------------" << endl ;
  
  
  //*****************************************
  //----    �롼�׳���         --------------
  //*****************************************
  
  int i_ion     = 0 ; 
  int i_neutral = 0 ;  
  int i_neutral_o = 0 ;
  do
    {
      //*****************************************
      //== �롼�ײ����æΥSi�ο��ν��ϡ���Ͽ
      //*****************************************
      if(i_ion % N_COUT_INTERVAL == 0) 
	{
	  time(&computing_current);
	  
	  cout << "Ion: " << i_ion 
	       << "\tCl: " << i_neutral 
	       << "\tO: " << i_neutral_o  
	       << "\t\tdesorbed Si: "  << Shape.cntr_desorbed_Si 
	       << "\tdeposited Si: " << Shape.cntr_deposited_Si
	       << "\tdesorbed mask: "<< Shape.cntr_desorbed_mask
	       << "\tcomputing: " 
	       << difftime(computing_current, computing_start) << endl ;
	  
	  log_file << i_ion << "\t" << Shape.cntr_desorbed_Si 
		   << "\t" << Shape.cntr_deposited_Si << endl ;
	}
      //*****************************************
      // --        Cl �饸���������
      //*****************************************
      
#ifdef _INJECT_CL_RADICAL_
      while(double(i_ion) * NEUTRAL_ION_RATIO > double(i_neutral))
	{
	  i_neutral++ ;
	  Cl_neutral.all_process(&Shape, &Neutral_counter, false,
				 FLAG_FLUX_COUNT,
				 INCIDENT_ENERGY_NEUTRAL,
				 FLAG_CHEMICAL_ETCH, YIELD_CHEMICAL) ;
	}  //  === END: Cl �饸����ν��� 
#endif
      
	    
	  //*********************************************
	  //---   ���Ǹ���  ���� 
	  //*********************************************
#ifdef _INJECT_O_RADICAL_
      
	  while(double(i_ion) * OXYGEN_ION_RATIO > double(i_neutral_o) )
	    {
	      i_neutral_o++ ;
	      Oxygen_atom.all_process_oxygen(&Shape, &Neutral_counter, false,
					     FLAG_FLUX_COUNT,
					     INCIDENT_ENERGY_NEUTRAL) ;
	    } // ���Ǥν�����λ
#endif

      //*****************************************
      // -- ���������͡����륨�ͥ륮����Ϳ���Ƥ�äơ�
      //    ���ͤ򷫤��֤������ͥ륮�������뤷�����ͤ򲼲�ä���
      //�������ȥåפ��롣
      // �⤷����ķ���֤ä� z < 0 �Ȥʤä����⥹�ȥåס�
      //*****************************************
      // flag �ˤ�ä����ͤξ����Ѥ���
      // 150eV -> m/s ���Ѵ�
      
      // === ��ɽγ�ҿ��� 1/Ymax �ܤ���Τǡ�Ymax�󷫤��֤� ===
      //i_counter = 0 ; //--debug
      for (int i_virtual_ion = 0; 
	   i_virtual_ion  < YIELD_MAX_INT; i_virtual_ion++)
	{
	  //== ���������� ==
	  if (ION_INJECT_FLAG == 1){
	    Cl_ion.inject_from_center( sqrt(2.0 * INCIDENT_ENERGY_ION * Q_ELEMENTAL / Cl_ion.mass) ) ;
	  }
	  else if (ION_INJECT_FLAG == 2 ){
	    Cl_ion.inject_from_top( sqrt(2.0 * INCIDENT_ENERGY_ION * Q_ELEMENTAL / Cl_ion.mass) ) ;
	  }
	  else {//(ION_INJECT_FLAG == 3 ) 
	    Cl_ion.inject_iadf( sqrt(2.0 * INCIDENT_ENERGY_ION * Q_ELEMENTAL / Cl_ion.mass) ) ;
	  }


	  Cl_ion.set_flag_reflection(false);//== ���������flag��ꥻ�å� 
	  
	  while(1) 
	    {
	      //-- ���ֺ�ɸ������γ�Ҥΰ�ư��
	      // -- free flight path(L) �ϰ���ȸ��ʤ�
	      
	      Cl_ion.move_trans(FREE_FLIGHT_PATH_Si) ;

#ifdef _ION_TRAJECTORY_
	      if(i_ion % (int)(N_ION_INJECT / ION_TRAJECTORY_COUNT) == 0 ){
	      //-- ion_trajectory_file �ν��� (Default==comment out)
	      	      	      ion_trajectory_file << Cl_ion.pos_v.x * 1.0e+9 << "\t"
	      				  << Cl_ion.pos_v.z * 1.0e+9 - N_from_TOP_to_MASK * CELL_SIZE * 1.0e+9 << "\n" ;
	      }
#endif

		if(Cl_ion.put_flag_inside() == false)
		break ; //�ΰ�����ӽФ������
		
		/*
		//==�ޥ�������ã�������� break ==
		if(Shape.put_shape_matrix(Cl_ion.pos_v.x, Cl_ion.pos_v.z , &i_x, &i_z ) == HARD_MASK )
		{
			if(FLAG_FLUX_COUNT == true)
			Ion_counter.count(i_x, i_z ) ;
			
			break ;
		}
		*/
		
		//�������𤢤�
		if(FLAG_FORWARD_SCATTER == true)
		tmp_flag = Cl_ion.impact_scattering(&Shape, FLAG_MASK_EROSION);
		
		//��������ʤ�
		else
		tmp_flag = Cl_ion.impact_on_surface(&Shape);
		
		if(tmp_flag == true)
		break ;
		
		} //END of while loop

	  Cl_ion.add_ctr_reflection(); //== ��������Υ����󥿲û� ==

	  // ==== ���ͥ륮�����������ʤä��Ȥ���Si ���ҤǤ���Ф���������
	  if(Cl_ion.put_flag_inside() == true )
	    {
	      //***** 02Dec2003 **************
	      if(RAN0() < 1.0 / YIELD_MAX) //<- ����ˤ��󤷤ƤⲾ��γ�Ҥ��ΨŪ�˰���
		Shape.adsorb_Cl(i_x, i_z) ;
	    }

	  
	  //*************************************************
	  //---   etch product  æΥ ��Cl_ion ��flag �ˤ���
	  //*************************************************
	  #ifdef _INCLUDE_PRODUCT_SiCl4_
	  if(Cl_ion.flag_desorb_Si == true )
	  {
		bool flag_product_diffusion  ;
		
		if(Cl_ion.n_oxy_desorb_Si == 1)
		{
			flag_product_diffusion =
		    SiOCl2_neutral.allocate_on_surface(&Shape, Cl_ion.position_at_desorption, sqrt(2.0 * INCIDENT_ENERGY_NEUTRAL * Q_ELEMENTAL / SiOCl2_neutral.mass)) ;
		    
		    if( flag_product_diffusion == true )
		    SiOCl2_neutral.whole_flight(&Shape, false) ;
		}
	    
	    else if(Cl_ion.n_oxy_desorb_Si == 2)
		{
		  flag_product_diffusion =
		    SiO2_neutral.allocate_on_surface
		    (&Shape,  Cl_ion.position_at_desorption,
		     sqrt(2.0 * INCIDENT_ENERGY_NEUTRAL * 
			  Q_ELEMENTAL / SiO2_neutral.mass)) ;
		  
		  if( flag_product_diffusion == true )
		    SiO2_neutral.whole_flight(&Shape, false) ;
		}
	    
	    //== SiCl4�ξ��
	    else
		{
		  flag_product_diffusion =
		    SiCl4_neutral.allocate_on_surface
		    (&Shape,  Cl_ion.position_at_desorption,
		     sqrt(2.0 * INCIDENT_ENERGY_NEUTRAL * 
		      Q_ELEMENTAL / SiCl4_neutral.mass)) ;
		  
		  if( flag_product_diffusion == true )
		    SiCl4_neutral.whole_flight(&Shape, false) ;
		}
	  }
	  #endif
	  //*************************************************
	  //---   SiCl2  ���� 
	  //*************************************************
	  #ifdef _INCLUDE_PRODUCT_SiCl2_
	      if(SiCl4_neutral.put_flag_inside() == false && RAN0() < SiCl2_REINCIDENCE_PROBABILITY )
	      {
		  SiCl2_neutral.inject_from_top(sqrt(2.0 * INCIDENT_ENERGY_NEUTRAL * 
						     Q_ELEMENTAL/SiCl2_neutral.mass)); 
		  SiCl2_neutral.add_n_injection();
		  SiCl2_neutral.whole_flight(&Shape, false) ;
		  
		  } // SiCl2 �ν�����λ
	    #endif
	  //*************************************************
	  //---   SiCl2O  ���� 
	  //*************************************************
	  #ifdef _INCLUDE_PRODUCT_SiOCl2_
	      if(SiCl4_neutral.put_flag_inside() == false &&
		 RAN0() < SiOCl2_REINCIDENCE_PROBABILITY )
		    {
		      
		      SiOCl2_neutral.inject_from_top
			( sqrt(2.0 * INCIDENT_ENERGY_NEUTRAL * 
			       Q_ELEMENTAL / SiOCl2_neutral.mass) ) ; 
		      SiOCl2_neutral.add_n_injection();
		      SiOCl2_neutral.whole_flight(&Shape, false) ;
		    } // SiOCl2 �ν�����λ
	      //=== ���Ϳ������󥿤ν��� ===
	      if(i_ion % INTERVAL_FILE_OUTPUT == 0 || i_ion == N_ION_INJECT )
		  file_SiOCl2 << SiOCl2_neutral.put_n_injection() << "\n" ;
	   #endif
      
      //*************************************************
	  //=== ���Ϳ������󥿤ν��� ===
	  //*************************************************
	  if(i_ion % INTERVAL_FILE_OUTPUT == 0 ||
	     i_ion == N_ION_INJECT )
	    {
			#ifdef _INCLUDE_PRODUCT_SiCl2_
		    file_SiCl2 << i_ion << "\t" << SiCl2_neutral.put_n_injection() << "\n" ;
		    #endif
		    
		    #ifdef _INCLUDE_PRODUCT_SiOCl2_
		    file_SiOCl2 << i_ion << "\t"<< SiOCl2_neutral.put_n_injection() << "\n" ;
		    #endif
	    }
	  
	}// === for loop  END : ���������ͤν���
      
      //-- isolation check
      Shape.remove_isolated_Si() ; //<- �����ȥ����Ȥ��Ƥ���
      
      //****************************
      //--     �ե��������
      //  -> ��ĤΥ���ˤ�����Cl�ο��Ȼ��Ǥο���Ʊ��Υե������
      //     ��Ͽ��������-> 10�ʿ��ǽ��ΰ̤���Ǥο�����ΰ̤�Cl�ο��Ȥ���
      //     -> �ץ�åȤ���ݤ�mod��ȤäƤ��줾��ο�����Ф���
      //****************************
      if(i_ion % INTERVAL_FILE_OUTPUT == 0 ||
	 i_ion == N_ION_INJECT ||
	 Shape.flag_get_bottom == true ) 
	//-- ���̤���ã������ե�������Ϥ��ƥ롼�׽�λ
	{
	  int tmp;   char OUT1[50] ; 
	  tmp = sprintf( OUT1, "%s%d.dat", CL_BOND_FILE, i_ion);
	  
	  output_cellinfo(Shape.n_oxygen, Shape.n_Clbond ,
			  i_ion,  OUT1, 
			  N_CELL_X, N_CELL_Z , CELL_SIZE ) ;
			  
	  tmp = sprintf( OUT1, "%s%d.dat", SI_MATRIX_FILE, i_ion);
	  output_array_splot(OUT1 , Shape.shape_matrix ,
			     N_CELL_X, N_CELL_Z ) ;

	  if(FLAG_FLUX_COUNT == true && i_ion != 0)
	    {
	      tmp = sprintf( OUT1, "%s%d.dat", ION_COUNTER_FILE, i_ion);
	      output_array_splot(OUT1 , Ion_counter.ctr ,
				 N_CELL_X, N_CELL_Z ) ;  
	      tmp = sprintf( OUT1, "%s%d.dat", NEUTRAL_COUNTER_FILE, i_ion);
	      output_array_splot(OUT1 , Neutral_counter.ctr ,
				 N_CELL_X, N_CELL_Z ) ;  
	    }
	}

      i_ion++ ;
    }// do loop ��λ
  while( i_ion <= N_ION_INJECT &&
	 Shape.flag_get_bottom == false ) ;

  return 0;

}


