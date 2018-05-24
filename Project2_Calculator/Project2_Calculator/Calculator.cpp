// Student ID: B10615043
// Date: April 6, 2018
// Last Update: April 7, 2018
// Problem statement: This C++ header to implement class .
#include "Calculator.h"


Calculator::Calculator()
{
}

Calculator::~Calculator()
{
	// Free every pointer in varList
	for (auto it : varList)
	{
		delete it.second;
	}
}

string Calculator::process(string strFormula)
{
	// Make sure that '=' are covered by ' '
	auto found = strFormula.find('=');
	if (found != string::npos)
	{
		if (strFormula[found + 1] != ' ')
		{
			strFormula.insert(found + 1, " ");
		}
		if (strFormula[found - 1] != ' ')
		{
			strFormula.insert(found - 1, " ");
		}
	}

	stringstream ssCommand;
	ssCommand << strFormula;

	string strBegin;
	ssCommand >> strBegin;

	stringstream ssFormula;

	// Set Variable
	if (strBegin == "Set" || strBegin == "set") // Set A = 1 + 2 + B
	{
		string varType, varName, assign;
		ssCommand >> varType >> varName >> assign;

		if (assign != "=")
		{
			return message("COMMAND NOT DEFINED!");
		}
		// Set Integer Variable
		if (varType == "Integer" || varType == "integer")
		{
			string pureFormula;
			getline(ssCommand, pureFormula);
			pureFormula.erase(pureFormula.begin());

			// preProcess formula
			if (!preProcess(pureFormula))
			{
				return message("EXPRESSION ERROR");
			}

			ssFormula << pureFormula;

			NumObject* pt = calculate(ssFormula);

			if (pt->isError())
			{
				return message("CALCULATION ERROR");
			}

			varList[varName] = pt;
			return message("SUCCESS SET VARIABLE");
		}

		// Set Decimal Variable
		else if (varType == "Decimal" || varType == "decimal")
		{
			string pureFormula;
			getline(ssCommand, pureFormula);
			pureFormula.erase(pureFormula.begin());

			// preProcess formula
			if (!preProcess(pureFormula))
			{
				return message("EXPRESSION ERROR");
			}

			ssFormula << pureFormula;

			NumObject* pt = calculate(ssFormula);

			if (pt->isError())
			{
				return message("CALCULATION ERROR");
			}

			varList[varName] = calculate(ssFormula);

			return message("SUCCESS SET VARIABLE");
		}

		// Type not defined
		else
		{
			return message("TYPE NOT DEFINED");
		}
	}

	// Assign varible value or Formula calculate
	else
	{
		string strSecond;
		ssFormula >> strSecond;

		// Assign varible value
		// A = 1 + 2 + B 
		if (strSecond == "=") 
		{
			// Is strBegin legal

			// Search Varible
			auto it = varList.find(strBegin);

			if (it != varList.end())
			{
				string pureFormula;
				getline(ssCommand, pureFormula);
				pureFormula.erase(pureFormula.begin());

				// preProcess formula
				if (!preProcess(pureFormula))
				{
					return message("EXPRESSION ERROR");
				}

				ssFormula << pureFormula;

				NumObject* pt = calculate(ssFormula);

				if (pt->isError())
				{
					return message("CALCULATION ERROR");
				}

				delete it->second;
				it->second = calculate(ssFormula);

				return message("SUCCESS VARIABLE ASSIGN");
			}

			// Variable not exist
			else
			{
				return message("VARIABLE NOT EXIST");
			}
		}

		// Formula calculate 
		// 1.5 + 3 * ( - ( - 5 ) )
		else
		{
			string result;

			// preProcess formula
			if (!preProcess(strFormula))
			{
				return message("EXPRESSION ERROR");
			}

			ssFormula << strFormula;

			NumObject* pt = calculate(ssFormula);

			if (pt->isError())
			{
				return message("CALCULATION ERROR");
			}

			if (pt->getType() == "Integer")
			{
				result = ((Integer *)calculate(ssFormula))->getOutput();
			}
			else
			{
				result = ((Decimal *)calculate(ssFormula))->getOutput();
			}
			delete pt;
			return result;
		}
	}
	return string();
}