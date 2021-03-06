#pragma once
#include "NumObject.h"
#include "Integer.h"

class Decimal : public NumObject
{
public:
	// Default set sign to positive, 0/1
	Decimal();

	// Allow "1234" or "-1234" or "1234.5678"
	// also "123 + 456"
	Decimal(const string& number);

	// Allow "1234" or "-1234" or "1234.5678"
	// but don't allow "123 + 456"
	Decimal(const string& number, int);
	Decimal(const Integer& other);
	Decimal(const Decimal& other);
	virtual ~Decimal();

	// Operator overloading
	const Decimal& operator =(const Decimal& other);
	const Decimal& operator =(const Integer& other);
	const Decimal& operator =(const string& number);
	const Decimal operator +(const Decimal& other) const;
	const Decimal operator -(const Decimal& other) const;
	const Decimal operator *(const Decimal& other) const;
	const Decimal operator /(const Decimal& other) const;

	friend Decimal operator + (const Integer& lva, const Decimal& rva);
	friend Decimal operator - (const Integer& lva, const Decimal& rva);
	friend Decimal operator * (const Integer& lva, const Decimal& rva);
	friend Decimal operator / (const Integer& lva, const Decimal& rva);

	// Accessor
	virtual const char getErrorFlag() const { return errorFlag; };
	bool getSign() const { return sign; };
	Integer getNumerator() const { return numerator; };
	Integer getDenominator() const { return denominator; };

	// Mutator
	virtual const void setErrorFlag(char error) { errorFlag = error; };
	void setSign(bool sign) { this->sign = sign; };
	void setNumerator(Integer numerator) { this->numerator = numerator; };
	void setDenominator(Integer denominator) { this->denominator = denominator; };

	// Other functions
	// Allow 2.5^(2) or 2.5^(2.5)
	const Decimal power(const Decimal& other) const;

	// Allow (3.0)!
	// Not allow (3.5)!
	// factorial() always returns Integer
	const Decimal factorial() const;

	// Convert Decimal to Integer
	const Integer dtoi() const;

	virtual const string getOutput() const;
	virtual const void setInput(string formula);

	virtual const bool isError() const { return errorFlag ? true : false; };
	virtual const string getErrorString() const;

protected:
	virtual const string getType() const { return "Decimal"; };

private:
	char errorFlag;

	// true  : positive
	// false : negative
	bool sign;

	// Take 37/4 as example:
	// numerator   : 37
	// denominator : 4
	Integer numerator;
	Integer denominator;

	// Other functions
	// To reduce a fraction to lowest terms
	void reduceFraction();

	// Helper functions
	// reduceFraction()
	//   - getGCD()
	//     To get greatest common divisor
	Integer getGCD(Integer a, Integer b) const;

	// power
	//   - squareRoot()
	Decimal squareRoot(string target) const;
};