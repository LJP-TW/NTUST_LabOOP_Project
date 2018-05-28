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

			NumObject* pt = calculate(ssFormula, 0);

			if (pt == nullptr)
			{
				return message("CALCULATION ERROR");
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
				return message("EXPRESSION ERROR");
			}

			ssFormula << pureFormula;

			NumObject* pt = calculate(ssFormula, 1);

			if (pt == nullptr)
			{
				return message("CALCULATION ERROR");
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

				// preProcess formula
				if (!preProcess(pureFormula))
				{
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

			if (pt == nullptr)
			{
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
	// 規則:
	// 不能出現除了字母, 數字, 運算子 的字		[complete]
	// 變數不能相鄰								[complete]
	// 運算子不能相鄰(正負號前可遇到運算子)		[complete]
	// 特定運算子要符合特定位置有出現數字		[complete]
	// 運算子後面可以接 正號 負號 數字			[complete]
	// 小數不能像 .xxxx , 一定要 yyyy.xxxx		[complete]
	// 括號要對									[complete]
	// 正負回傳 P,N								[complete]

	bool illegal = false;	/*檢查不合法*/
	int number_Of_Dot = 0;	/*判斷.在一單位中出現幾次*/
	bool isSign = false;	/*判斷是否為正負*/
	bool meetParentheses = false;
	/*歸零在遇空白和換單位 確認乘冪用*/
	bool meetPower = false;
	string variable = "";	/*變數名稱*/

							/*英文3/operator2/數字1/括號4*/
	int pre = 0;
	/*英文3/operator2/數字1/括號4*/
	int now = 0;

	/*判斷括號用*/
	stack<char>parentheses;

	/*拿掉字串最前面的空白 (ex:    5)*/
	for (int i = 0; i < strFormula.size(); i++)
	{
		if (i == 0 && strFormula[i] == ' ')
		{
			strFormula.erase(i, 1);
			i -= 1;
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < strFormula.size(); i++)
	{
		/*空白*/
		if (strFormula[i] == ' ')
		{
			/*只留一個空白*/
			if (strFormula[i - 1] == ' ')
			{
				strFormula.erase(i - 1, 1);
				i -= 1;
			}
			number_Of_Dot = 0;
			meetPower = false;
			continue;
		}
		/*數字*/
		else if (strFormula[i] <= '9' && strFormula[i] >= '0')
		{
			now = 1;
		}
		/*operator*/
		else if (strFormula[i] == '+' || strFormula[i] == '-' || strFormula[i] == '*' || strFormula[i] == '/' || strFormula[i] == '^' || strFormula[i] == '!')
		{
			now = 2;
		}
		/*字母*/
		else if (strFormula[i] >= 'a' && strFormula[i] <= 'z' || strFormula[i] >= 'A' && strFormula[i] <= 'Z')
		{
			variable += strFormula[i];
			now = 3;
		}
		/*判斷括號有無對稱*/
		else if (strFormula[i] == '(')
		{
			now = 4;
			parentheses.push(strFormula[i]);
		}
		else if (strFormula[i] == ')')
		{
			meetParentheses = true;
			now = 4;
			if (parentheses.size() == 0)
			{
				illegal = true;
				cout << "remind your fucking parentheses\n";
				break;
			}
			else
			{
				parentheses.pop();
			}
		}
		/*判斷'.'有無重複*/
		else if (strFormula[i] == '.')
		{
			number_Of_Dot++;
			/*判斷1.5.3 和 2 ^ 0.5的情況*/
			if ((meetPower && strFormula[i + 1] != '5') || number_Of_Dot > 1)
			{
				illegal = true;
				cout << "Dot repeat or power error\n";
				break;
			}
		}
		/*非數字運算子字母*/
		else
		{
			illegal = true;
			cout << "word not included\n";
			break;
		}


		/*括號+空白*/
		if (strFormula[i] == '(' || strFormula[i] == ')')
		{
			if (i != 0 && strFormula[i - 1] != ' ')
			{
				number_Of_Dot = 0;
				strFormula.insert(i, " ");
				i++;
			}
			/*' ) '前不可接運算子*/
			if (i >= 2 && strFormula[i] == ')' && (pre == 2 && strFormula[i - 2] != '!' || strFormula[i - 2] == '('))
			{
				illegal = true;
				cout << "remind your fucking parentheses\n";
				break;
			}
			if (strFormula[i] == '(' && ((pre == 3 || pre == 1) || (i >= 2 && strFormula[i - 2] == '!')))
			{
				illegal = true;
				cout << "remind your fucking parentheses\n";
				break;
			}

		}

		/*運算子後面沒接東西 (發生在字串尾)*/
		if ((i == strFormula.size() - 1) && now == 2 && strFormula[i] != '!')
		{
			illegal = true;
			cout << "need number or variable after operator\n";
			break;
		}


		/*第一個字元 pre = now 且 判斷第一個字不能為^*!/. 且第一個字為正負符號必為sign */
		if (i == 0)
		{
			pre = now;
			if (strFormula[i] == '^' || strFormula[i] == '/' || strFormula[i] == '*' || strFormula[i] == '!' || strFormula[i] == '.')
			{
				illegal = true;
				cout << "operator cna't be the first character\n";
				break;
			}
			else if (strFormula[i] == '+' || strFormula[i] == '-')
			{
				isSign = true;
			}
		}

		/*換單位就+空白 把isSign還原 歸零.的數量*/
		if (now != pre)
		{
			isSign = false;
			meetPower = false;
			/*換單位*/
			if (strFormula[i - 1] != ' ')
			{
				strFormula.insert(i, " ");
				number_Of_Dot = 0;
				i++;
			}

			/* 如果 pre 是變數時 */
			if (pre == 3)
			{
				/*檢查變數是否存在*/
				auto find = varList.find(variable);
				if (find == varList.end())
				{
					illegal = true;
					cout << "Variable doesn't exist!" << endl;
					break;
				}

				variable = "";
			}
		}

		/*數字或字母前不能為' ) '*/
		if (i >= 2 && strFormula[i - 2] == ')' && now == 1)
		{
			illegal = true;
			cout << "remind your fucking parentheses\n";
			break;
		}

		/*連續operatorc加空白 判斷 '(' 第一個不用做 前一個若為階層有例外*/
		if (now == 2 && i != 0 && (pre == 2 || (i >= 2 && strFormula[i - 2] == '(')))
		{
			if (strFormula[i - 1] != ' ')
			{
				strFormula.insert(i, " ");
				i++;
			}
			if (strFormula[i] == '+' || strFormula[i] == '-' || strFormula[i - 2] == '!')
			{
				if (strFormula[i - 2] == '^')
				{
					illegal = true;
					cout << "can't continuous intput operator\n";
					break;
				}
				if (strFormula[i - 2] == '!')
				{
					isSign = false;
				}
				else
				{
					isSign = true;
				}
			}
			/*判斷合不合法*/
			else
			{
				illegal = true;
				cout << "can't continuous intput operator\n";
				break;
			}
		}
		/*正負符號換@#*/
		if (isSign)
		{
			if (strFormula[i] == '+')
			{
				strFormula.replace(i, 1, "@");
			}
			else if (strFormula[i] == '-')
			{
				strFormula.replace(i, 1, "#");
			}
		}

		/*判斷是否合法 (Ex a a + 5) 第一個不判斷 ||後面判斷階層特殊案例*/
		if (i != 0 && strFormula[i - 1] == ' ' && now != 2 && now != 4)
		{
			if ((pre != 2 && pre != 4) || (strFormula[i - 2] == '!' && i > 1))
			{
				illegal = true;
				cout << "can't continuous input variable or number\n";
				break;
			}
		}

		/*判斷是否遇到^ */
		if (now == 1 && i >= 2 && strFormula[i - 2] == '^')
		{
			meetPower = true;
		}


		/*now換pre*/
		switch (now)
		{
		case 1:
			pre = 1;
			break;
		case 2:
			pre = 2;
			break;
		case 3:
			pre = 3;
			break;
		case 4:
			pre = 4;
			break;
		}

	}

	/*括號不對稱*/
	if (parentheses.size() > 0 && illegal == false)
	{
		illegal = true;
		cout << "remind your fucking parentheses\n";
	}
	if (illegal)
	{
		return false;
	}
	return true;
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