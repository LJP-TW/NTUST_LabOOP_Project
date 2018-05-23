// Student ID: B10615043
// Date: April 14, 2018
// Last Update: April 14, 2018
// Problem statement: This C++ header to declare class .
#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Integer.h"
#include "Decimal.h"

using namespace std;

class Calculator
{
public:
	Calculator();
	~Calculator();
	string process(string& strFormula);

	bool preProcess(string& strFormula);

	NumObject* calculate(stringstream& formula);

private:
	map <string, NumObject*> varList;

	// error message function
	string message(string errorMessage);
};
