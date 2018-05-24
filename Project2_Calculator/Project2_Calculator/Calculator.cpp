// Student ID: B10615043
// Date: April 6, 2018
// Last Update: April 7, 2018
// Problem statement: This C++ header to implement class .
#include <stack>
#include "Calculator.h"
#define PRIORITY_LAYER 6

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
		ssCommand >> strSecond;

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

			result = pt->getOutput();

			delete pt;
			return result;
		}
	}

}

NumObject* Calculator::calculate(stringstream& formula)
{
	stack<NumObject*> numStack;
	string temp, expression;
	stringstream ssExpression;
	bool error = false;

	// Turn to postfix expression
	expression = toPostfixExpression(formula);
	ssExpression.str(expression);

	// Calculate the postfix expression
	while (ssExpression >> temp)
	{
		// If temp is a number
		if (temp[0] >= '0' && temp[0] <= '9')
		{
			// If temp is a decimal
			if (temp.find('.') != string::npos)
			{
				numStack.push(new Decimal(temp));
			}
			else
			{
				numStack.push(new Integer(temp));
			}
		}

		// Else if temp is a operator
		else
		{
			if (temp[0] == '!')
			{
				NumObject* pt = numStack.top();
				if (pt->getType() == "Integer")
				{
					((Integer*)pt)->factorial();
				}
				else
				{
					((Decimal*)pt)->factorial();

					// Error checking
					if (pt->isError())
					{
						error = true;
						break;
					}
				}
			}
			else if (temp[0] == '^')
			{
				NumObject* pt = numStack.top();
				NumObject* rvalue;
				if (pt->getType() == "Integer")
				{
					rvalue = new Integer(*(Integer*)pt);
				}
				else
				{
					rvalue = new Decimal(*(Decimal*)pt);
				}
				delete pt;
				numStack.pop();

				pt = numStack.top();
				if (pt->getType() == "Integer")
				{
					// Integer ^ Integer
					if (rvalue->getType() == "Integer")
					{
						((Integer *)pt)->power(*(Integer *)rvalue);
					}

					// Integer ^ Decimal
					else
					{
						NumObject* temp = pt;
						pt = new Decimal(*(Integer *)pt);
						((Decimal *)pt)->power(*(Decimal *)rvalue);

						delete temp;
					}
				}
				else
				{
					// Decimal ^ Integer
					if (rvalue->getType() == "Integer")
					{
						NumObject* temp = rvalue;
						rvalue = new Decimal(*(Integer *)rvalue);
						((Decimal *)pt)->power(*(Decimal *)rvalue);

						delete temp;
					}

					// Decimal ^ Decimal
					else
					{
						((Decimal *)pt)->power(*(Decimal *)rvalue);
					}
				}

				delete rvalue;

				// Error checking
				if (pt->isError())
				{
					error = true;
					break;
				}
			}
			else if (temp[0] == 'P')
			{
				// Do nothing, haha
			}
			else if (temp[0] == 'N')
			{
				NumObject* pt = numStack.top();
				if (pt->getType() == "Integer")
				{
					((Integer *)pt)->setSign(!((Integer *)pt)->getSign());
				}
				else
				{
					((Decimal *)pt)->setSign(!((Decimal *)pt)->getSign());
				}
			}
			else if (temp[0] == '*')
			{
				NumObject* pt = numStack.top();
				NumObject* rvalue;
				if (pt->getType() == "Integer")
				{
					rvalue = new Integer(*(Integer*)pt);
				}
				else
				{
					rvalue = new Decimal(*(Decimal*)pt);
				}
				delete pt;
				numStack.pop();

				pt = numStack.top();
				if (pt->getType() == "Integer")
				{
					// Integer * Integer
					if (rvalue->getType() == "Integer")
					{
						(*(Integer *)pt) = (*(Integer *)pt) * (*(Integer *)rvalue);
					}

					// Integer * Decimal
					else
					{
						NumObject* temp = pt;
						pt = new Decimal(*(Integer *)pt);
						(*(Decimal *)pt) = (*(Decimal *)pt) * (*(Decimal *)rvalue);

						delete temp;
					}
				}
				else
				{
					// Decimal * Integer
					if (rvalue->getType() == "Integer")
					{
						NumObject* temp = rvalue;
						rvalue = new Decimal(*(Integer *)rvalue);
						(*(Decimal *)pt) = (*(Decimal *)pt) * (*(Decimal *)rvalue);

						delete temp;
					}

					// Decimal * Decimal
					else
					{
						(*(Decimal *)pt) = (*(Decimal *)pt) * (*(Decimal *)rvalue);
					}
				}

				delete rvalue;
			}
			else if (temp[0] == '/')
			{
				NumObject* pt = numStack.top();
				NumObject* rvalue;
				if (pt->getType() == "Integer")
				{
					rvalue = new Integer(*(Integer*)pt);
				}
				else
				{
					rvalue = new Decimal(*(Decimal*)pt);
				}
				delete pt;
				numStack.pop();

				pt = numStack.top();
				if (pt->getType() == "Integer")
				{
					// Integer / Integer
					if (rvalue->getType() == "Integer")
					{
						(*(Integer *)pt) = (*(Integer *)pt) / (*(Integer *)rvalue);
					}

					// Integer / Decimal
					else
					{
						NumObject* temp = pt;
						pt = new Decimal(*(Integer *)pt);
						(*(Decimal *)pt) = (*(Decimal *)pt) / (*(Decimal *)rvalue);

						delete temp;
					}
				}
				else
				{
					// Decimal / Integer
					if (rvalue->getType() == "Integer")
					{
						NumObject* temp = rvalue;
						rvalue = new Decimal(*(Integer *)rvalue);
						(*(Decimal *)pt) = (*(Decimal *)pt) / (*(Decimal *)rvalue);

						delete temp;
					}

					// Decimal / Decimal
					else
					{
						(*(Decimal *)pt) = (*(Decimal *)pt) / (*(Decimal *)rvalue);
					}
				}

				delete rvalue;

				// Error checking
				if (pt->isError())
				{
					error = true;
					break;
				}
			}
			else if (temp[0] == '+')
			{
				NumObject* pt = numStack.top();
				NumObject* rvalue;
				if (pt->getType() == "Integer")
				{
					rvalue = new Integer(*(Integer*)pt);
				}
				else
				{
					rvalue = new Decimal(*(Decimal*)pt);
				}
				delete pt;
				numStack.pop();

				pt = numStack.top();
				if (pt->getType() == "Integer")
				{
					// Integer + Integer
					if (rvalue->getType() == "Integer")
					{
						(*(Integer *)pt) = (*(Integer *)pt) + (*(Integer *)rvalue);
					}

					// Integer + Decimal
					else
					{
						NumObject* temp = pt;
						pt = new Decimal(*(Integer *)pt);
						(*(Decimal *)pt) = (*(Decimal *)pt) + (*(Decimal *)rvalue);

						delete temp;
					}
				}
				else
				{
					// Decimal + Integer
					if (rvalue->getType() == "Integer")
					{
						NumObject* temp = rvalue;
						rvalue = new Decimal(*(Integer *)rvalue);
						(*(Decimal *)pt) = (*(Decimal *)pt) + (*(Decimal *)rvalue);

						delete temp;
					}

					// Decimal + Decimal
					else
					{
						(*(Decimal *)pt) = (*(Decimal *)pt) + (*(Decimal *)rvalue);
					}
				}

				delete rvalue;
			}
			else if (temp[0] == '-')
			{
				NumObject* pt = numStack.top();
				NumObject* rvalue;
				if (pt->getType() == "Integer")
				{
					rvalue = new Integer(*(Integer*)pt);
				}
				else
				{
					rvalue = new Decimal(*(Decimal*)pt);
				}
				delete pt;
				numStack.pop();

				pt = numStack.top();
				if (pt->getType() == "Integer")
				{
					// Integer - Integer
					if (rvalue->getType() == "Integer")
					{
						(*(Integer *)pt) = (*(Integer *)pt) - (*(Integer *)rvalue);
					}

					// Integer - Decimal
					else
					{
						NumObject* temp = pt;
						pt = new Decimal(*(Integer *)pt);
						(*(Decimal *)pt) = (*(Decimal *)pt) - (*(Decimal *)rvalue);

						delete temp;
					}
				}
				else
				{
					// Decimal - Integer
					if (rvalue->getType() == "Integer")
					{
						NumObject* temp = rvalue;
						rvalue = new Decimal(*(Integer *)rvalue);
						(*(Decimal *)pt) = (*(Decimal *)pt) - (*(Decimal *)rvalue);

						delete temp;
					}

					// Decimal - Decimal
					else
					{
						(*(Decimal *)pt) = (*(Decimal *)pt) - (*(Decimal *)rvalue);
					}
				}

				delete rvalue;
			}
		}
	}

	if (error || numStack.size() != 1)
	{
		while (numStack.size() != 0)
		{
			delete numStack.top();
			numStack.pop();
		}

		return nullptr;
	}

	return numStack.top();
}

