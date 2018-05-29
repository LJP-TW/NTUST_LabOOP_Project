#include <Windows.h>
#include <stack>
#include "Calculator.h"
#define PRIORITY_LAYER 6
#define ERROR_MSG

extern HANDLE hConsole;

namespace
{
	enum
	{
		CONSTANT = 0,
		VARIABLE,
		PARENTHESES,
		FACTORIAL,
		POWER,
		OPERATOR,
		SIGN
	};
}

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
	SetConsoleTextAttribute(hConsole, 10);

	// Make sure that '=' are covered by ' '
	auto found = strFormula.find('=');
	if (found != string::npos)
	{
		if (found + 1 < strFormula.size() && strFormula[found + 1] != ' ')
		{
			strFormula.insert(found + 1, " ");
		}
		if (found - 1 >= 0 && strFormula[found - 1] != ' ')
		{
			strFormula.insert(found, " ");
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
		// 更多更詳盡程式碼在※ https://github.com/LJP-TW/NTUST_LabOOP_Project/ 雞哈ㄅ摳得網
		ssCommand >> varType >> varName >> assign;

		if (assign != "=")
		{
			SetConsoleTextAttribute(hConsole, 12);
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
				SetConsoleTextAttribute(hConsole, 12);
				return message("EXPRESSION ERROR");
			}

			ssFormula << pureFormula;

			NumObject* pt = calculate(ssFormula, 0);

			if (pt == nullptr)
			{
				SetConsoleTextAttribute(hConsole, 12);
				return message("FAIL SET VARIABLE");
			}

			// If there is a object, delete it and then put a new pointer to replace it.
			if (varList[varName])
			{
				delete varList[varName];
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
				SetConsoleTextAttribute(hConsole, 12);
				return message("EXPRESSION ERROR");
			}

			ssFormula << pureFormula;

			NumObject* pt = calculate(ssFormula, 1);

			if (pt == nullptr)
			{
				SetConsoleTextAttribute(hConsole, 12);
				return message("FAIL SET VARIABLE");
			}

			// If there is a object, delete it and then put a new pointer to replace it.
			if (varList[varName])
			{
				delete varList[varName];
			}
			varList[varName] = pt;

			return message("SUCCESS SET VARIABLE");
		}

		// Type not defined
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
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

			// If the variable is found
			if (it != varList.end())
			{
				NumObject* pt;
				string pureFormula;
				getline(ssCommand, pureFormula);
				pureFormula.erase(pureFormula.begin());
				// 更多更詳盡程式碼在※ https://github.com/LJP-TW/NTUST_LabOOP_Project/ 雞哈ㄅ摳得網

				// preProcess formula
				if (!preProcess(pureFormula))
				{
					SetConsoleTextAttribute(hConsole, 12);
					return message("EXPRESSION ERROR");
				}

				ssFormula << pureFormula;

				if (it->second->getType() == "Integer")
				{
					pt = calculate(ssFormula, 0);
				}
				else
				{
					pt = calculate(ssFormula, 1);
				}

				if (pt == nullptr)
				{
					SetConsoleTextAttribute(hConsole, 12);
					return message("CALCULATION ERROR");
				}

				// Delete old object, and then put a new object pointer to replace it.
				delete it->second;
				it->second = pt;

				return message("SUCCESS VARIABLE ASSIGN");
			}

			// Variable not exist
			else
			{
				SetConsoleTextAttribute(hConsole, 12);
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
				SetConsoleTextAttribute(hConsole, 12);
				return message("EXPRESSION ERROR");
			}

			ssFormula << strFormula;

			NumObject* pt = calculate(ssFormula);

			if (pt == nullptr)
			{
				SetConsoleTextAttribute(hConsole, 12);
				return message("CALCULATION ERROR");
			}

			result = pt->getOutput();

			delete pt;
			return result;
		}
	}
}

