// Student ID: B10615043
// Date: April 6, 2018
// Last Update: April 7, 2018
// Problem statement: This C++ header to implement class .
#include "Calculator.h"
#include "Integer.h"
#define ASCII_BASE 48

namespace
{
	enum ErrorType
	{
		ERROR_CONSTRUCT = 0b00000001,
		ERROR_FACTORIAL = 0b00000010,
		ERROR_DIVISION = 0b00000100,
	};
}

Integer::Integer() : errorFlag(0), sign(true), number("0")
{
}

Integer::Integer(const string& number)
{
	Calculator calculator;
	string processedNum = calculator.process(number);
	// If the return is a number
	if (processedNum[0] == '-' || (processedNum[0] >= '0' && processedNum[0] <= '9'))
	{
		*this = Integer(processedNum, 0);
	}
	else
	{
		this->errorFlag = ERROR_CONSTRUCT;
		this->sign = true;
		this->number = "1";
	}
}

Integer::Integer(const string & number, int)
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

	// Handling number
	this->number = "";
	while (number[i] != 0 && number[i] != '.')
	{
		this->number += number[i++];
	}

	removeZeroPrefix();
}

Integer::Integer(const Integer& other)
{
	this->errorFlag = other.errorFlag;
	this->sign = other.sign;
	this->number = other.number;
}

Integer::~Integer()
{
}

const Integer& Integer::operator =(const Integer& other)
{
	this->errorFlag = other.errorFlag;
	this->sign = other.sign;
	this->number = other.number;

	return *this;
}

const Integer& Integer::operator =(const string& number)
{
	int i = 0;

	this->errorFlag = 0;

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

	this->number = "";
	while (number[i] != 0 && number[i] != '.')
	{
		this->number += number[i++];
	}

	removeZeroPrefix();

	return *this;
}

const Integer Integer::operator +(const Integer& other) const
{
	Integer newInteger; // Result

	// Determine do "+" or "-"
	// "+" + "+"
	if (this->sign && other.sign)
	{
		newInteger.sign = true;
		char* newArr;

		// If length of this bigger than other or same 
		if (*this >= other)
		{
			// Initial a new Array for newInteger
			newArr = new char[this->number.length() + 1];
			for (int i = 0; i < this->number.length() + 1; i++)
			{
				newArr[i] = 0;
			}

			// Process two value addition
			for (int i = 0; i < this->number.length(); i++)
			{
				if (i < other.number.length())
				{
					newArr[i] += this->number[this->number.length() - i - 1] - ASCII_BASE + other.number[other.number.length() - i - 1] - ASCII_BASE;
				}
				else
				{
					newArr[i] += this->number[this->number.length() - i - 1] - ASCII_BASE;
				}
				while (newArr[i] >= 10)
				{
					newArr[i] -= 10;
					newArr[i + 1]++;
				}
			}

			// Convert to string of newInteger "number"
			newInteger.number = invertToString(newArr, this->number.length() + 1);

			delete[] newArr;
		}

		// If length of other bigger than this 
		// Exchange this and other then do it again
		else
		{
			newInteger = other + *this;
		}
	}

	// "-" + "-"
	else if (!this->sign && !other.sign)
	{
		Integer thisTemp = *this;
		Integer otherTemp = other;

		thisTemp.sign = true;
		otherTemp.sign = true;

		newInteger = thisTemp + otherTemp;
		newInteger.sign = false; // - ( "+" + "+" )
	}

	// "+" + "-"
	else if (this->sign && !other.sign)
	{
		Integer temp = other;
		temp.sign = true;
		newInteger = *this - temp; // "+" - "+"
	}

	// "-" + "+"
	else if (!this->sign && other.sign)
	{
		Integer temp = *this;
		temp.sign = true;
		newInteger = other - temp; // "+" - "+"
	}

	newInteger.errorFlag = (this->errorFlag | other.errorFlag);

	return newInteger;
}

