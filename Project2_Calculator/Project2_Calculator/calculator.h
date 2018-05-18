// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class numObject
{
public:
	numObject();
	~numObject();
	void print();

private:

};

// for begining
void formulaProcess(string& strFormula);

// set variable
void setInteger(numObject& var);
void setDecimal(numObject& var);

// calculate function
numObject calculate(stringstream& formula);

// for error message

void error(string condition);