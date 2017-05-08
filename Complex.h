#ifndef Complex_H
#define Complex_H

#include <iostream>
#include <string>
using namespace std;

class Complex{
	public:
		//Constructors, Getters, Setters
		explicit Complex(void);
		explicit Complex(double r, double i);
		void setReal(double r);
		void setImag(double i);
		double getReal(void) const;
		double getImag(void) const;
		//Operand Overloading with other Complex numbers
		Complex operator+(const Complex &a);
		Complex operator-(const Complex &a);
		Complex operator*(const Complex &a);
		Complex operator/(const Complex &a);
		Complex operator+=(const Complex &a);
		bool operator==(const Complex &a);
		//Operand Overloading with just itself
		Complex operator-();	//returns opposite values of real and imaginary
		Complex operator~();	//returns opposite values of imaginary
		//Operand Overloading with doubles
		Complex operator+(const double a);
		Complex operator-(const double a);
		Complex operator*(const double a);
		Complex operator/(const double a);
		Complex operator+=(const double a);
		//Input/Output
		friend ostream &operator<<(ostream &, const Complex &);
		friend istream &operator>>(istream &, Complex &);
	private:
		double real;
		double imag;
};
//Primitives on LHS
Complex operator+(const double &a, const Complex &b);
Complex operator-(const double &a, const Complex &b);
Complex operator*(const double &a, const Complex &b);
Complex operator/(const double &a, const Complex &b);

#endif