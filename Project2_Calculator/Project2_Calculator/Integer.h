// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#pragma once
#include "NumObject.h" 

class Integer : public NumObject
{
public:
	// Default set sign to positive, 0
	Integer();

	// Allow "1234" or "-1234" or "1234.5678" (will save as "1234")
	// also "123 + 456"
	Integer(const string& number);

	// Allow "1234" or "-1234" or "1234.5678" (will save as "1234")
	// but don't allow "123 + 456"
	Integer(const string& number, int);
	Integer(const Integer& other);
	virtual ~Integer();

	// Operator overloading
	const Integer& operator =(const Integer& other);
	const Integer& operator =(const string& number);
	const Integer operator +(const Integer& other) const;
	const Integer operator -(const Integer& other) const;
	const Integer operator *(const Integer& other) const;
	const Integer operator /(const Integer& other) const;
	const Integer operator %(const Integer& other) const;

	const bool operator >(const Integer& other) const;
	const bool operator >=(const Integer& other) const;
	const bool operator <(const Integer& other) const;
	const bool operator <=(const Integer& other) const;
	const bool operator ==(const Integer& other) const;
	const bool operator !=(const Integer& other) const;

	friend ostream& operator <<(ostream& output, const Integer& integer);

	// Only allow legal input
	friend istream& operator >>(istream& input, Integer& integer);

	// Accessor
	virtual const void setError(char error) { errorFlag = error; };
	bool getSign() const { return sign; };
	string getNumber() const { return number; };

	// Mutator
	virtual const char getError() const { return errorFlag; };
	void setSign(bool sign) { this->sign = sign; };
	void setNumber(string number) { this->number = number; };

	// Other functions
	// Doesn't handle cases like 2^(3.5)
	const Integer power(const Integer& other) const;

	const Integer factorial() const;

	virtual const string getOutput() const;

	virtual const bool isError() const { return errorFlag ? true : false; };

protected:
	virtual const string getType() const { return "Integer"; };

private:
	char errorFlag;

	// true  : positive
	// false : negative
	bool sign;

	// "1234" means number 1234
	string number;

	// Other Functions
	// Remove the 0 prefix
	void removeZeroPrefix();

	// Helper Functions
	// Invert a char array to string
	// e.g.
	// target[0] = 'h' , [1] = 'e', [2] = 'G'
	// output string = "Geh"
	string invertToString(char *target, int size) const;
};