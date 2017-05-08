#ifndef Matrix_H
#define Matrix_H
#include <vector>
#include "Complex.h"

#include <iostream>
#include <string>
using namespace std;

class Matrix{
	public:
		//Constructor Getter Setters
		explicit Matrix(void);
		explicit Matrix(int);
		explicit Matrix(int, vector<Complex>&);
		void size(int newSize);	//resize a matrix
		int size(void) const;	//get the size of the matrix
		void setValues(void);	//set values to 0
		void setValues(const Complex&, int); //set a single value to a single complex
		void setValues(vector<Complex>&);  //set all the values to a vector of complex
		Complex* getValues(void) const;	//get the pointer to the matrix
		//Operand Overload on itself
		Complex& operator()(int, int);	//Get complex at (row,col)
		Matrix operator-();	//Turns complexs in the array to -complex
		Matrix operator~();	//Turns complexs in the array to ~complex
		//Matrix operator=()
		//Operand Overloading with other Matrices
		Matrix operator+(const Matrix&);
		Matrix operator-(const Matrix&);
		Matrix operator*(const Matrix&);
		Matrix operator+=(const Matrix&);
		bool operator==(const Matrix&);
		//Operand Overloading with non-Matrices
		Matrix operator*(const Complex&);
		Matrix operator*(const double&);
		Matrix operator/(const Complex&);
		Matrix operator/(const double&);
		//Input/Output
		friend ostream &operator<<(ostream &, const Matrix &);
		friend istream &operator>>(istream &, Matrix &);

	private:
		bool getInit(void);	
		void setInit(bool);
		bool initialized;	//initialized is used for re-sizing matrixes
		int arraySize;	//size of array
		Complex* values;  //Pointer to array
};

void compareSize(const Matrix&, const Matrix&);	//Compares array size, can throw domain_error
Complex strToComplex(string); //Converts String to Complex, used in istream

//For when a Matrix is on the RHS
Matrix operator*(const Complex&, const Matrix&);
Matrix operator*(const double&, const Matrix&);

#endif