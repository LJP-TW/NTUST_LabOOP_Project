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
		int* newArr;

		// Determine which is Bigger (Default this is bigger)
		bool thisIsBigger = true;

		// If length of other bigger than this 
		if (this->number.length() < other.number.length())
		{
			thisIsBigger = false;
		}

		// If length are same
		else if (this->number.length() == other.number.length())
		{
			for (int i = 0; i < this->number.length(); i++)
			{
				if (this->number[i] != other.number[i])
				{
					if (this->number[i] < other.number[i])
					{
						thisIsBigger = false;
						break;
					}
				}
			}
		}

		// If length of this bigger than other 
		if (thisIsBigger)
		{
			// Initial a new Array for newInteger
			newArr = new int[this->number.length() + 1];
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

			// Output to string of newInteger "number"

			newInteger.number = ""; // Initial string blank
			bool zero = false;		// Flag to determine output '0'

			for (int i = this->number.length(); i >= 0; i--)
			{
				if ((!newArr[i] && !i) || newArr[i])
				{
					zero = true;
				}
				if (!newArr[i])
				{
					if (zero)
					{
						newInteger.number += newArr[i] + ASCII_BASE;
					}
				}
				else
				{
					newInteger.number += newArr[i] + ASCII_BASE;
				}
			}
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
		int* newArr;

		// Determine which is Bigger (Default this is bigger)
		bool thisIsBigger = true;

		// If length of other bigger than this 
		if (this->number.length() < other.number.length())
		{
			thisIsBigger = false;
		}
		// If length are same
		else if (this->number.length() == other.number.length())
		{
			for (int i = 0; i < this->number.length(); i++)
			{
				if (this->number[i] != other.number[i])
				{
					if (this->number[i] < other.number[i])
					{
						thisIsBigger = false;
						break;
					}
				}
			}
		}

		if (thisIsBigger)
		{
			// Initial a new Array for newInteger
			newArr = new int[this->number.length() + 1];
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

			newInteger.number = ""; // Initial string blank
			bool zero = false;		// Flag to determine output '0'

			for (int i = this->number.length(); i >= 0; i--)
			{
				if ((!newArr[i] && !i) || newArr[i])
				{
					zero = true;
				}
				if (!newArr[i])
				{
					if (zero)
					{
						newInteger.number += newArr[i] + ASCII_BASE;
					}
				}
				else
				{
					newInteger.number += newArr[i] + ASCII_BASE;
				}
			}
		}
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