bool Calculator::preProcess(string& strFormula)
{
	// 現在處理到第幾個字
	int i = 0;

	// 最後一個咚咚是啥東
	int lastStuff = -1;

	// 幾個括號, 每一個左括號會加一, 右括號會減一, 每次減一都要先確定此值非0, 字串處理結束後也要check此值為0
	int parenthesesNum = 0;

	// 是否合法
	bool illegal = false;
	
	// 是否是正負號
	bool isSign = true;

	// 是否是多餘的空格
	bool isExcessBlank = true;

	// 後續可以接什麼
	bool canConstant = true;
	bool canVariable = true;
	bool canLeftParentheses = true;
	bool canRightParentheses = false;
	bool canFactorial = false;
	bool canPower = false;
	bool canOperator = false;
	bool canSign = true;

	// 消除開頭的0
	while (strFormula[0] == ' ')
	{
		strFormula.erase(0, 1);
	}

	// preProcess every char in strFormula
	while (strFormula[i])
	{
		// If it is a dot
		if (strFormula[i] == '.')
		{
			illegal = true;
#ifdef ERROR_MSG
			cout << "PREPROCESS : BUG SUCH LIKE \".\", \"54 .87\", \"54 * .87\"" << endl;
#endif
			break;
		}

		// If it is a blank
		else if (strFormula[i] == ' ')
		{
			if (isExcessBlank)
			{
				strFormula.erase(i, 1);
			}
			else
			{
				isExcessBlank = true;
				++i;
			}
		}

		// Else if it is a constant
		else if (strFormula[i] >= '0' && strFormula[i] <= '9')
		{
			if (!canConstant)
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "PREPROCESS : THERE ARE SOMETHING WRONG BEFORE CONSTANT" << endl;
#endif
				break;
			}

			bool meetDot = false;
			int dotNum = 0;
			char c;

			while (++i < strFormula.size())
			{
				c = strFormula[i];
				if (c >= '0' && c <= '9')
				{
					meetDot = false;
					continue;
				}
				else if (c == '.')
				{
					meetDot = true;

					if (++dotNum > 1)
					{
						illegal = true;
#ifdef ERROR_MSG
						cout << "PREPROCESS : BUG SUCH LIKE \"54.8.7\"" << endl;
#endif
						break;
					}
				}
				else if (c == ' ')
				{
					break;
				}
				else
				{
					strFormula.insert(i, " ");
					break;
				}
			}
			
			if (illegal)
			{
				break;
			}

			if (meetDot)
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "PREPROCESS : BUG SUCH LIKE \"54. \", \"54.*2\"" << endl;
#endif
				break;
			}

			// Setting Flag
			canConstant = false;
			canVariable = false;
			canLeftParentheses = false;
			canRightParentheses = true;
			canFactorial = true;
			canPower = true;
			canOperator = true;
			canSign = false;
			
			// '+' '-' behind a constant represent addition/subtraction but not positive/nagetive
			isSign = false;

			isExcessBlank = false;

			lastStuff = CONSTANT;
		}

		// Else if it is a variable
		else if ((strFormula[i] >= 'a' && strFormula[i] <= 'z') ||
			(strFormula[i] >= 'A' && strFormula[i] <= 'Z'))
		{
			if (!canVariable)
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "PREPROCESS : THERE ARE SOMETHING WRONG BEFORE VARIABLE" << endl;
#endif
				break;
			}

			string variable = "";
			char c;

			variable += strFormula[i];

			while (++i < strFormula.size())
			{
				c = strFormula[i];
				if ((c >= '0' && c <= '9') ||
					(c >= 'a' && c <= 'z') ||
					(c >= 'A' && c <= 'Z'))
				{
					variable += c;
					continue;
				}
				else if (c == ' ')
				{
					break;
				}
				else
				{
					strFormula.insert(i, " ");
					break;
				}
			}

			// Check whether variable exist
			auto find = varList.find(variable);
			if (find == varList.end())
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "PREPROCESS : VARIABLE NOT EXIST" << endl;
#endif
				break;
			}

			// Setting Flag
			canConstant = false;
			canVariable = false;
			canLeftParentheses = false;
			canRightParentheses = true;
			canFactorial = true;
			canPower = true;
			canOperator = true;
			canSign = false;

			// '+' '-' behind a variable represent addition/subtraction but not positive/nagetive
			isSign = false;

			isExcessBlank = false;

			lastStuff = VARIABLE;
		}

		// Else if it is a left parenthes
		else if (strFormula[i] == '(')
		{
			if (!canLeftParentheses)
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "PREPROCESS : THERE ARE SOMETHING WRONG BEFORE (" << endl;
#endif
				break;
			}

			++parenthesesNum;
			++i;

			if (i < strFormula.size() && strFormula[i] != ' ')
			{
				strFormula.insert(i, " ");
			}
			
			// Setting Flag
			canConstant = true;
			canVariable = true;
			canLeftParentheses = true;
			canRightParentheses = true;
			canFactorial = false;
			canPower = false;
			canOperator = false;
			canSign = true;

			// '+' '-' behind '(' represent positive/nagetive but not addition/subtraction
			isSign = true;

			isExcessBlank = false;

			lastStuff = PARENTHESES;
		}

		// Else if it is a right parenthes
		else if (strFormula[i] == ')')
		{
			if(!canRightParentheses)
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "PREPROCESS : THERE ARE SOMETHING WRONG BEFORE )" << endl;
#endif
				break;
			}

			if (--parenthesesNum < 0) 
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "PREPROCESS : PARENTHESES ERROR" << endl;
#endif
				break;
			}

			++i;

			if (i < strFormula.size() && strFormula[i] != ' ')
			{
				strFormula.insert(i, " ");
			}

			// Setting Flag
			canConstant = false;
			canVariable = false;
			canLeftParentheses = false;
			canRightParentheses = true;
			canFactorial = true;
			canPower = true;
			canOperator = true;
			canSign = false;

			// '+' '-' behind ')' represent addition/subtraction but not positive/nagetive
			isSign = false;

			isExcessBlank = false;

			lastStuff = PARENTHESES;
		}

		else if (strFormula[i] == '!')
		{
			if (!canFactorial)
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "PREPROCESS : THERE ARE SOMETHING WRONG BEFORE FACTORIAL" << endl;
#endif
				break;
			}

			++i;

			if (i < strFormula.size() && strFormula[i] != ' ')
			{
				strFormula.insert(i, " ");
			}

			// Setting Flag
			canConstant = false;
			canVariable = false;
			canLeftParentheses = false;
			canRightParentheses = true;
			canFactorial = true;
			canPower = true;
			canOperator = true;
			canSign = false;

			// '+' '-' behind '!' represent addition/subtraction but not positive/nagetive
			isSign = false;

			isExcessBlank = false;

			lastStuff = FACTORIAL;
		}

		else if (strFormula[i] == '^')
		{
			if (!canPower)
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "PREPROCESS : THERE ARE SOMETHING WRONG BEFORE POWER" << endl;
#endif
				break;
			}

			++i;

			if (i < strFormula.size() && strFormula[i] != ' ')
			{
				strFormula.insert(i, " ");
			}

			// Setting Flag
			canConstant = true;
			canVariable = true;
			canLeftParentheses = true;
			canRightParentheses = false;
			canFactorial = false;
			canPower = false;
			canOperator = false;
			canSign = false;

			// '+' '-' behind '^' turn out error
			isSign = true;

			isExcessBlank = false;

			lastStuff = POWER;
		}

		else if (isSign && (strFormula[i] == '+' || strFormula[i] == '-'))
		{
			if (!canSign)
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "PREPROCESS : THERE ARE SOMETHING WRONG BEFORE SIGN" << endl;
#endif
				break;
			}

			// Use '@' to represent positive and '#' to represent nagetive
			strFormula[i] = strFormula[i] == '+' ? '@' : '#';
			
			++i;

			if (i < strFormula.size() && strFormula[i] != ' ')
			{
				strFormula.insert(i, " ");
			}

			// Setting Flag
			canConstant = true;
			canVariable = true;
			canLeftParentheses = true;
			canRightParentheses = false;
			canFactorial = false;
			canPower = false;
			canOperator = false;
			canSign = true;

			// '+' '-' behind '+' '-' represent  but positive/nagetive not addition/subtraction
			isSign = true;

			isExcessBlank = false;

			lastStuff = SIGN;
		}

		else if (strFormula[i] == '*' ||
			strFormula[i] == '/' ||
			strFormula[i] == '+' ||
			strFormula[i] == '-')
		{
			if (!canOperator)
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "PREPROCESS : THERE ARE SOMETHING WRONG BEFORE OPERATOR" << endl;
#endif
				break;
			}

			++i;

			if (i < strFormula.size() && strFormula[i] != ' ')
			{
				strFormula.insert(i, " ");
			}

			// Setting Flag
			canConstant = true;
			canVariable = true;
			canLeftParentheses = true;
			canRightParentheses = false;
			canFactorial = false;
			canPower = false;
			canOperator = false;
			canSign = true;

			// '+' '-' behind '+' '-' '*' '/' represent positive/nagetive but not addition/subtraction
			isSign = true;

			isExcessBlank = false;

			lastStuff = OPERATOR;
		}

		else
		{
			illegal = true;
#ifdef ERROR_MSG
			cout << "PREPROCESS : ILLEGAL CHARACTER" << endl;
#endif
			break;
		}
	}

	if (!illegal &&
		(lastStuff == POWER ||
			lastStuff == OPERATOR ||
			lastStuff == SIGN))
	{
		illegal = true;
#ifdef ERROR_MSG
		cout << "PREPROCESS : OPERATOR LACKS OF CONSTANT/VARIABLE" << endl;
#endif
	}

	if (!illegal && parenthesesNum != 0)
	{
		illegal = true;
#ifdef ERROR_MSG
		cout << "PREPROCESS : PARENTHESES SYMMETRY ERROR" << endl;
#endif
	}

	return illegal ? false : true;
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
				numStack.push(new Decimal(temp, 0));
			}
			else
			{
				numStack.push(new Integer(temp, 0));
			}
		}

		// Else if temp is a variable
		else if ((temp[0] >= 'a' && temp[0] <= 'z') ||
			(temp[0] >= 'A' && temp[0] <= 'Z'))
		{
			// Create a temp variable for calculation
			if (varList[temp]->getType() == "Decimal")
			{
				numStack.push(new Decimal(*(Decimal *)varList[temp]));
			}
			else
			{
				numStack.push(new Integer(*(Integer *)varList[temp]));
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
					(*(Integer*)pt) = ((Integer*)pt)->factorial();
				}
				else
				{
					Decimal decimalTemp = ((Decimal*)pt)->factorial();

					delete pt;
					// 更多更詳盡程式碼在※ https://github.com/LJP-TW/NTUST_LabOOP_Project/ 雞哈ㄅ摳得網
					numStack.pop();
					numStack.push(new Decimal(decimalTemp));

					pt = numStack.top();
				}

				// Error checking
				if (pt->isError())
				{
					error = true;
					break;
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
					// Integer ^ Positive Integer
					if (rvalue->getType() == "Integer")
					{
						(*(Integer *)pt) = ((Integer *)pt)->power(*(Integer *)rvalue);
					}

					// Integer ^ Decimal
					else
					{
						// Make a new decimal, pop old data, push new data
						Decimal newDecimal = Decimal(*(Integer *)pt).power((*(Decimal *)rvalue));

						delete pt;
						numStack.pop();
						numStack.push(new Decimal(newDecimal));

						pt = numStack.top();
					}
				}
				else
				{
					// Decimal ^ Integer
					if (rvalue->getType() == "Integer")
					{
						// Make a new decimal
						Decimal newDecimal(*(Integer *)rvalue);

						(*(Decimal *)pt) = (*(Decimal *)pt).power(newDecimal);
					}

					// Decimal ^ Decimal
					else
					{
						(*(Decimal *)pt) = ((Decimal *)pt)->power(*(Decimal *)rvalue);
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
			else if (temp[0] == '@')
			{
				// Do nothing, haha
			}
			else if (temp[0] == '#')
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
					// 更多更詳盡程式碼在※ https://github.com/LJP-TW/NTUST_LabOOP_Project/ 雞哈ㄅ摳得網
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
						// Make a new decimal, pop old data, push new data
						Decimal newDecimal = Decimal(*(Integer *)pt) * (*(Decimal *)rvalue);

						delete pt;
						numStack.pop();
						numStack.push(new Decimal(newDecimal));

						pt = numStack.top();
					}
				}
				else
				{
					// Decimal * Integer
					if (rvalue->getType() == "Integer")
					{
						// Make a new decimal
						Decimal newDecimal(*(Integer *)rvalue);

						(*(Decimal *)pt) = (*(Decimal *)pt) * newDecimal;
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
						// Make a new decimal, pop old data, push new data
						Decimal newDecimal = Decimal(*(Integer *)pt) / (*(Decimal *)rvalue);

						delete pt;
						numStack.pop();
						numStack.push(new Decimal(newDecimal));

						pt = numStack.top();
					}
				}
				else
				{
					// Decimal / Integer
					if (rvalue->getType() == "Integer")
					{
						// Make a new decimal
						Decimal newDecimal(*(Integer *)rvalue);

						(*(Decimal *)pt) = (*(Decimal *)pt) / newDecimal;
					}
					// 更多更詳盡程式碼在※ https://github.com/LJP-TW/NTUST_LabOOP_Project/ 雞哈ㄅ摳得網

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
						// Make a new decimal, pop old data, push new data
						Decimal newDecimal = Decimal(*(Integer *)pt) + (*(Decimal *)rvalue);

						delete pt;
						numStack.pop();
						numStack.push(new Decimal(newDecimal));

						pt = numStack.top();
					}
				}
				else
				{
					// Decimal + Integer
					if (rvalue->getType() == "Integer")
					{
						// Make a new decimal
						Decimal newDecimal(*(Integer *)rvalue);

						(*(Decimal *)pt) = (*(Decimal *)pt) + newDecimal;
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
					// 更多更詳盡程式碼在※ https://github.com/LJP-TW/NTUST_LabOOP_Project/ 雞哈ㄅ摳得網
					else
					{
						// Make a new decimal, pop old data, push new data
						Decimal newDecimal = Decimal(*(Integer *)pt) - (*(Decimal *)rvalue);

						delete pt;
						numStack.pop();
						numStack.push(new Decimal(newDecimal));

						pt = numStack.top();
					}
				}
				else
				{
					// Decimal - Integer
					if (rvalue->getType() == "Integer")
					{
						// Make a new decimal
						Decimal newDecimal(*(Integer *)rvalue);

						(*(Decimal *)pt) = (*(Decimal *)pt) - newDecimal;
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

	if (pt == nullptr)
	{
		return pt;
	}

	// If mode == 0, return Integer
	if (mode == 0 && pt->getType() == "Decimal")
	{
		Integer numerator = (*(Decimal *)pt).getNumerator();
		numerator.setSign((*(Decimal *)pt).getSign());

		Integer denominator = (*(Decimal *)pt).getDenominator();

		pt = new Integer(numerator / denominator);
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
		// If temp is a number or a variable
		if ((temp[0] >= '0' && temp[0] <= '9') ||
			(temp[0] >= 'a' && temp[0] <= 'z') ||
			(temp[0] >= 'A' && temp[0] <= 'Z'))
		{
			// Just put it into postfixExpression
			postfixExpression += temp;
			postfixExpression += ' ';
		}
		// 更多更詳盡程式碼在※ https://github.com/LJP-TW/NTUST_LabOOP_Project/ 雞哈ㄅ摳得網
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
		"@#", // @ : Plus sign, not addition sign; # : Minus sign, not subtraction sign
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





// 更多更詳盡程式碼在※ https://github.com/LJP-TW/NTUST_LabOOP_Project/ 雞哈ㄅ摳得網