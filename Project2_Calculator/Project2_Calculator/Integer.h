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

	// Accessor
	virtual const char getErrorFlag() const { return errorFlag; };
	bool getSign() const { return sign; };
	string getNumber() const { return number; };

	// Mutator
	virtual const void setErrorFlag(char error) { errorFlag = error; };
	void setSign(bool sign) { this->sign = sign; };
	void setNumber(string number) { this->number = number; };

	// Other functions
	// Doesn't handle cases like 2^(3.5)
	const Integer power(const Integer& other) const;

	const Integer factorial() const;

	virtual const string getOutput() const;
	virtual const void setInput(string formula);

	virtual const bool isError() const { return errorFlag ? true : false; };
	virtual const string getErrorString() const;

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