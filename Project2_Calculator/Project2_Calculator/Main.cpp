// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "General.h"
#include "NumObject.h"
#include "Integer.h"
#include "Decimal.h"

using namespace std;

int main()
{
	map <string, NumObject> varList;
	string strFormula;
	while (cin >> strFormula)
	{
		formulaProcess(strFormula);

		stringstream ssCommand;
		ssCommand << strFormula;

		string strBegin;
		ssCommand >> strBegin;

		stringstream ssFormula;

		// Set Variable
		if (strBegin == "Set" || strBegin == "set") // Set A = 1 + 2 + B
		{
			string varType,	varName, assign;
			ssCommand >> varType >> varName >> assign;

			// Set Integer Variable
			if (varType == "Integer" || varType == "integer")
			{
				string pureFormula;
				getline(ssCommand, pureFormula);
				pureFormula.erase(pureFormula.begin());
				ssFormula << pureFormula;

				Integer variable = ssFormula;
				varList[varName] = variable;
			}

			// Set Decimal Variable
			else if (varType == "Decimal" || varType == "decimal")
			{
				string pureFormula;
				getline(ssCommand, pureFormula);
				pureFormula.erase(pureFormula.begin());
				ssFormula << pureFormula;

				Decimal variable = ssFormula;
				varList[varName] = variable;
			}

			// Type not defined
			else
			{
				error("TYPE NOT DEFINED");
			}
		}

		// Assign varible value or Formula calculate
		else
		{
			string strSecond;
			ssFormula >> strSecond;

			// Assign varible value
			if (strSecond == "=") // A = 1 + 2 + B 
			{
				// Search Varible
				auto it = varList.find(strBegin);

				if (it != varList.end())
				{
					string pureFormula;
					getline(ssCommand, pureFormula);
					pureFormula.erase(pureFormula.begin());
					ssFormula << pureFormula;

					it->second = ssFormula;
				}

				// Variable not exist
				else
				{
					error("VARIABLE NOT EXIST");
				}
			}

			// Formula calculate // 1.5 + 3 * ( - ( - 5 ) )
			else
			{
				ssFormula << strFormula;
				NumObject result = ssFormula;
				result.print();
			}
		}
	}
	return 0;
}
