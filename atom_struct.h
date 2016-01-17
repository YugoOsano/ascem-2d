#ifndef _ATOM_STRUCT_H_DEFINED_

#include <cmath>

//==================================
//==  Utility Constants     ========
//==================================
const int RANDOM_NUMBER_SEED = 529;//3 ;//4; //
//const int TRUE  = 1 ; 
//const int FALSE = 0 ;



//====================================
//==  ʪ�����              ==========
//====================================
const double PI    = 3.1415926535897932384626433 ; // �߼�Ψ
const double Q_ELEMENTAL    =  1.602e-19  ;    // ���Ų� ( c )
const double MASS_ELEC      =  9.1095e-31 ;   // �ŻҼ��� ( kg )
const double E_PERMITTIVITY =  8.8542e-12  ;  // ������Ͷ��Ψ( C2 / J m )
const double K_BOLTZMANN    =  1.3806503e-23; // Boltzmann���(m2 kg s-2 K-1)
const double K_BOLTZMANN_kcal = 1.987e-3  ;  // Boltzmann���(kcal mol-1 K-1)

const double BOHR_RADIUS    = 5.29177e-11 ;  // BohrȾ�� (m)



//====================================
//==  ��¤��                ==========
//====================================
//1: SCOFF ��¤���������
struct Atom_struct
{
  //Atomic Number
  int atomic_n ;
  
  //Atomic mass of most abundant isotope
  int atomic_mass ;
  
  //Atomic weight of most abundant isotope 
  double atomic_weight ;
  
  //Atomic weight of solid with normal isotopic abundance
  double atomic_weight_solid ;
  
  //Density of solid in grams/cm3
  double density_mass ;
  
  //Density of solid in units of 10^22 atoms/cm3
  double density_atom ;
};

//2: Si
const struct Atom_struct Si = {14, 28, 27.977, 28.086, 2.3212, 4.977}  ;

//3: Free Flight Path
const double FREE_FLIGHT_PATH_Si = pow( (Si.density_atom * 1.0e+28), -1.0/3.0 ) ;
//��ͳ����L=N^(-1/3), Si̩�٤��黻��(2.718592533e-10[m])


//4: Interatomic Distance
const double L_INTER_ATOMIC = FREE_FLIGHT_PATH_Si ;
//���Ҵֵ�Υ:��ͳ������Ʊ���Ȥ���(����)

//5: ����¾��γ��
const struct Atom_struct Cl = {17, 35, 34.969, 35.453, 1.8956, 3.22,  } ;


//6: γ�Ҽ���
const double CL_MASS = Cl.atomic_weight * 1.6726231e-27 ;
const double O_MASS  = 8.0              * 1.6726231e-27 ;



//====================================
//==  modeling geometry     ==========
//====================================
// ion stopping �κ�ɸ�˹�碌�ơ�x-z ʿ�̤򰷤����Ȥˤ���(z�ϲ�����)
// 2.718592533e-10 m / 1 cell
// 30nm  �����Ȥǡ�110.3512191 cells
// 40nm            147         cells
// 50nm  �����Ȥǡ�183.9186983 cells
// 80nm            294         cells
// 70nm  �����Ȥǡ�257.4861777 cells
// 100nm �����Ȥǡ�367.8373967 cells
// 200nm : 735 cells
// 250nm   919 cells
// 300nm  1102 cells  

const double CELL_SIZE = L_INTER_ATOMIC ;

//1: Layer
const int    N_from_TOP_to_MASK = 10; //Mask�����ΰ���
const int    N_MASK = 184; //184 //(mask)
const int    N_Si   = 0; //(mask)
const int    N_Si_2 = 0; //(mask)
const int    N_from_Si_bottom_to_SiO2_layer_top = 735;
const int    N_SiO2_layer = 7;
const int    N_under_Si_layer = 184;

//Mask��̵ͭ
//#define _NO_MASK_

//2: Line and Space Pattern
const int    N_CELL_X  = 184 + 18 + 184;
const int    N_CELL_Z = N_from_TOP_to_MASK + N_MASK + N_Si + N_Si_2 + N_from_Si_bottom_to_SiO2_layer_top + N_SiO2_layer + N_under_Si_layer;

const int    N_LEFT_MASK   = 184; //Mask�����̤ΰ���
const int    N_RIGHT_MASK  = 184 + 18; //Mask�����̤ΰ���
//const int    N_LEFT_MASK2  = 184 + 37 + 184;
//const int    N_RIGHT_MASK2 = 184 + 37 + 184 + 110; 
//const int    N_LEFT_MASK3  = 184 + 37 + 184 + 110 + 184;
//const int    N_RIGHT_MASK3 = 184 + 37 + 184 + 110 + 184 + 184;
//const int    N_LEFT_MASK4  = 184 + 37 + 184 + 110 + 184 + 184 + 184; 
//const int    N_RIGHT_MASK4 = 184 + 37 + 184 + 110 + 184 + 184 + 184 + 257;
//const int    N_LEFT_MASK5  = 184 + 37 + 184 + 110 + 184 + 184 + 184 + 257 + 184;
//const int    N_RIGHT_MASK5 = 184 + 37 + 184 + 110 + 184 + 184 + 184 + 257 + 184 + 368;
//const int    N_LEFT_MASK6  = 184 + 37 + 184 + 110 + 184 + 184 + 184 + 257 + 184 + 368 + 184;
//const int    N_RIGHT_MASK6 = 184 + 37 + 184 + 110 + 184 + 184 + 184 + 257 + 184 + 368 + 184 + 735;
//const int    N_LEFT_MASK7 = 184 + 37 + 184 + 110 + 184 + 184 + 184 + 257 + 184 + 368 + 184 + 735 + 184;
//const int    N_RIGHT_MASK7 = 184 + 37 + 184 + 110 + 184 + 184 + 184 + 257 + 184 + 368 + 184 + 735 + 184 + 1837;





