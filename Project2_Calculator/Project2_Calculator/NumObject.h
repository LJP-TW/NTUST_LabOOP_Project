// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#pragma once
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class NumObject
{
public:
	NumObject();
	virtual ~NumObject();

	// Other functions
	virtual const string getType() const = 0;
	virtual const string getOutput() const = 0;
	virtual const bool isError() const = 0;
	virtual const void setError(char error) = 0;
	virtual const char getError() const = 0;
};