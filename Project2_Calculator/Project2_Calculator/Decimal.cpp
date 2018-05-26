// Student ID: B10615043
// Date: April 6, 2018
// Last Update: April 7, 2018
// Problem statement: This C++ header to implement class .
#include "Decimal.h"

Decimal::Decimal() : errorFlag(0), sign(true), numerator(string("0")), denominator(string("1"))
{
}

Decimal::Decimal(const string& number)
{
	int i = 0;

	// Handling errorFlag
	this->errorFlag = 0;

	// Handling sign
	if (number[i] == '-')
	{
		++i;
		this->sign = false;
	}
	else if (number[i] == '+')
	{
		++i;
		this->sign = true;
	}
	else
	{
		this->sign = true;
	}

	// Handling numerator and denominator
	string strNumerator = "";
	string strDenominator = "1";

	while (number[i] != '.' && number[i])
	{
		strNumerator += number[i++];
	}

	// For case like 1234 or -1234 (no dot)
	if (!number[i])
	{
		strDenominator = "1";
	}

	// For case like 1234.5678 or -1234.5678
	else
	{
		++i;
		while (number[i])
		{
			strNumerator += number[i++];
			strDenominator += '0';
		}
	}

	this->numerator = strNumerator;
	this->denominator = strDenominator;
}

Decimal::Decimal(const Integer& other)
{
	const NumObject* pt = &other;
	this->errorFlag = pt->getError();
	this->sign = other.getSign();
	this->numerator = other.getNumber();
	this->numerator.setSign(true);
	this->denominator = "1";
}

Decimal::Decimal(const Decimal& other)
{
	this->errorFlag = other.errorFlag;
	this->sign = other.sign;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
}

Decimal::~Decimal()
{
}

const Decimal& Decimal::operator =(const Decimal& other)
{
	this->errorFlag = other.errorFlag;
	this->sign = other.sign;
	this->numerator = other.numerator;
	this->denominator = other.denominator;

	return *this;
}

const Decimal& Decimal::operator =(const Integer& other)
{
	const NumObject* pt = &other;
	this->errorFlag = pt->getError();
	this->sign = other.getSign();
	this->numerator = other;
	this->numerator.setSign(true);
	this->denominator = "1";

	return *this;
}

const Decimal& Decimal::operator =(const string& number)
{
	int i = 0;

	// Handling errorFlag
	this->errorFlag = 0;

	// Handling sign
	if (number[i] == '-')
	{
		++i;
		this->sign = false;
	}
	else if (number[i] == '+')
	{
		++i;
		this->sign = true;
	}
	else
	{
		this->sign = true;
	}

	// Handling numerator and denominator
	string strNumerator = "";
	string strDenominator = "1";

	while (number[i] != '.' && number[i])
	{
		strNumerator += number[i++];
	}

	// For case like 1234 or -1234 (no dot)
	if (!number[i])
	{
		strDenominator = "1";
	}
	// For case like 1234.5678 or -1234.5678
	else
	{
		++i;
		while (number[i])
		{
			strNumerator += number[i++];
			strDenominator += '0';
		}
	}

	this->numerator = strNumerator;
	this->denominator = strDenominator;

	return *this;
}

const Decimal Decimal::operator +(const Decimal& other) const
{
	Decimal newDecimal;

	Integer thisNumerator = this->numerator;
	thisNumerator.setSign(this->getSign());

	Integer otherNumerator = other.numerator;
	otherNumerator.setSign(other.getSign());

	newDecimal.numerator = thisNumerator * other.denominator + otherNumerator * this->denominator;
	newDecimal.denominator = this->denominator * other.denominator;

	newDecimal.sign = newDecimal.numerator.getSign();
	newDecimal.numerator.setSign(true);

	return newDecimal;
}

const Decimal Decimal::operator -(const Decimal& other) const
{
	Decimal newDecimal;

	Integer thisNumerator = this->numerator;
	thisNumerator.setSign(this->getSign());

	Integer otherNumerator = other.numerator;
	otherNumerator.setSign(other.getSign());

	newDecimal.numerator = thisNumerator * other.denominator - otherNumerator * this->denominator;
	newDecimal.denominator = this->denominator * other.denominator;

	newDecimal.sign = newDecimal.numerator.getSign();
	newDecimal.numerator.setSign(true);

	return newDecimal;
}

const Decimal Decimal::operator *(const Decimal& other) const
{
	Decimal newDecimal;

	newDecimal.numerator = this->numerator * other.numerator;
	newDecimal.denominator = this->denominator * other.denominator;

	newDecimal.sign = !(this->getSign() ^ other.getSign());

	return newDecimal;
}

const Decimal Decimal::operator /(const Decimal& other) const
{
	Decimal newDecimal;

	newDecimal.numerator = this->numerator * other.denominator;
	newDecimal.denominator = this->denominator * other.numerator;

	newDecimal.sign = !(this->getSign() ^ other.getSign());

	return newDecimal;
}

istream& operator >>(istream& input, Decimal& decimal)
{
	string number;
	input >> number;
	decimal = number;

	return input;
}

const Integer Decimal::factorial()
{
	Integer newInteger = "1";
	Integer temp = numerator;
	Integer zero = "0";
	Integer one = "1";

	// Not allow for nagetive decimal or denominator != 1
	if (!this->sign || this->denominator != one)
	{
		newInteger.setError(ERROR_FACTORIAL);
		return newInteger;
	}

	while (temp != zero)
	{
		newInteger = newInteger * temp;
		temp = temp - one;
	}

	return newInteger;
}

const string Decimal::getOutput() const
{
	Integer integerPart = this->numerator / this->denominator;
	Integer remainder = this->numerator % this->denominator;

	string strPostfix(100, '0');
	remainder.setNumber(remainder.getNumber() + strPostfix);

	remainder = remainder / this->denominator;

	string strPrefix(100 - remainder.getNumber().length(), '0');
	string sign = this->sign ? "" : "-";
	return sign + integerPart.getOutput() + '.' + strPrefix + remainder.getOutput();
}