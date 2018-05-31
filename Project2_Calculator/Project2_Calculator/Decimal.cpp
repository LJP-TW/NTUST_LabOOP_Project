#include "Calculator.h"
#include "Decimal.h"
#define OUTPUT_DIGITS 100

namespace 
{
	enum ErrorType
	{
		ERROR_CONSTRUCT = 0b00000001,
		ERROR_FACTORIAL = 0b00000010,
		ERROR_DIVISION	= 0b00000100,
		ERROR_POWER		= 0b00001000,
	};
}

Decimal::Decimal() : errorFlag(0), sign(true), numerator(string("0")), denominator(string("1"))
{
}

Decimal::Decimal(const string& number)
{
	Calculator calculator;
	string processedNum = calculator.process(number);
	// If the return is a number
	if (processedNum[0] == '-' || (processedNum[0] >= '0' && processedNum[0] <= '9'))
	{
		*this = Decimal(processedNum, 0);
	}
	else
	{
		this->errorFlag = ERROR_CONSTRUCT;
		this->sign = true;
		this->numerator = "1";
		this->denominator = "1";
	}
}

Decimal::Decimal(const string& number, int)
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
	this->errorFlag = other.getErrorFlag();
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
	this->errorFlag = other.getErrorFlag();
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

	newDecimal.reduceFraction();

	newDecimal.errorFlag = (this->errorFlag | other.errorFlag);

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

	newDecimal.reduceFraction();

	newDecimal.errorFlag = (this->errorFlag | other.errorFlag);

	return newDecimal;
}

const Decimal Decimal::operator *(const Decimal& other) const
{
	Decimal newDecimal;

	newDecimal.numerator = this->numerator * other.numerator;
	newDecimal.denominator = this->denominator * other.denominator;

	newDecimal.sign = !(this->getSign() ^ other.getSign());

	newDecimal.reduceFraction();

	newDecimal.errorFlag = (this->errorFlag | other.errorFlag);

	return newDecimal;
}

const Decimal Decimal::operator /(const Decimal& other) const
{
	Decimal newDecimal;

	newDecimal.numerator = this->numerator * other.denominator;
	newDecimal.denominator = this->denominator * other.numerator;

	if (newDecimal.denominator == Integer("0", 0))
	{
		newDecimal.errorFlag = ERROR_DIVISION;
		return newDecimal;
	}

	newDecimal.sign = !(this->getSign() ^ other.getSign());

	newDecimal.reduceFraction();

	newDecimal.errorFlag = (this->errorFlag | other.errorFlag);

	return newDecimal;
}

Decimal operator+(const Integer & lva, const Decimal & rva)
{
	Decimal d_lva(lva);
	Decimal newDecimal = d_lva + rva;

	return newDecimal;
}

Decimal operator-(const Integer & lva, const Decimal & rva)
{
	Decimal d_lva(lva);
	Decimal newDecimal = d_lva - rva;

	return newDecimal;
}

Decimal operator*(const Integer & lva, const Decimal & rva)
{
	Decimal d_lva(lva);
	Decimal newDecimal = d_lva * rva;

	return newDecimal;
}

Decimal operator/(const Integer & lva, const Decimal & rva)
{
	Decimal d_lva(lva);
	Decimal newDecimal = d_lva / rva;

	return newDecimal;
}

const Decimal Decimal::power(const Decimal& other) const
{
	Decimal newDecimal("1", 0);
	Decimal temp = *this;
	Integer powerTimes = other.numerator;
	Integer one("1", 0);
	Integer zero("0", 0);
	bool needRoot = false;

	if (other.denominator == Integer("2", 0))
	{
		needRoot = true;
	}

	// Only can handle case which is powered by multiple of 0.5
	if (other.denominator != Integer("1", 0) && !needRoot)
	{
		newDecimal.setErrorFlag(ERROR_POWER);
		return newDecimal;
	}

	// If something like (-1)^0.5
	if (!temp.sign && needRoot)
	{
		newDecimal.setErrorFlag(ERROR_POWER);
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
		newDecimal = newDecimal * temp;
		powerTimes = powerTimes - one;
	}

	if (needRoot)
	{
		newDecimal = squareRoot(newDecimal.getOutput());
	}

	newDecimal.reduceFraction();

	return newDecimal;
}

const Decimal Decimal::factorial() const
{
	Decimal newDecimal("1", 0);
	Integer temp = numerator;
	Integer zero("0", 0);
	Integer one("1", 0);

	// Not allow for nagetive decimal or denominator != 1
	if (!this->sign || this->denominator != one)
	{
		newDecimal.setErrorFlag(ERROR_FACTORIAL);
		return newDecimal;
	}

	while (temp != zero)
	{
		newDecimal.numerator = newDecimal.numerator * temp;
		temp = temp - one;
	}

	return newDecimal;
}

const Integer Decimal::dtoi() const
{
	Integer newInteger;

	newInteger = numerator / denominator;

	return newInteger;
}

const string Decimal::getOutput() const
{
	Integer integerPart = this->numerator / this->denominator;
	Integer remainder = this->numerator % this->denominator;

	string strPostfix(OUTPUT_DIGITS, '0');
	remainder.setNumber(remainder.getNumber() + strPostfix);

	remainder = remainder / this->denominator;

	if (this->numerator == Integer("0", 0))
	{
		return "0." + strPostfix;
	}
	
	string strPrefix(OUTPUT_DIGITS - remainder.getNumber().length(), '0');
	string sign = this->sign ? "" : "-";
	return sign + integerPart.getOutput() + '.' + strPrefix + remainder.getOutput();
}

const void Decimal::setInput(string formula)
{
	string processedNum;
	Calculator calculator;

	processedNum = calculator.process(formula);

	// If the return is a number
	if (processedNum[0] == '-' || (processedNum[0] >= '0' && processedNum[0] <= '9'))
	{
		*this = Decimal(processedNum, 0);
	}
	else
	{
		this->errorFlag = ERROR_CONSTRUCT;
		this->sign = true;
		this->numerator = "1";
		this->denominator = "1";
	}
}

const string Decimal::getErrorString() const
{
	if (this->isError())
	{
		switch (this->getErrorFlag())
		{
		case ERROR_CONSTRUCT:
			return "ERROR_CONSTRUCT";
		case ERROR_FACTORIAL:
			return "ERROR_FACTORIAL";
		case ERROR_DIVISION:
			return "ERROR_DIVISION";
		default:
			return "ERROR_INTEGER_UNKNOWN_ERROR";
		}
	}

	return "";
}

void Decimal::reduceFraction()
{
	Integer GCD = getGCD(numerator, denominator);
	Integer notExist("-1", 0);

	if (GCD != notExist)
	{
		numerator = numerator / GCD;
		denominator = denominator / GCD;
	}
}

Integer Decimal::getGCD(Integer a, Integer b) const
{
	/* a == numerator, b == denominator */
	Integer zero("0", 0);
	Integer one("1", 0);
	Integer GCD_notExist("-1", 0);

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
		for (char i = '9'; i >= '0'; --i)
		{
			divisor.setNumber(strNowDivisor + i);

			string strTemp = string(1, i);
			Integer integerTemp = divisor * Integer(strTemp, 0);

			if (integerTemp <= dividend)
			{
				dividend = dividend - integerTemp;
				divisor = divisor + Integer(strTemp, 0);

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

	return Decimal(quotient, 0);
}