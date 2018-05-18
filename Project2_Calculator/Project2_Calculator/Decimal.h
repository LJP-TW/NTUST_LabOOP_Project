// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#pragma once
#include "NumObject.h"

class Decimal: public NumObject
{
public:
	Decimal();
	Decimal(stringstream& formula);
	~Decimal();

	const Decimal& operator=(stringstream& formula);

private:

};