//��¦Open Space(FLAG)
const bool   FLAG_OPEN_SPACE = false; //DEFAULT

const double SYSTEM_WIDTH_X  = L_INTER_ATOMIC * N_CELL_X ;
const double SYSTEM_HEIGHT_Z = L_INTER_ATOMIC * N_CELL_Z ;

//3: Mask¦�ɤη��г�
const double SLOPE_ANGLE_SIDEWALL = 0.0 * PI / 180.0 ; //degree->radian
//4: Si�����̤η��г�
const double SLOPE_ANGLE_SIDEWALL_Si   = 0.0 * PI / 180.0 ; //degree->radian
const double SLOPE_ANGLE_SIDEWALL_Si_2 = 0.0 * PI / 180.0 ; //degree->radian



//==================================
//==  Ion                   ========
//==================================
//1: Inject Ion
const int ION_INJECT_FLAG  = 3 ;
//From Center: 1
//From Top   : 2
//Use IADF   : 3


const int N_IADF_ARRAY = 901 ; //IADF�ζ��ڤ��


//2: Ion Flux
const double ION_FLUX = 1.0e+20 ; //(/m2 s)
//1.0e+20(/m2 s)=1.0e+16(/cm2 s)


//3: Incident Ion Energy
const double INCIDENT_ENERGY_ION = 100.0 ; //(eV)
#define IADF_FILE "iadf100.dat"


//4-1: Ion �����ͳ�(psi)
const double INCIDENT_ANGLE = 0.0 ;//(degree) (-90~90)

//4-2: Ion �����Ͳ�ž��(theta)
const bool RANDOM_ROTATION_ANGLE_FLAG = true;//false;//

//4-3: Ion ��������(From Center ONLY!!)
const int BEAM_WIDTH = 50 ;//(cell) 




//5: Threshold Energy
const double Eth_Si   = 12.0 ; //(eV)
const double Eth_SiO2 = 30.0 ; //(eV)


//6: Etch Yield�κ�����
//Ei��¸����Ƴ�����뤿�ᡢγ�Ҥε���æΥȿ���� 1/Ymax �ܤ�����Ψ�ǵ�����
const double YIELD_MAX     = int(0.353 *(sqrt(INCIDENT_ENERGY_ION) - sqrt(Eth_Si))) + 1.0 ;
const int    YIELD_MAX_INT = int(YIELD_MAX) ;

//7: Ion stopping energy
const double ENERGY_ION_STOPPING = 4.0 ;//(eV)


//8: Forward Scattering(FLAG)
const bool FLAG_FORWARD_SCATTER = true;//false;//


//9: Ion Reactive Etching(FLAG)
const bool FLAG_ION_REACTIVE_ETCH = true;//false;//



//==================================
//==  Neutral               ========
//==================================
//1: Inject Neutral /*����*/
#define _INJECT_CL_RADICAL_


//2: Neutral/Ion Flux Ratio
const double NEUTRAL_ION_RATIO = 100.0;//100.0 ;


//3: Incident Neutral Energy
const double INCIDENT_ENERGY_NEUTRAL = 2.0 ; //(eV)

//2: Oxygenʿ�Ѳ�program
const bool FLAG_DISPERSE_OXIDATION = false;//true; //DEFAULT==false
//(Osano 3rd paper)���Ǥ����夹�뤳�Ȥˤ������԰�����ɤ���������αƶ�(��Ψ���㲼)��ʬ��������


//3: 1�ĤΥ����Ȥ˵������ Cl adatom �ο�
const int NMAX_ADATOM  = 4 ;//3;//


//4: Chemical Etching
const bool FLAG_CHEMICAL_ETCH  = true;//false;// //DEFAULT==TRUE

const double N_DOPANT    = 1.0e+18 ; //Dopant Density(cm-3)
const double T_SUBSTRATE = 320.0 ;   //Substrate Temperature(K)
const double T_GAS       = 500.0 ;   //Gas Temperature(K)

const double YIELD_CHEMICAL
= (4.04e-18 * pow(N_DOPANT, 0.39) * sqrt(T_SUBSTRATE) * exp( - 4.70 / (K_BOLTZMANN_kcal * T_SUBSTRATE) ))
	* (1.0e-8 / 60.0) * Si.density_atom * 1.0e+22 / ( 0.25 * 1.0e+2 * sqrt(8.0 * K_BOLTZMANN * T_GAS / (PI * CL_MASS ))) ;