NumObject* Calculator::calculate(stringstream& formula, int mode)
{
	NumObject* pt = calculate(formula);
	NumObject* temp = pt;

	// If mode == 0, return Integer
	if (mode == 0 && pt->getType() == "Decimal")
	{
		pt = new Integer(pt->getOutput());
		delete temp;
	}

	// Else if mode == 1, return Decimal
	else if (mode == 1 && pt->getType() == "Integer")
	{
		pt = new Decimal(*(Integer *)pt);
		delete temp;
	}

	return pt;
}

string Calculator::toPostfixExpression(stringstream& formula)
{
	// Operator Stack
	stack<char> opStack;
	string postfixExpression = "";
	string temp;

	while (formula >> temp)
	{
		// If temp is a number
		if (temp[0] >= '0' && temp[0] <= '9')
		{
			// Just put it into postfixExpression
			postfixExpression += temp;
			postfixExpression += ' ';
		}

		// Or temp is a operator
		else
		{
			// If temp operator is ')'
			//   pop op out until '('
			if (temp == ")")
			{
				char op;
				while ((op = opStack.top()) != '(')
				{
					postfixExpression += op;
					postfixExpression += ' ';

					opStack.pop();
				}
				opStack.pop();
			}

			// Else if temp operator is '('
			//   push temp into stack
			else if (temp == "(")
			{
				opStack.push(temp[0]);
			}

			// Else if temp is '!', push it into postfixExpression
			else if (temp[0] == '!')
			{
				postfixExpression += temp[0];
				postfixExpression += ' ';
			}

			else
			{
				int priority = getOpPriority(temp[0]);

				// If 
				//    (Stack is not empty)
				//    And 
				//      (the priority of top element of stack is bigger than temp)
				//      Or ((the priorities between top element's and temp's are equal) and (the expression is calculated from right to left))
				//        pop top into postfixExpression
				char op;
				while (opStack.size() != 0
					&& ((getOpPriority((op = opStack.top())) > priority) ||
						((getOpPriority(op) == priority) && (priority == 1 || priority == 2))))
				{
					postfixExpression += op;
					postfixExpression += ' ';

					opStack.pop();
				}

				opStack.push(temp[0]);
			}
		}
	}

	// If opStack isn't empty in the end
	//   pop it into postfixExpression
	while (opStack.size() != 0)
	{
		postfixExpression += opStack.top();
		postfixExpression += ' ';

		opStack.pop();
	}

	return postfixExpression;
}

int Calculator::getOpPriority(char op)
{
	string priority[PRIORITY_LAYER] =
	{
		"(",
		"+-", // Addition sign, Subtraction sign
		"*/",
		"PN", // Plus sign, not addition sign, Minus sign, not subtraction sign
		"^",
		"!"
	};

	for (int i = 0; i < PRIORITY_LAYER; ++i)
	{
		auto found = priority[i].find(op);
		if (found != string::npos)
		{
			return i;
		}
	}

	return -1;
}