// Student ID: B10615043
// Date: April 6, 2018
// Last Update: April 7, 2018
// Problem statement: This C++ header to implement class .
#include "Integer.h"
#define ASCII_BASE 48

Integer::Integer() : errorFlag(0), sign(true), number("0")
{
}

Integer::Integer(const string& number)
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

	return newInteger;
}

const Integer& Integer::operator=(const Integer& other)
{
	this->errorFlag = other.errorFlag;
	this->sign = other.sign;
	this->number = other.number;

	return *this;
}

const Integer& Integer::operator=(const string& number)
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
	while (number[i])
	{
		this->number += number[i++];
	}

	return *this;
}

const bool Integer::operator>(const Integer & other) const
{
	// If length of this bigger than other 
	if (this->number.length() > other.number.length())
	{
		return true;
	}

	// If length of other bigger than this
	else if (this->number.length() < other.number.length())
	{
		return false;
	}
	// If length are same
	else if (this->number.length() == other.number.length())
	{
		for (int i = 0; i < this->number.length(); i++)
		{
			if (this->number[i] != other.number[i])
			{
				return this->number[i] > other.number[i];
			}
		}
	}
	return false;
}

const bool Integer::operator>=(const Integer & other) const
{
	// If length of this bigger than other 
	if (this->number.length() > other.number.length())
	{
		return true;
	}

	// If length of other bigger than this
	else if (this->number.length() < other.number.length())
	{
		return false;
	}
	// If length are same
	else if (this->number.length() == other.number.length())
	{
		for (int i = 0; i < this->number.length(); i++)
		{
			if (this->number[i] != other.number[i])
			{
				return this->number[i] > other.number[i];
			}
		}
	}
	return true;
}

const bool Integer::operator<(const Integer & other) const
{
	// If length of this bigger than other 
	if (this->number.length() > other.number.length())
	{
		return false;
	}

	// If length of other bigger than this
	else if (this->number.length() < other.number.length())
	{
		return true;
	}
	// If length are same
	else if (this->number.length() == other.number.length())
	{
		for (int i = 0; i < this->number.length(); i++)
		{
			if (this->number[i] != other.number[i])
			{
				return this->number[i] < other.number[i];
			}
		}
	}
	return false;
}

const bool Integer::operator<=(const Integer & other) const
{
	// If length of this bigger than other 
	if (this->number.length() > other.number.length())
	{
		return false;
	}

	// If length of other bigger than this
	else if (this->number.length() < other.number.length())
	{
		return true;
	}
	// If length are same
	else if (this->number.length() == other.number.length())
	{
		for (int i = 0; i < this->number.length(); i++)
		{
			if (this->number[i] != other.number[i])
			{
				return this->number[i] < other.number[i];
			}
		}
	}
	return true;
}

const bool Integer::operator==(const Integer & other) const
{
	// If length are same
	if (this->number.length() == other.number.length())
	{
		for (int i = 0; i < this->number.length(); i++)
		{
			if (this->number[i] != other.number[i])
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

ostream& operator <<(ostream& output, Integer& integer)
{
	if (!integer.sign)
	{
		output << '-';
	}

	output << integer.number;

	return output;
}

istream& operator >>(istream& input, Integer& integer)
{
	string number;
	input >> number;
	integer = number;

	return input;
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