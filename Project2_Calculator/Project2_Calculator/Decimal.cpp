// Student ID: B10615043
// Date: April 6, 2018
// Last Update: April 7, 2018
// Problem statement: This C++ header to implement class .
#include "Decimal.h"
#define OUTPUT_DIGITS 100

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

	reduceFraction();
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

	reduceFraction();

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

	reduceFraction();

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

ostream& operator <<(ostream& output, const Decimal& decimal)
{
	// Output to 100 decimal digit
	output << decimal.getOutput();

	return output;
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

const Decimal Decimal::power(const Decimal& other) const
{
	Decimal newDecimal = "1";
	Decimal temp = *this;
	Integer powerTimes = other.numerator;
	Integer one = "1";
	Integer zero = "0";
	bool needRoot = false;

	if (other.denominator == Integer("2"))
	{
		needRoot = true;
	}

	// Only can handle case which is powered by multiple of 0.5
	if (other.denominator != Integer("1") && !needRoot)
	{
		newDecimal.setError(ERROR_POWER);
		return newDecimal;
	}

	// If newDecimal is powered by nagetive number
	if (!other.sign)
	{
		Integer intTemp = temp.denominator;
		temp.denominator = temp.numerator;
		temp.numerator = intTemp;
	}

	while (powerTimes != zero)
	{
		newDecimal = newDecimal * (*this);
		powerTimes = powerTimes - one;
	}

	if (needRoot)
	{
		newDecimal = squareRoot(newDecimal.getOutput());
	}

	return newDecimal;
}

Decimal Decimal::squareRoot(string target) const
{
	// Using long division method
	Decimal newDecimal;
	Integer dividend;
	Integer divisor;
	string quotient;
	int dotPos;
	int nowPos = 0;
	int digits = 0;
	bool afterDot = false;

	// Preprocess the target string
	dotPos = target.find('.');
	if (dotPos != string::npos)
	{
		if ((target.size() - dotPos) % 2 == 0)
		{
			target += '0';
		}

		if (dotPos % 2 == 1)
		{
			target.insert(0, "0");
			dotPos += 1;
		}

		dotPos /= 2;
	}
	else
	{
		if (target.size() % 2 == 1)
		{
			target.insert(0, "0");
		}

		dotPos = target.size() / 2;
	}
	target.erase(dotPos * 2, 1);

	// Long division
	// Init
	dividend.setNumber("");
	divisor.setNumber("");

	// main loop
	while (digits != OUTPUT_DIGITS)
	{
		string strNowDivisor;
		// If this position is for digits
		if (nowPos == dotPos)
		{
			quotient += '.';
			afterDot = true;
			nowPos += 1;
			continue;
		}

		// If there are number in target
		if (target.size())
		{
			dividend.setNumber(dividend.getNumber() + target.substr(0, 2));
			target.erase(0, 2);
		}
		// Else, fill 00
		else
		{
			dividend.setNumber(dividend.getNumber() + "00");
		}

		// Find the correct divisor
		strNowDivisor = divisor.getNumber();
		for (char i = '0'; i <= '9'; ++i)
		{
			bool foundDivisor = false;
			divisor.setNumber(strNowDivisor + i);

			string strTemp = "" + i;
			Integer integerTemp = divisor * Integer(strTemp);

			if (integerTemp >= dividend)
			{
				foundDivisor = true;

				--i;
				divisor.setNumber(strNowDivisor + i);

				strTemp = "" + i;
				integerTemp = divisor * Integer(strTemp);
			}

			if (foundDivisor || i == '9')
			{
				dividend = dividend - integerTemp;
				divisor = divisor + Integer(strTemp);

				quotient += i;
				++nowPos;
				if (afterDot)
				{
					++digits;
				}
				break;
			}
		}
	}

	return Decimal(quotient);
}

void Decimal::reduceFraction()
{
	Integer GCD = getGCD(numerator, denominator);
	Integer notExist = "-1";

	if (GCD != notExist)
	{
		numerator = numerator / GCD;
		denominator = denominator / GCD;
	}

}

Integer Decimal::getGCD(Integer a, Integer b) const
{
	/* a == numerator, b == denominator */
	Integer zero = "0";
	Integer one = "1";
	Integer GCD_notExist = "-1";

	while (1)
	{
		if (a == one || b == one)
		{
			return GCD_notExist;
		}
		if (a == zero)
		{
			return b;
		}
		if (b == zero)
		{
			return a;
		}

		if (a > b)
		{
			a = a % b;
		}
		else if (a == b)
		{
			return a;
		}
		else
		{
			b = b % a;
		}
	}
}