const Integer Integer::operator -(const Integer& other) const
{
	Integer newInteger;

	// Determine do "+" or "-"

	// "+" - "+"
	if (this->sign && other.sign)
	{
		char* newArr;

		// If length of this bigger than other or same 
		if (*this >= other)
		{
			// Initial a new Array for newInteger
			newArr = new char[this->number.length() + 1];
			for (int i = 0; i < this->number.length() + 1; i++)
			{
				newArr[i] = 0;
			}

			// Process two value subtraction
			for (int i = 0; i < this->number.length(); i++)
			{
				if (i < other.number.length())
				{
					newArr[i] += (this->number[this->number.length() - i - 1] - ASCII_BASE) - (other.number[other.number.length() - i - 1] - ASCII_BASE);
				}
				else
				{
					newArr[i] += this->number[this->number.length() - i - 1] - ASCII_BASE;
				}
				while (newArr[i] < 0)
				{
					newArr[i] += 10;
					newArr[i + 1]--;
				}
			}

			// Output to string of newInteger "number"
			newInteger.number = invertToString(newArr, this->number.length() + 1);

			delete[] newArr;
		}

		// If length of other bigger than this 
		// Exchange this and other then do it again
		else
		{
			newInteger = other - *this;
			newInteger.sign = false;
		}
	}

	// "-" - "-"
	else if (!this->sign && !other.sign)
	{
		Integer thisTemp = *this;
		Integer otherTemp = other;

		thisTemp.sign = true;
		otherTemp.sign = true;

		newInteger = otherTemp - thisTemp; // "+" - "+"
	}

	// "+" - "-"
	else if (this->sign && !other.sign)
	{
		Integer temp = other;
		temp.sign = true;
		newInteger = *this + temp; // "+" + "+"
	}

	// "-" - "+"
	else if (!this->sign && other.sign)
	{
		Integer temp = other;
		temp.sign = false;
		newInteger = *this + temp; // "-" + "-"
	}

	newInteger.removeZeroPrefix();

	newInteger.errorFlag = (this->errorFlag | other.errorFlag);

	return newInteger;
}

const Integer Integer::operator *(const Integer& other) const
{
	Integer newInteger;

	// Initial a new Array for newInteger
	char* newArr = new char[this->number.length() + other.number.length()];
	for (int i = 0; i < this->number.length() + other.number.length(); i++)
	{
		newArr[i] = 0;
	}

	for (int i = 0; i < other.number.length(); i++)
	{
		for (int j = 0; j < this->number.length(); j++)
		{
			newArr[i + j] += (this->number[this->number.length() - j - 1] - ASCII_BASE) * (other.number[other.number.length() - i - 1] - ASCII_BASE);
			while (newArr[i + j] >= 10)
			{
				newArr[i + j] -= 10;
				newArr[i + j + 1]++;
			}
		}
	}

	// Output to string of newInteger "number"
	newInteger.number = invertToString(newArr, this->number.length() + other.number.length());

	// Determine sign of result
	if ((this->sign && other.sign) || (!this->sign && !other.sign))
	{
		newInteger.sign = true;
	}
	else
	{
		newInteger.sign = false;
	}

	delete[] newArr;

	newInteger.removeZeroPrefix();

	newInteger.errorFlag = (this->errorFlag | other.errorFlag);

	return newInteger;
}

const Integer Integer::operator /(const Integer& other) const
{
	Integer newInteger;

	// Initial zero Integer
	Integer zero("0", 0);

	// At first to check legal or zero
	if (other == zero)
	{
		newInteger.number = "0";
		newInteger.setError(ERROR_DIVISION);
		return newInteger;
	}
	else if (other > *this)
	{
		return zero;
	}

	// Initial BN array
	Integer BN[11];
	for (int i = 0; i < 11; i++)
	{
		if (!i)
		{
			string zero = "0";
			BN[i] = Integer(zero, 0);
		}
		else
		{
			BN[i] = BN[i - 1] + other;
		}
	}

	// Initial a new Array for newInteger
	char* newArr = new char[this->number.length() - other.number.length() + 1];
	for (int i = 0; i <this->number.length() - other.number.length() + 1; i++)
	{
		newArr[i] = 0;
	}

	// Create a temp Integer to do "/"
	string strTemp;
	strTemp.assign(this->number, 0, other.number.length());
	strTemp = "0" + strTemp;
	Integer thisTemp(strTemp);

	// Process "/"
	int strLocation = other.number.length();
	int arrLocation = this->number.length() - other.number.length();
	while (this->number.length() >= strLocation)
	{
		if (strLocation != other.number.length())
		{
			thisTemp.number += this->number[strLocation - 1];
		}
		for (int i = 0; i < 11; i++)
		{
			if (BN[i] > thisTemp)
			{
				thisTemp = thisTemp - BN[i - 1];
				newArr[arrLocation] = i - 1;
				arrLocation--;
				break;

			}
			else if (BN[i] == thisTemp)
			{
				thisTemp = zero;
				newArr[arrLocation] = i;
				arrLocation--;
				break;
			}
		}
		strLocation++;
	}

	// Output to string of newInteger "number"
	newInteger.number = invertToString(newArr, this->number.length() - other.number.length() + 1);

	// delete newArr
	delete[] newArr;

	// Determine sign of result
	if ((this->sign && other.sign) || (!this->sign && !other.sign))
	{
		newInteger.sign = true;
	}
	else
	{
		newInteger.sign = false;
	}

	newInteger.removeZeroPrefix();

	newInteger.errorFlag = (this->errorFlag | other.errorFlag);

	return newInteger;
}

