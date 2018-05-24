// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#pragma once
#include "NumObject.h"
#include "Integer.h"

class Decimal : public NumObject
{
public:
	// Default set sign to positive, 0/1
	Decimal();

	// Allow 1234 or 1234.5678 or -1234 or -1234.5678
	Decimal(const string& number);
	Decimal(const Integer& other);
	Decimal(const Decimal& other);
	virtual ~Decimal();

	// Operator overloading
	const Decimal& operator =(const Decimal& other);
	const Decimal& operator =(const Integer& other);
	const Decimal& operator =(const string& number);
	const Decimal operator +(const Decimal& other) const;
	const Decimal operator +(const Integer& other) const;
	const Decimal operator -(const Decimal& other) const;
	const Decimal operator -(const Integer& other) const;
	const Decimal operator *(const Decimal& other) const;
	const Decimal operator *(const Integer& other) const;
	const Decimal operator /(const Decimal& other) const;
	const Decimal operator /(const Integer& other) const;
	friend ostream& operator <<(ostream& output, Decimal& decimal);

	// Only allow legal input
	friend istream& operator >>(istream& input, Decimal& decimal);

	const bool operator >(const Decimal& other) const;
	const bool operator >(const Integer& other) const;
	const bool operator >=(const Decimal& other) const;
	const bool operator >=(const Integer& other) const;
	const bool operator <(const Decimal& other) const;
	const bool operator <(const Integer& other) const;
	const bool operator <=(const Decimal& other) const;
	const bool operator <=(const Integer& other) const;
	const bool operator ==(const Decimal& other) const;
	const bool operator ==(const Integer& other) const;

	// Accessor
	bool getSign() const { return sign; };
	Integer getNumerator() const { return numerator; };
	Integer getDenominator() const { return denominator; };

	// Mutator
	void setSign(bool sign) { this->sign = sign; };
	void setNumerator(Integer numerator) { this->numerator = numerator; };
	void setDenominator(Integer denominator) { this->denominator = denominator; };

	// Other functions
	// Allow 2.5^(2) or 2.5^(2.5)
	const Decimal power(const Integer& other) const;
	const Decimal power(const Decimal& other) const;

	// Allow 2^(2.5) (powering a Integer)
	const Decimal powerInteger(const Integer& other) const;

	// Allow (3.0)!
	// Not allow (3.5)!
	// factorial() always returns Integer
	const Integer factorial();

	// Convert Decimal to Integer
	const Integer dtoi() const;

	virtual const string getOutput() const;

	virtual const bool isError() const;

protected:
	virtual const string getType() const { return "Decimal"; };

	// Accessor
	virtual const void setError(char error) { errorFlag = error; };

	// Mutator
	virtual const char getError() const { return errorFlag; };

private:
	enum ErrorType
	{

	};

	char errorFlag;

	// true  : positive
	// false : negative
	bool sign;

	// Take 37/4 as example:
	// numerator   : 37
	// denominator : 4
	Integer numerator;
	Integer denominator;
};