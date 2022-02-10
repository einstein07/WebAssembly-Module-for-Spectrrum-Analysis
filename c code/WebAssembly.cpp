//============================================================================
// Name        : WebAssembly.cpp
// Author      : Sindiso Mkhatshwa
// Version     :
// Copyright   : Your copyright notice
// Description : This file reads in satellite data ( from a binary file ), and
//				 performs a FFT on the data, and then writes the results to
//				 a results text file.
//============================================================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h> //for benchmarking purposes
#include "getFreqRep.h"
#include "getFreqRep_terminate.h"
#include "getFreqRep_types.h"

using namespace std;
const int SIZE_ = 2048;
/* Function Declarations */
static void argInit_2048x1_real_T(float *result, string filename);

static void argInit_real_T(float *result_data, string filename);

static void main_getFreqRep(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : emxArray_real_T *
 */
static void argInit_2048x1_real_T(float *result, string filename){
	streampos begin,end;
	ifstream myfile (filename, ios::binary);

	if (myfile.is_open()) {
		// ok, proceed with file operations

		short int value;
		int i = 0;
		int op = 0;

		while (myfile.read(reinterpret_cast<char *>(&value), sizeof(value))){
			if (op == 0){
				if (i == SIZE_){
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
static void argInit_real_T(float *result_data, string filename){
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

  float x[SIZE_];
  float y[SIZE_];
  /* Initialize function 'getFreqRep' input arguments. */
  /* Initialize function input argument 'x'. */
  /* Call the entry-point 'getFreqRep'. */
  argInit_2048x1_real_T(x, dataFileName);

  clock_t start = clock();
  float*  output = getFreqRep(x, y);
  clock_t end = clock();
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time taken %f seconds\n", time_spent);


  ofstream y_file ("y.txt");
  int y_size = SIZE_;
  printf( "Y size: %d\n", y_size );
  if (y_file.is_open() ){
	  for (int i = 0; i < y_size; i++){
		  y_file << y[i] << "\n";
		  (*output++);
	  }
	  y_file.close();
  }

}


int main() {


	/* The initialize function is being called automatically from your entry-point
	 * function. So, a call to initialize is not included here.
	 * Invoke the entry-point functions.
	 * You can call entry-point functions multiple times. */
	main_getFreqRep("data.bin");
	/* Terminate the application.You do not need to do this more than one time. */
	getFreqRep_terminate();
	printf( "Exiting gracefully\n" ); // prints !!!Hello World!!!
	return 0;
}
