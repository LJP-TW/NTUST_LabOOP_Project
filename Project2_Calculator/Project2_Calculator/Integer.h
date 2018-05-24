// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#pragma once
#include "NumObject.h" 

class Integer: public NumObject
{
public:
	// Default set sign to positive, 0
	Integer();

	// Allow 1234 or -1234
	Integer(string& number);
	Integer(const Integer& other);
	virtual ~Integer();

	// Operator overloading
	const Integer& operator =(const Integer& other);
	const Integer& operator =(const string& number);
	const Integer operator +(const Integer& other) const;
	const Integer operator -(const Integer& other) const;
	const Integer operator *(const Integer& other) const;
	const Integer operator /(const Integer& other) const;
	friend ostream& operator <<(ostream& output, Integer& integer);
	

	// Only allow legal input
	friend istream& operator >>(istream& input, Integer& integer);

	// Accessor
	bool getSign() const { return sign; };
	string getNumber() const { return number; };

	// Mutator
	void setSign(bool sign) { this->sign = sign; };
	void setNumber(string number) { this->number = number; };

	// Other functions
	// Doesn't handle cases like 2^(3.5)
	const Integer power(const Integer& other) const;

	const Integer factorial();

	virtual const string getOutput() const;
	
protected:
	virtual const string getType() const { return "Integer"; };

private:
	// true  : positive
	// false : negative
	bool sign;

	// "1234" means number 1234
	string number;
};
