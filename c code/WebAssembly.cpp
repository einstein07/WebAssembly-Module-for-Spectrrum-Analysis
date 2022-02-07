//============================================================================
// Name        : WebAssembly.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "getFreqRep.h"
#include "getFreqRep_terminate.h"
#include "getFreqRep_types.h"

using namespace std;

/* Function Declarations */
static void argInit_2048x1_real_T(/**double*/ float result[2048], string filename);

static void argInit_real_T(double *result_data, string filename);

static void main_getFreqRep(void);
//static emxArray_real_T *argInit_d1000000x1_real_T(int size, string filename);

//static void argInit_real_T(string filename, double *result_data);

//static void main_getFreqRep(string filename);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : emxArray_real_T *
 */
static void argInit_2048x1_real_T(float/**double*/ result[2048], string filename){
	//argInit_real_T(result, filename);
	streampos begin,end;
	ifstream myfile (filename, ios::binary);

	if (myfile.is_open()) {
		// ok, proceed with file operations

		short int value;
		int i = 0;
		int op = 0;

		while (myfile.read(reinterpret_cast<char *>(&value), sizeof(value))){
			//cout << value << " ";
			if (op == 0){
				if (i == 2048){
					//cout << "overflow" << endl;
				}
				else{
					result[i] = value;
					i++;
					op = 1;
				}
			}
			else{
				op = 0;
			}
		}
		ofstream outfile ("input_data.txt");
		cout << "data size: "<< i <<endl;
		if (outfile.is_open()){
		  for (int j = 0; j < i-1; j++){
			  outfile << result[j] << "\n";
		  }
		  outfile << result[(i-1)];
		  outfile.close();
		  printf( "data read successfully!\n" );
		}
		else{
			printf( "Could not open file: input_data.txt" );
		}
		myfile.close();
	}
	else{
		printf( "Could not open file: %s", filename );
	}
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static void argInit_real_T(double *result_data, string filename){
	streampos begin,end;
	ifstream myfile (filename, ios::binary);

	if (myfile.is_open()) {
		// ok, proceed with file operations

		short int value;
		int i = 0;
		int op = 0;

		while (myfile.read(reinterpret_cast<char *>(&value), sizeof(value))){
			//cout << value << " ";
			if (op == 0){
				if (i > 2048){
					//cout << "overflow" << endl;
				}
				else{
					result_data[i] = value;
					i++;
					op = 1;
				}
			}
			else{
				op = 0;
			}
		}
		ofstream myfile ("input_data.txt");

		if (myfile.is_open()){
		  for (int j = 0; j < i-1; j++){
			  myfile << result_data[j] << ", ";
		  }
		  myfile << result_data[(i-1)];
		  myfile.close();
		}
		printf( "data read successfully!\n" );
	}
	else{
		printf( "Could not open file: %s", filename );
	}

}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_getFreqRep(string dataFileName){
//	streampos size;
//
//	ifstream file (dataFileName, ios::in|ios::binary|ios::ate);
//	if (file.is_open()){
//		size = file.tellg();
//		size = size/2;
//	}
//
  /**double*/float x[2048];
  /**double*/float y[2048];
  /* Initialize function 'getFreqRep' input arguments. */
  /* Initialize function input argument 'x'. */
  /* Call the entry-point 'getFreqRep'. */
  argInit_2048x1_real_T(x, dataFileName);
  cout << "Performing fft" <<endl;
  float*  output = getFreqRep(x, y);
  cout << "FFT done" <<endl;
  ofstream y_file ("y.txt");
  int y_size = 2048;
  printf( "Y size: %d\n", y_size );
  if (y_file.is_open() ){
	  for (int i = 0; i < y_size; i++){
		  y_file << y[i] << "\n";
		  printf( "%f\n", *output);
		  (*output++);
	  }
	  y_file.close();
  }

}


int main() {


	  /* The initialize function is being called automatically from your entry-point
	   * function. So, a call to initialize is not included here. */
	  /* Invoke the entry-point functions.
	You can call entry-point functions multiple times. */
	main_getFreqRep("data.bin");
	  /* Terminate the application.
	You do not need to do this more than one time. */
	//  getFreqRep_terminate();
	  printf( "!!!Hello World!!!\n" ); // prints !!!Hello World!!!
	return 0;
}
