// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "NumObject.h"
#include "Integer.h"
#include "Decimal.h"
#include "Calculator.h"

using namespace std;

int main()
{
	Calculator calculator;
	string strFormula;
	string result;

	while (cin >> strFormula)
	{
		result = calculator.process(strFormula);
		cout << result;
	}
	return 0;
}
