// Student ID: B10615043
// Date: April 6, 2018
// Last Update: April 7, 2018
// Problem statement: This C++ header to implement class .
#include "Integer.h"

Integer::Integer() : sign(true), number("0")
{
}

Integer::Integer(string& number)
{
	int i = 0;
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
}

Integer::Integer(const Integer& other)
{
	this->sign = other.sign;
	this->number = other.number;
}

Integer::~Integer()
{
}

const Integer& Integer::operator=(const Integer& other)
{
	this->sign = other.sign;
	this->number = other.number;

	return *this;
}

const Integer& Integer::operator=(const string& number)
{
	int i = 0;
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
