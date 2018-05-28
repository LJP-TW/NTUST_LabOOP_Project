// Student ID: B10615043
// Date: April 14, 2018
// Last Update: April 14, 2018
// Problem statement: This C++ header to declare class .
#pragma once
#include <iostream>
#include <string>
#include <map>
#include "NumObject.h"

using namespace std;

class Calculator
{
public:
	Calculator();
	~Calculator();

	string process(string strFormula);

private:
	map <string, NumObject*> varList;

	// process Helper function
	// - preProcess
	//   Verify whether strFormula includes a illegal formula
	//   If strFormula doesn't include a illegal formula, return true
	//   or return false
	bool preProcess(string& strFormula);

	// - calculate
	//   Handle formula, which may be command that setting variable, or just a single calculable formula
	//   The pointer returned by this function may be point to a Integer or Decimal
	NumObject* calculate(stringstream& formula);

	//   mode 0 : The pointer return by this function points to a Integer
	//   mode 1 : The pointer return by this function points to a Decimal
	NumObject* calculate(stringstream& formula, int mode);

	//   - toPostfixExpression
	string toPostfixExpression(stringstream& formula);

	//   - getOpPriority
	//     get priority of operator 
	int getOpPriority(char op);

	// message function
	string message(string errorMessage) { return errorMessage; };
};

#include "Integer.h"
#include "Decimal.h"