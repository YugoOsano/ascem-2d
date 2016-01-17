// output_particle.cc

// -- 複数の配列に対してファイル出力を行なう 
// オーバーロードして配列1つ、2つ、3つの場合に対応
// output_array( [ファイル名] [配列] ... )



#ifndef _FILEIO_PARTICLE_CC_

#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>

#include "fileio_particle.h"
using namespace std;

//void input_array(char[],double[], double[],long int ) ;

//void output_array(char[],double[], long int ) ;

// X-Y plot 向け。GNUPLOTで
// plot " - " using 1:2 w l
// と出力

//void output_array(char[],double[],double[], long int );

//----------------------------------------------------
// 入力

void input_array(char file_name[], 
		 double  array1[] ,  double array2[],
		 long int  array_size )
{
  ifstream  data_file_input(file_name) ;
  if(data_file_input.bad())
    {
      cerr << "Unable to open the file:" << file_name << "\n" ;  
      exit(8) ;
    }

  for (int i = 0 ; i < array_size ; i++ )
    {
      data_file_input >> array1[i] >> array2[i];
      if(data_file_input.bad())
	{
	  cerr << "Unable to access the file:" 
	       << file_name << "\n" ;  
	  exit(8) ;
	}
    }
 
} 

//---------------------------------------------------
// 出力
void output_array(char file_name[], double  array1[] , 
		  long int  array_size )
{
  ofstream  data_file(file_name) ;
  if(data_file.bad())
    {
      cerr << "Unable to open the file:" << file_name << "\n" ;  
      exit(8) ;
    }
  for (int i = 0 ; i < array_size ; i++ )
    {
      data_file << array1[i] << endl ;
      if(data_file.bad())
	{
	  cerr << "Unable to access the file:" 
	       << file_name << "\n" ;  
	  exit(8) ;
	}
    }
 
} 

void output_array(char file_name[], double  array1[] , double  array2[] ,
		  long int  array_size )
{
  ofstream  data_file(file_name) ;
  if(data_file.bad())
    {
      cerr << "Unable to open the file:" << file_name << "\n" ;  
      exit(8) ;
    }

  for (int i = 0 ; i < array_size ; i++ )
    {
      data_file << array1[i] << "\t" << array2[i] << endl ;
      if(data_file.bad())
	{
	  cerr << "Unable to access the file:" 
	       << file_name << "\n" ;  
	  exit(8) ;
	}
    }
}
//**************************************************
void output_array(char file_name[], double  array1[] , double  array2[] ,
		  double  array3[] , double  array4[] ,
		  long int  array_size )
{
  ofstream  data_file(file_name) ;
  if(data_file.bad())
    {
      cerr << "Unable to open the file:" << file_name << "\n" ;  
      exit(8) ;
    }
  for (int i = 0 ; i < array_size ; i++ )
    {
      data_file << array1[i] << "\t" << array2[i]
		<< "\t" << array3[i] << "\t" << array4[i] << endl ;
      if(data_file.bad())
	{
	  cerr << "Unable to access the file:" 
	       << file_name << "\n" ;  
	  exit(8) ;
	}
    }
} 