const Integer Integer::operator %(const Integer& other) const
{
	Integer newInteger, temp;
	temp = *this / other;
	newInteger = *this - (temp*other);

	newInteger.removeZeroPrefix();

	newInteger.errorFlag = (this->errorFlag | other.errorFlag);

	return newInteger;
}

const bool Integer::operator >(const Integer& other) const
{
	Integer thisTemp = *this;
	Integer otherTemp = other;

	// If length of this bigger than other 
	if (thisTemp.number.length() > otherTemp.number.length())
	{
		int diff = thisTemp.number.length() - otherTemp.number.length();
		for (int i = 0; i < diff; i++)
		{
			otherTemp.number = "0" + otherTemp.number;
		}
	}

	// If length of other bigger than this
	else if (thisTemp.number.length() < otherTemp.number.length())
	{
		int diff = otherTemp.number.length() - thisTemp.number.length();
		for (int i = 0; i < diff; i++)
		{
			thisTemp.number = "0" + thisTemp.number;
		}
	}

	// Now both length are same
	for (int i = 0; i < thisTemp.number.length(); i++)
	{
		if (thisTemp.number[i] != otherTemp.number[i])
		{
			return thisTemp.number[i] > otherTemp.number[i];
		}
	}
	return false;
}

const bool Integer::operator >=(const Integer& other) const
{
	Integer thisTemp = *this;
	Integer otherTemp = other;

	// If length of this bigger than other 
	if (thisTemp.number.length() > otherTemp.number.length())
	{
		int diff = thisTemp.number.length() - otherTemp.number.length();
		for (int i = 0; i < diff; i++)
		{
			otherTemp.number = "0" + otherTemp.number;
		}
	}

	// If length of other bigger than this
	else if (thisTemp.number.length() < otherTemp.number.length())
	{
		int diff = otherTemp.number.length() - thisTemp.number.length();
		for (int i = 0; i < diff; i++)
		{
			thisTemp.number = "0" + thisTemp.number;
		}
	}

	// Now both length are same
	for (int i = 0; i < thisTemp.number.length(); i++)
	{
		if (thisTemp.number[i] != otherTemp.number[i])
		{
			return thisTemp.number[i] > otherTemp.number[i];
		}
	}
	return true;
}

const bool Integer::operator <(const Integer& other) const
{
	Integer thisTemp = *this;
	Integer otherTemp = other;

	// If length of this bigger than other 
	if (thisTemp.number.length() > otherTemp.number.length())
	{
		int diff = thisTemp.number.length() - otherTemp.number.length();
		for (int i = 0; i < diff; i++)
		{
			otherTemp.number = "0" + otherTemp.number;
		}
	}

	// If length of other bigger than this
	else if (thisTemp.number.length() < otherTemp.number.length())
	{
		int diff = otherTemp.number.length() - thisTemp.number.length();
		for (int i = 0; i < diff; i++)
		{
			thisTemp.number = "0" + thisTemp.number;
		}
	}

	// Now both length are same
	for (int i = 0; i < thisTemp.number.length(); i++)
	{
		if (thisTemp.number[i] != otherTemp.number[i])
		{
			return thisTemp.number[i] < otherTemp.number[i];
		}
	}
	return false;
}