/*Ogryzlo�μ�*/



//5: Adsorption Probability
const double ADSORPTION_PROBABILITY   = 1.0;
const double ADSORPTION_PROBABILITY_O = 1.0;
//*������Simulation��Ǥϲ���Ū��1/Ymax�ܤ�����Τ����


//6-1: Selectivity (SiO,SiO2)
const double SELECTIVITY_SiO  = 1.0/8.2;//15.1;//45.1;//24.5;//22.5;//19.7;//14.8;//19.8;//24.2;//7.0;
const double SELECTIVITY_SiO2 = 1.0/8.2;//15.1;//45.1;//24.5;//22.5;//19.7;//14.8;//19.8;//24.2;//7.0;

//6-2: Selectivity (Hard Mask)
//Mask�ο���
const bool FLAG_MASK_EROSION = true;//false;//
/*TRUE�ʤ�Mask���γ�Ҥ�����*/

const double SELECTIVITY_HARDMASK = 0.0;//0.05;//
/*0.0�ʤ�Mask��Etching����ʤ�*/


//7: Flux Count(FLAG)
const bool FLAG_FLUX_COUNT = false;//true;// //DEFAULT


//8-1: Saturated Surface(FLAG)
const bool FLAG_SATURATED_SURFACE = false;//true;//

//8-2: Saturated Surface oxygen(FLAG)
const bool FLAG_SATURATED_SURFACE_OXYGEN = false;//true;//



//==================================
//==  Oxygen                ========
//==================================
//1: Inject Neutral /*����*/
//#define _INJECT_O_RADICAL_


//2: Oxygen/Ion Flux Ratio
const double OXYGEN_ION_RATIO = 0.0;



//==================================
//==  Etch Products SiCl4   ========
//==================================
//1: Include SiCl4 /*����*/
#define _INCLUDE_PRODUCT_SiCl4_


//2: SiCl4 Deposition Probability
const double SiCl4_DEPOSITION_PROBABILITY= 0.05;



//==================================
//==  Etch Products SiCl2   ========
//==================================
//1: Include SiCl2 /*����*/
#define _INCLUDE_PRODUCT_SiCl2_


//2: SiCl2 Deposition Probability
const double SiCl2_DEPOSITION_PROBABILITY  = 0.05;

//3: SiCl2 Re-Incidence Probability
const double SiCl2_REINCIDENCE_PROBABILITY = 0.0;



//==================================
//==  Etch Products SiOCl2  ========
//==================================
//1: Include SiOCl2 /*����*/
//#define _INCLUDE_PRODUCT_SiOCl2_


//2: SiOCl2 Deposition Probability
const double SiOCl2_DEPOSITION_PROBABILITY  = 0.0;


//3: SiOCl2 Re-Incidence Probability
const double SiOCl2_REINCIDENCE_PROBABILITY = 0.0;



//====================================
//==  Simulation Time       ==========
//====================================
//1-1:File�˵�Ͽ��������
const int INTERVAL_FILE_OUTPUT = int( 5.0 * ION_FLUX * SYSTEM_WIDTH_X * L_INTER_ATOMIC ) ;
/*int( 5.0 <- ���ο������ÿ���ɽ��)*/


//1-2:File�˵�Ͽ��������(DEFAULT==unsetup)
//const int INTERVAL_FILE_OUTPUT = 1000 ;//int(N_ION_INJECT / 1) ; //10) ; //

//Output Ion Trajectory(DEFAULT==unsetup)
//#define _ION_TRAJECTORY_ //DEFAULT==unsetup
const int ION_TRAJECTORY_COUNT = 100 ;


//2:Number of inject Ion
const int N_ION_INJECT = INTERVAL_FILE_OUTPUT * 100 ;


//3:Real Time(Flux->Time�Ѵ�)
const double REAL_ELAPSED_TIME 
=     N_ION_INJECT /  (ION_FLUX * SYSTEM_WIDTH_X * L_INTER_ATOMIC) ;



//====================================
//==  Option                ==========
//====================================
//1: Standard I/O (���̽�������)
const int N_COUT_INTERVAL = 100 ;


//2: ����FILE���ɹ�(FLAG) (DEFAULT==false)
const bool FLAG_INPUT_PROFILE = false;//true;


#define CL_INPUT_FILE  "Cl_bond543950.dat"
#define SI_INPUT_FILE  "Si_matrix543950.dat"

#define CL_BOND_FILE          "Cl_bond"
#define SI_MATRIX_FILE        "Si_matrix"
#define CONDITION_FILE        "condition.txt"
#define YIELD_FILE            "yield"
#define ION_COUNTER_FILE      "ion_count"
#define NEUTRAL_COUNTER_FILE  "neutral_count"



//====================================
//==  ��ɸ                  ==========
//====================================
struct Particle_location_velocity_struct
{
  double x ;
  double y ;
  double z ; 
  
  double v_x ;
  double v_y ;
  double v_z ;

  double v_r ;
  double v_theta ;
  double v_psi ;
};


#define _ATOM_STRUCT_H_DEFINED_
#endif



