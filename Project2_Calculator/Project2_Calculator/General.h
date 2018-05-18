// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "NumObject.h"

using namespace std;

// for begining
void formulaProcess(string& strFormula);

// set variable
void setInteger(NumObject& var);
void setDecimal(NumObject& var);

// for error message
void error(string condition);