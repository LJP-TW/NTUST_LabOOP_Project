// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#pragma once
#include "NumObject.h"

class Integer:public NumObject
{
public:
	Integer();
	Integer(stringstream& formula);
	~Integer();

	const Integer& operator=(stringstream& formula);

private:

};
