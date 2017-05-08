#include "Matrix.h"
#include <iomanip>
#include <stdexcept>
#include <cstring>
using namespace std;

Matrix::Matrix(void){
	//if nothing is given, make it a 1x1 with 0 values
	setInit(false);
	size(1);
	setInit(true);
	setValues();
}

Matrix::Matrix(int num){
	//if just the size is given, make every complex zero
	setInit(false);
	size(num);
	setInit(true);
	setValues();
}

Matrix::Matrix(int num, vector<Complex>& newValues){
	//if given size and values, add them
	setInit(false);
	size(num);
	setInit(true);
	setValues(newValues);
}

void Matrix::size(int newSize){
	//Check if newSize is acceptable
	if(newSize < 1){
		throw std::invalid_argument( "invalid array size" );
	}
	//Create the new array of blank values
	Complex* newValues = new Complex[newSize*newSize];
	//Check if first time making array
	if(initialized){
		//if the newsize is bigger, upgrade
		if(newSize > arraySize){
			Complex blank;
			for(int i = 0; i < newSize; i++){
				for(int j = 0; j < newSize; j++){
					if(i < arraySize && j < arraySize){
						newValues[newSize*i+j] = values[arraySize*i+j];
					} else {
						newValues[newSize*i+j] = blank;
					}
				}
			}
		//If the newsize is smaller, downgrade
		} else if(newSize < arraySize){
			for(int i = 0; i < newSize; i++){
				for(int j = 0; j < newSize; j++){
					newValues[newSize*i+j] = values[arraySize*i+j];
				}
			}
		}
		//deletes values in old arrays, prevent memory leaks
		delete[] values;
	}
	//assign new Size and Values
	values = newValues;
	arraySize = newSize;
}

int Matrix::size(void) const{
	return arraySize;
}

void Matrix::setValues(void){
	Complex c;
	for(int i = 0; i < arraySize*arraySize; i++){
		values[i] = c;
	}
}

void Matrix::setValues(const Complex& c, int i){
	values[i] = c;
}

void Matrix::setValues(vector<Complex>& newValues){
	for(int i = 0; i < arraySize*arraySize; i++){
		values[i] = newValues.at(i);
	}
}

Complex* Matrix::getValues(void) const{
	return values;
}

///////////////////////

Complex& Matrix::operator()(int row, int col){
	if((row >= arraySize)||(col >= arraySize)){
		throw std::out_of_range( "out of range" );
	}
	return values[row*arraySize + col];
}

Matrix Matrix::operator-(){
	Matrix mat(this->size());
	for(int i = 0; i < (this->size()*this->size()); i++){
		mat.setValues(-1*(this->getValues()[i]),i);
	}
	return mat;
}

Matrix Matrix::operator~(){
	Matrix mat(this->size());
	for(int i = 0; i < (this->size()*this->size()); i++){
		mat.setValues(~(this->getValues()[i]),i);
	}
	return mat;
}

////////////////////////

Matrix Matrix::operator+(const Matrix& a){
	//check size
	compareSize(*this,a);
	Matrix mat(this->size());
	for(int i = 0; i < (this->size()*this->size()); i++){
		mat.setValues(this->getValues()[i] + a.getValues()[i],i);
	}
	return mat;
}

Matrix Matrix::operator-(const Matrix& a){
	//check size
	compareSize(*this,a);
	Matrix mat(this->size());
	for(int i = 0; i < (this->size()*this->size()); i++){
		mat.setValues(this->getValues()[i] - a.getValues()[i],i);
	}
	return mat;
}

Matrix Matrix::operator*(const Matrix& a){
	//Check size
	compareSize(*this,a);
	Matrix mat(this->size());
	//Variable setup
	int thisRow, aCol;
	Complex total;
	for(int i = 0; i < (this->size()*this->size()); i++){
		//thisRow is row of the matrix to multiple with
		thisRow = (i / (this->size()))*(this->size());
		//acol is the col of the matrix to multiple with
		aCol = i % (this->size());
		//reset total
		total.setReal(0);
		total.setImag(0);
		for(int j = 0; j < this->size(); j++){
			total += (this->getValues()[thisRow+j] * a.getValues()[aCol+this->size()*j]);
		}
		mat.setValues(total,i);
	}
	return mat;
}

Matrix Matrix::operator+=(const Matrix& a){
	compareSize(*this,a);
	for(int i = 0; i < (this->size()*this->size()); i++){
		this->setValues(this->getValues()[i] + a.getValues()[i],i);
	}
	return *this;
}

