// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#include <iostream>
#include <string>
#include <sstream>

#include "calculator.h"

using namespace std;

int main()
{
	string strFormula;
	while (cin >> strFormula)
	{
		formulaProcess(strFormula);

		stringstream formula;
		formula << strFormula;

		string command;
		formula >> command;

		if (command == "Set" || command == "set")
		{
			formula >> command;

			string variableName;
			formula >> variableName;

			if (command == "Integer" || command == "integer")
			{
				numObject variable = calculate(formula);
				setInteger(variable);
			}
			else if (command == "Decimal" || command == "decimal")
			{
				numObject variable = calculate(formula);
				setDecimal(variable);
			}
			else
			{
				error("TYPE NOT DEFINED");
			}
		}
		else
		{
			string temp;
			formula >> temp;

			if (temp == "=")
			{
				
			}
			else
			{
				numObject result = calculate(formula);
			}

		}

		result.print();
	}
	return 0;
}