const bool Integer::operator <=(const Integer& other) const
{
	Integer thisTemp = *this;
	Integer otherTemp = other;

	// If length of this bigger than other 
	if (thisTemp.number.length() > otherTemp.number.length())
	{
		int diff = thisTemp.number.length() - otherTemp.number.length();
		for (int i = 0; i < diff; i++)
		{
			otherTemp.number = "0" + otherTemp.number;
		}
	}

	// If length of other bigger than this
	else if (thisTemp.number.length() < otherTemp.number.length())
	{
		int diff = otherTemp.number.length() - thisTemp.number.length();
		for (int i = 0; i < diff; i++)
		{
			thisTemp.number = "0" + thisTemp.number;
		}
	}

	// Now both length are same
	for (int i = 0; i < thisTemp.number.length(); i++)
	{
		if (thisTemp.number[i] != otherTemp.number[i])
		{
			return thisTemp.number[i] < otherTemp.number[i];
		}
	}
	return true;
}

const bool Integer::operator ==(const Integer& other) const
{
	Integer thisTemp = *this;
	Integer otherTemp = other;

	// If length of this bigger than other 
	if (thisTemp.number.length() > otherTemp.number.length())
	{
		int diff = thisTemp.number.length() - otherTemp.number.length();
		for (int i = 0; i < diff; i++)
		{
			otherTemp.number = "0" + otherTemp.number;
		}
	}

	// If length of other bigger than this
	else if (thisTemp.number.length() < otherTemp.number.length())
	{
		int diff = otherTemp.number.length() - thisTemp.number.length();
		for (int i = 0; i < diff; i++)
		{
			thisTemp.number = "0" + thisTemp.number;
		}
	}

	// Now both length are same
	for (int i = 0; i < thisTemp.number.length(); i++)
	{
		if (thisTemp.number[i] != otherTemp.number[i])
		{
			return false;
		}
	}
	return true;
}

const bool Integer::operator !=(const Integer& other) const
{
	return *this == other ? false : true;
}

ostream& operator <<(ostream& output, const Integer& integer)
{
	if (integer.getError())
	{
		switch (integer.getError())
		{
		case ERROR_CONSTRUCT:
			output << "ERROR_CONSTRUCT";
			break;
		case ERROR_FACTORIAL:
			output << "ERROR_FACTORIAL";
			break;
		case ERROR_DIVISION:
			output << "ERROR_DIVISION";
			break;
		default:
			output << "ERROR_INTEGER_UNKNOWN_ERROR";
			break;
		}

		return output;
	}

	if (!integer.sign)
	{
		output << '-';
	}

	output << integer.number;

	return output;
}

istream& operator >>(istream& input, Integer& integer)
{
	string number, processedNum;
	Calculator calculator;

	input >> number;
	processedNum = calculator.process(number);
	
	// If the return is a number
	if (processedNum[0] == '-' || (processedNum[0] >= '0' && processedNum[0] <= '9'))
	{
		integer = Integer(processedNum, 0);
	}
	else
	{
		integer.errorFlag = ERROR_CONSTRUCT;
		integer.sign = true;
		integer.number = "1";
	}

	return input;
}

const Integer Integer::power(const Integer& other) const
{
	Integer newInteger("1", 0);
	Integer temp = other;
	Integer one("1", 0);
	Integer zero("0", 0);

	// If case like 2^(-5), the result must small than 0.
	// Because the value returning is Integer, so it will be 0 (Decimal 0.xxxxxx ==> Integer 0)
	if (!other.getSign())
	{
		return zero;
	}

	while (temp != zero)
	{
		newInteger = newInteger * (*this);
		temp = temp - one;
	}

	return newInteger;
}

const Integer Integer::factorial() const
{
	Integer newInteger("1", 0);
	Integer temp = *this;
	Integer zero("0", 0);
	Integer one("1", 0);

	// Not allow for (-87)!
	if (!this->sign)
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

const string Integer::getOutput() const
{
	if (*this == Integer("0", 0))
		return "0";
	else
		return sign == true ? (number) : (string("-") + number);
}

void Integer::removeZeroPrefix()
{
	while (number.size() > 1 && number[0] == '0')
	{
		number.erase(0, 1);
	}
}

string Integer::invertToString(char * target, int size) const
{
	// Output to string of newInteger "number"

	string number = ""; // Initial string blank
	bool zero = false;		// Flag to determine output '0'

	for (int i = size - 1; i >= 0; i--)
	{
		if ((!target[i] && !i) || target[i])
		{
			zero = true;
		}
		if (!target[i])
		{
			if (zero)
			{
				number += target[i] + ASCII_BASE;
			}
		}
		else
		{
			number += target[i] + ASCII_BASE;
		}
	}
	return number;
}