//============================================================================
// Name        : WebAssembly.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iostream>
#include <fstream>
#include "getFreqRep.h"
#include "getFreqRep_emxAPI.h"
#include "getFreqRep_terminate.h"
#include "getFreqRep_types.h"

using namespace std;

/* Function Declarations */
static emxArray_real_T *argInit_d1000000x1_real_T(int size, string filename);

static void argInit_real_T(string filename, double *result_data);

static void main_getFreqRep(string filename);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : emxArray_real_T *
 */
static emxArray_real_T *argInit_d1000000x1_real_T(int size, string filename)
{
  emxArray_real_T *result;
  double *result_data;
  const int i = size;//2;
  int idx0;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreateND_real_T(1, &i);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  //for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    /**result_data[idx0] = */argInit_real_T(filename, result_data);
  //}
  return result;
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static void argInit_real_T(string filename, double *result_data)
{
	streampos begin,end;
	ifstream myfile (filename, ios::binary);

	if (myfile.is_open()) {
		/* ok, proceed with file operations */

		short int value;
		int i = 0;
		int op = 0;

		while (myfile.read(reinterpret_cast<char *>(&value), sizeof(value))){
			//cout << value << " ";
			if (op == 0){
				if (i > 1000){
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
		  for (int i = 0; i < 1000; i++){
			  myfile << result_data[i] << "\n";
		  }
		  myfile.close();
		}
		cout << "data read successfully!"<<endl;
		myfile.close();
	}
	else{
		cout << "Could not open file: " << filename << endl;
	}

	//return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_getFreqRep(string dataFileName)
{
	streampos size;

	ifstream file (dataFileName, ios::in|ios::binary|ios::ate);
	if (file.is_open()){
		size = file.tellg();
		size = size/2;
	}
  emxArray_creal_T *y;
  emxArray_creal_T *y_shifted;
  emxArray_real_T *x;
  emxInitArray_creal_T(&y, 1);
  emxInitArray_creal_T(&y_shifted, 1);

  /* Initialize function 'getFreqRep' input arguments. */
  /* Initialize function input argument 'x'. */
  x = argInit_d1000000x1_real_T(1000, dataFileName);

  /* Call the entry-point 'getFreqRep'. */
  getFreqRep(x, y, y_shifted);

  ofstream y_file ("y.txt");
  ofstream y_shifted_file ("y_shifted.txt");
  int y_size = y->size[0];
  int yshifted_size = y_shifted->size[0];
  cout << "Y size: " << y_size << endl;
  cout << "Y shifted size: " << yshifted_size << endl;
  if (y_file.is_open() && y_shifted_file.is_open()){
	  for (int i = 0; i < y_size; i++){
		  y_file << y->data[i].re << " " << y->data[i].im << "\n";
		  y_shifted_file << y_shifted->data[i].re << " " << y_shifted->data[i].im << "\n";
	  }
	  y_file.close();
	  y_shifted_file.close();
  }

  emxDestroyArray_creal_T(y_shifted);
  emxDestroyArray_creal_T(y);
  emxDestroyArray_real_T(x);
}



int main() {


	  /* The initialize function is being called automatically from your entry-point
	   * function. So, a call to initialize is not included here. */
	  /* Invoke the entry-point functions.
	You can call entry-point functions multiple times. */
	  main_getFreqRep("data.bin");
	  /* Terminate the application.
	You do not need to do this more than one time. */
	  getFreqRep_terminate();
	  cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