bool Matrix::operator==(const Matrix& a){
	if(!(this->size() == a.size())){
		return false;
	} 
	for(int i = 0; i < (this->size()*this->size()); i++){
		if(!(this->getValues()[i] == a.getValues()[i])){
			return false;
		}
	}
	return true;
}

//////////////////////////////

Matrix Matrix::operator*(const Complex& c){
	Matrix mat(this->size());
	for(int i = 0; i < (this->size()*this->size()); i++){
		mat.setValues(this->getValues()[i] * c,i);
	}
	return mat;
}

Matrix Matrix::operator*(const double& d){
	Complex c(d,0);
	Matrix mat(this->size());
	for(int i = 0; i < (this->size()*this->size()); i++){
		mat.setValues(this->getValues()[i] * c,i);
	}
	return mat;
}

Matrix Matrix::operator/(const Complex& c){
	Matrix mat(this->size());
	for(int i = 0; i < (this->size()*this->size()); i++){
		mat.setValues(this->getValues()[i] / c,i);
	}
	return mat;
}

Matrix Matrix::operator/(const double& d){
	Complex c(d,0);
	Matrix mat(this->size());
	for(int i = 0; i < (this->size()*this->size()); i++){
		mat.setValues(this->getValues()[i] / c,i);
	}
	return mat;
}

////////////

ostream &operator<<(ostream &output, const Matrix& mat){
	for(int i = 0; i < mat.size(); i++){
		for(int j = 0; j < mat.size(); j++){
			output << mat.getValues()[mat.size()*i+j] << " ";
		}
		output << endl;
	}
	return output;
}

istream &operator>>(istream &input, Matrix& mat){
	//Get the line of text
	string text;
	getline(input, text);
	//check text exists
	if(text == ""){
		getline(input, text);
	}
	//Set up to divide new Complex numbers
	int len = text.size();
	int i = 0;
	int matCounter = 0;
	Complex c;
	string complexText;
	//While there is text left
	while(i < len){
		complexText = ""; //reset Complex text
		if((text[i] != ' ') && (i < len)){  //Check if end of line or space
			while((text[i] != ' ') && (i < len)){  //Same thing, but in the loop
				complexText = complexText + text[i];  //Make the textfile for complex
				i++;
			}
			c = strToComplex(complexText);  //turn the string into a complex value
			mat.setValues(c,matCounter);  //put the complex value into the array
			matCounter++;  //go to the next complex value
		}
		//move pointer by one
		i++;
	}
	return input;
}

/////////////////////////////////

bool Matrix::getInit(void){
	return initialized;
}

void Matrix::setInit(bool b){
	initialized = b;
}

////////////////////////////

void compareSize(const Matrix& mat1, const Matrix& mat2){
    if(mat1.size() != mat2.size()){
    	throw std::domain_error( "array sizes don't match" );
    }
}

Complex strToComplex(string text){
	int len = text.size();
	//Set up to divide new Complex numbers
	int i = 0;
	bool setNeg = 0;
	string realStr = "";
	string imagStr = "";
	double realNum = 0;
	double imagNum = 0;
	//Find Real Part
	if(text[i] == '-'){
		setNeg = 1;
	}
	while((text[i] != '+') && (text[i] != '-')){
		realStr = realStr + text[i];
		i++;
	}
	realNum = stod(realStr);
	if(setNeg){
		realNum = -1*realNum;
	}
	//Find imag Part
	setNeg = 0;
	if(text[i] == '-'){
		setNeg = 1;
	}
	i++;
	while((text[i] != 'i')){
		imagStr = imagStr + text[i];
		i++;
	}
	imagNum = stod(imagStr);
	if(setNeg){
		imagNum = -1*imagNum;	
	}
	//Create complex number
	Complex c;
	c.setReal(realNum);
	c.setImag(imagNum);
	return c;
}

//////////////////////////

Matrix operator*(const Complex& c, const Matrix& m){
	Matrix mat(m.size());
	for(int i = 0; i < (m.size()*m.size()); i++){
		mat.setValues(m.getValues()[i] * c,i);
	}
	return mat;
}

Matrix operator*(const double& d, const Matrix& m){
	Complex c(d,0);
	Matrix mat(m.size());
	for(int i = 0; i < (m.size()*m.size()); i++){
		mat.setValues(m.getValues()[i] * c,i);
	}
	return mat;
}