#include "Integer.h"
#define ASCII_BASE 48

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
			newInteger.number = invertToString(newArr, this->number.length());
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

			// Process two value addition
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
			newInteger.number = invertToString(newArr, this->number.length());
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

	return newInteger;
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
	return string();
}