//   ---- input function for dynamically allocated 2D array
void input_array_splot(char file_name[], 
			double **array1, 
			int  array_size_x, int  array_size_y  )
{
  ifstream  data_file2(file_name) ;
  if(data_file2.bad())
    {
      cerr << "Unable to open the file:" 
	   << file_name << "\n" ;  
      exit(8) ;
    }
  double pos_x, pos_y ;
  for(int i_y = 0 ; i_y < array_size_y ; i_y++ )
    {
      for (int i_x = 0 ; i_x < array_size_x ; i_x++ )
	{
	  data_file2 >> pos_x >> pos_y >> array1[i_x][i_y] ;
	  if(data_file2.bad())
	    {
	      cerr << "Unable to access the file:" 
		   << file_name << "\n" ;  
	      exit(8) ;
	    }
	}
    }
}
//-----
void input_array_splot(char file_name[], 
		       int **array1, 
		       int  array_size_x, int  array_size_y  )
{
  ifstream  data_file2(file_name) ;
  if(data_file2.bad())
    {
      cerr << "Unable to open the file:" 
	   << file_name << "\n" ;  
      exit(8) ;
    }
  //double pos_x, pos_y ;
  for(int i_y = 0 ; i_y < array_size_y ; i_y++ )
    {
      for (int i_x = 0 ; i_x < array_size_x ; i_x++ )
	{
	  data_file2 >> array1[i_x][i_y] ;
	  if(data_file2.bad())
	    {
	      cerr << "Unable to access the file:" 
		   << file_name << "\n" ;  
	      exit(8) ;
	    }
	}
    }
} 
//********** OUTPUT ***********************

void output_array_splot(char file_name[], 
			double **array1 , 
			int  array_size_x, int  array_size_y ,
                        double cell_size )
{
  ofstream  data_file2(file_name) ;
  if(data_file2.bad())
    {
      cerr << "Unable to open the file:" 
	   << file_name << "\n" ;  
      exit(8) ;
    }
  double pos_x, pos_y ;
  for(int i_y = 0 ; i_y < array_size_y ; i_y++ )
    {
      pos_y = (i_y + 0.5) * cell_size ;// --　セルは中央の位置を座標にとる
      for (int i_x = 0 ; i_x < array_size_x ; i_x++ )
	{
          pos_x = (i_x + 0.5) * cell_size ;
	  data_file2 << pos_x << "\t"
		     << pos_y << "\t"
		     << array1[i_x][i_y] << endl ;
	  if(data_file2.bad())
	    {
	      cerr << "Unable to access the file:" 
		   << file_name << "\n" ;  
	      exit(8) ;
	    }
	}
      data_file2  << endl ;
    }
  data_file2  << endl ;
}

void output_array_splot(char file_name[], 
			int **array1 , 
			int  array_size_x, int  array_size_y ,
                        double cell_size )
{
  ofstream  data_file2(file_name) ;
  if(data_file2.bad())
    {
      cerr << "Unable to open the file:" 
	   << file_name << "\n" ;  
      exit(8) ;
    }
  double pos_x, pos_y ;
  for(int i_y = 0 ; i_y < array_size_y ; i_y++ )
    {
      pos_y = (i_y + 0.5) * cell_size ;// --　セルは中央の位置を座標にとる
      for (int i_x = 0 ; i_x < array_size_x ; i_x++ )
	{
          pos_x = (i_x + 0.5) * cell_size ;
	  data_file2 << pos_x << "\t"
		     << pos_y << "\t"
		     << array1[i_x][i_y] << endl ;
	  if(data_file2.bad())
	    {
	      cerr << "Unable to access the file:" 
		   << file_name << "\n" ;  
	      exit(8) ;
	    }
	}
      data_file2  << endl ;
    }
  data_file2  << endl ;
}



//--- 09/Sep/2004 HDDの節約のため x,y 座標をプロットしない関数も用意
void  output_array_splot(char file_name[], 
			 int **array1 , 
			 int  array_size_x, int  array_size_y )
{
  ofstream  data_file2(file_name) ;
  if(data_file2.bad())
    {
      cerr << "Unable to open the file:" 
	   << file_name << "\n" ;  
      exit(8) ;
    }
  
  for(int i_y = 0 ; i_y < array_size_y ; i_y++ )
    {
      for (int i_x = 0 ; i_x < array_size_x ; i_x++ )
	{
	  data_file2  << array1[i_x][i_y] << endl ;
	  if(data_file2.bad())
	    {
	      cerr << "Unable to access the file:" 
		   << file_name << "\n" ;  
	      exit(8) ;
	    }
	}
      data_file2  << endl ;
    }
  data_file2  << endl ;
}


#define _FILEIO_PARTICLE_CC_
#endif
