#include <stack>
#include "Calculator.h"
#define PRIORITY_LAYER 6

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
					if (rvalue->getType() == "Integer")
					{
						((Integer *)pt)->power(*(Integer *)rvalue);
					}
					else
					{
						NumObject* temp = pt;
						pt = rvalue;
						rvalue = temp;
						((Decimal *)pt)->powerInteger(*(Integer *)rvalue);
					}
				}
				else
				{
					if (rvalue->getType() == "Integer")
					{
						((Decimal *)pt)->power(*(Integer *)rvalue);
					}
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
				if (pt->getType == "Integer")
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
					if (rvalue->getType() == "Integer")
					{
						(*(Integer *)pt) = (*(Integer *)pt) * (*(Integer *)rvalue);
					}
					else
					{
						NumObject* temp = pt;
						pt = rvalue;
						rvalue = temp;
						(*(Decimal *)pt) = (*(Decimal *)pt) * (*(Integer *)rvalue);
					}
				}
				else
				{
					if (rvalue->getType() == "Integer")
					{
						(*(Decimal *)pt) = (*(Decimal *)pt) * (*(Integer *)rvalue);
					}
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
						pt = rvalue;
						rvalue = temp;
						(*(Decimal *)pt) = (*(Decimal *)pt) / (*(Integer *)rvalue);
					}
				}
				else
				{
					if (rvalue->getType() == "Integer")
					{
						(*(Decimal *)pt) = (*(Decimal *)pt) / (*(Integer *)rvalue);
					}
					else
					{
						(*(Decimal *)pt) = (*(Decimal *)pt) / (*(Decimal *)rvalue);
					}
				}

				delete rvalue;
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
					if (rvalue->getType() == "Integer")
					{
						(*(Integer *)pt) = (*(Integer *)pt) + (*(Integer *)rvalue);
					}
					else
					{
						NumObject* temp = pt;
						pt = rvalue;
						rvalue = temp;
						(*(Decimal *)pt) = (*(Decimal *)pt) + (*(Integer *)rvalue);
					}
				}
				else
				{
					if (rvalue->getType() == "Integer")
					{
						(*(Decimal *)pt) = (*(Decimal *)pt) + (*(Integer *)rvalue);
					}
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
					if (rvalue->getType() == "Integer")
					{
						(*(Integer *)pt) = (*(Integer *)pt) - (*(Integer *)rvalue);
					}
					else
					{
						NumObject* temp = pt;
						pt = rvalue;
						rvalue = temp;
						(*(Decimal *)pt) = (*(Decimal *)pt) - (*(Integer *)rvalue);
					}
				}
				else
				{
					if (rvalue->getType() == "Integer")
					{
						(*(Decimal *)pt) = (*(Decimal *)pt) - (*(Integer *)rvalue);
					}
					else
					{
						(*(Decimal *)pt) = (*(Decimal *)pt) - (*(Decimal *)rvalue);
					}
				}

				delete rvalue;
			}
		}
	}

	if (error)
	{
		while (numStack.size() != 0)
		{
			delete numStack.top();
			numStack.pop();
		}

		return nullptr;
	}

	return nullptr;
}

NumObject* Calculator::calculate(stringstream& formula, int mode)
{
	return nullptr;
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