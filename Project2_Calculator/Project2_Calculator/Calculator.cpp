// Student ID: B10615043
// Date: April 6, 2018
// Last Update: April 7, 2018
// Problem statement: This C++ header to implement class .
#include "Calculator.h"


string Calculator::process(string & strFormula)
{
	// determine formula is legal or not
	if (!preProcess(strFormula))
	{
		return message("ERROR! HOW STUPID YOU ARE!");
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
			ssFormula << pureFormula;

			varList[varName] = calculate(ssFormula);
			return message("SUCCESS SET VARIABLE");
		}

		// Set Decimal Variable
		else if (varType == "Decimal" || varType == "decimal")
		{
			string pureFormula;
			getline(ssCommand, pureFormula);
			pureFormula.erase(pureFormula.begin());
			ssFormula << pureFormula;

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
			// Search Varible
			auto it = varList.find(strBegin);

			if (it != varList.end())
			{
				string pureFormula;
				getline(ssCommand, pureFormula);
				pureFormula.erase(pureFormula.begin());
				ssFormula << pureFormula;

				*(it->second) = ssFormula;

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
			ssFormula << strFormula;
			NumObject result = ssFormula;
			result.print();
		}
	}
	return string();
}
