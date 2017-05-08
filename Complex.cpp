#include "Complex.h"
#include <iomanip>
using namespace std;

Complex::Complex(){
	//If nothing is given, set Complex to 0+0i
	setReal(0);
	setImag(0);
}

Complex::Complex(double r, double i){
	setReal(r);
	setImag(i);
}

void Complex::setReal(double r){
	real = r;
}

void Complex::setImag(double i){
	imag = i;
}

double Complex::getReal() const{
	return real;
}

double Complex::getImag() const{
	return imag;
}

//////////////

Complex Complex::operator+(const Complex &a){
	return Complex(getReal() + a.getReal(),getImag() + a.getImag());
}

Complex Complex::operator-(const Complex &a){
	return Complex(getReal() - a.getReal(),getImag() - a.getImag());
}

Complex Complex::operator*(const Complex &a){
	return Complex(getReal()*a.getReal()-a.getImag()*getImag(),
		getImag()*a.getReal()+getReal()*a.getImag());
}

Complex Complex::operator/(const Complex &a){
	return Complex((getReal()*a.getReal()+getImag()*a.getImag())/(a.getReal()*a.getReal()+a.getImag()*a.getImag()),
		(getImag()*a.getReal()-getReal()*a.getImag())/(a.getReal()*a.getReal()+a.getImag()*a.getImag()));
}

Complex Complex::operator+=(const Complex &a){
	setReal(real + a.getReal());
	setImag(imag + a.getImag());
	return *this;
}

bool Complex::operator==(const Complex &a){
	double r = (getReal() == a.getReal());
	double i = (getImag() == a.getImag());
	return (r * i);
}

/////////////////////

Complex Complex::operator-(){
	return Complex(-1*getReal(),-1*getImag());
}

Complex Complex::operator~(){
	return Complex(getReal(),-1*getImag());
}

/////////////////////

Complex Complex::operator+(const double a){
	return Complex(getReal() + a,getImag());
}

Complex Complex::operator-(const double a){
	return Complex(a - getReal(),-1 * getImag());
}

Complex Complex::operator*(const double a){
	return Complex(a * getReal(),a * getImag());
}

Complex Complex::operator/(const double a){
	return Complex((a*getReal())/(getReal()*getReal()+getImag()*getImag()),
		(-1*a*getImag())/(getReal()*getReal()+getImag()*getImag()));
}

Complex Complex::operator+=(const double a){
	setReal(real + a);
	return *this;
}

////////////////

ostream &operator<<(ostream &output, const Complex &comp){
	string imag = "";
	//determine if there is a imag componenet
	if(comp.getImag() != 0){
		//determine if there is a real component
		if(comp.getReal() == 0){
			//if no real, check if there is an i or -i
			if(comp.getImag() == 1){
				output << "i";
			} else if(comp.getImag() == -1){
				output << "-i";
			} else {
				output << comp.getImag() << "i";
			}
		} else {
			//if real, determine if i is either +i, -i
			if(comp.getImag() == 1){
				output << comp.getReal() << "+i";
			} else if(comp.getImag() == -1){
				output << comp.getReal() << "-i";
			} else {
				//determine if i is negative or positive
				if(comp.getImag() < 0){
					output << comp.getReal() << comp.getImag() << "i";
				} else {
					output << comp.getReal() << "+" << comp.getImag() << "i";
				}
			}
		}
	} else {
		output << comp.getReal();
	}
	return output;
}

istream &operator>>(istream &input, Complex &comp){
	//Set up variables
	char letter = ' ';
	string compStr = "";
	//Get the first non-space number
	input.get(letter);
	while(letter == ' '){
		input.get(letter);
	}
	//get to the next space
	while(letter != ' ' && letter != '\n'){
		compStr = compStr + letter;
		input.get(letter);
	}
	//determine if there are 1 or 2 parts
	string real = "";
	string imag = "";
	double realNum = 0;
	double imagNum = 0;
	
	if(compStr.find("+") != std::string::npos){
		//If there is +, there is definitely two components
		size_t pos = compStr.find("+");
		string first = compStr.substr(0,pos);
		string second = compStr.substr(pos+1);
		if(first.back() == 'i'){
			imag = first.substr(0,first.size()-1);
			real = second;
		} else {
			real = first;
			imag = second.substr(0,second.size()-1);
		}
		realNum = stod(real);
		if(imag == "-"){
			imag = "-1";
		}
		imagNum = stod(imag);
	} else if(compStr.substr(1).find("-") != std::string::npos){
		//If there is - component that isn't the first, there is definitely two components
		size_t pos = compStr.substr(1).find("-");
		string first = compStr.substr(0,pos+1);
		string second = compStr.substr(pos+1);
		if(first.back() == 'i'){
			imag = first.substr(0,first.size()-1);
			real = second;
		} else {
			real = first;
			imag = second.substr(0,second.size()-1);
		}
		realNum = stod(real);
		if(imag == "-"){
			imag = "-1";
		}
		imagNum = stod(imag);
	} else {
		//Otherwise there is only one component
		if(compStr.back() == 'i'){
			//If there is an i, it's imaginary
			imag = compStr.substr(0,compStr.size()-1);
			if(imag == "-"){
				imag = "-1";
			} else if(imag == ""){
				imag = "1";
			}
			imagNum = stod(imag);
		} else {
			//otherwise it's real
			real = compStr;
			realNum = stod(real);
		}
	}
	//Convert it to a Complex Class
	comp.setReal(realNum);
	comp.setImag(imagNum);
	return input;
}

/////////////////

Complex operator+(const double &a, const Complex &b){
	return Complex(a + b.getReal(),b.getImag());
}

Complex operator-(const double &a, const Complex &b){
	return Complex(a - b.getReal(),-1 * b.getImag());
}

Complex operator*(const double &a, const Complex &b){
	return Complex(a * b.getReal(),a * b.getImag());
}

Complex operator/(const double &a, const Complex &b){
	return Complex((a*b.getReal())/(b.getReal()*b.getReal()+b.getImag()*b.getImag()),
		(-1*a*b.getImag())/(b.getReal()*b.getReal()+b.getImag()*b.getImag()));
}