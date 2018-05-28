// Student ID: B10615043
// Date: April 6, 2018
// Last Update: April 7, 2018
// Problem statement: This C++ header to implement class .
#include <stack>
#include "Calculator.h"
#define PRIORITY_LAYER 6
//#define ERROR_MSG

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
		// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��
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
				return message("EXPRESSION ERROR");
			}

			ssFormula << pureFormula;

			NumObject* pt = calculate(ssFormula, 1);

			if (pt == nullptr)
			{
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
				// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��

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
	// �W�h:
	// ����X�{���F�r��, �Ʀr, �B��l ���r        [complete]
	// �ܼƤ���۾F                                [complete]
	// �B��l����۾F(���t���e�i�J��B��l)        [complete]
	// �S�w�B��l�n�ŦX�S�w��m���X�{�Ʀr        [complete]
	// �B��l�᭱�i�H�� ���� �t�� �Ʀr            [complete]
	// �p�Ƥ��๳ .xxxx , �@�w�n yyyy.xxxx        [complete]
	// �A���n��                                    [complete]
	// ���t�^�� P,N                                [complete]
	// ����٦���h �Q����a

	bool illegal = false;    /*�ˬd���X�k*/
	int number_Of_Dot = 0;    /*�P�_.�b�@��줤�X�{�X��*/
	bool isSign = false;    /*�P�_�O�_�����t*/
	bool isVariable = false; /*�P�_�O�_���ܼ�*/
	bool meetParentheses = false;
	/*�k�s�b�J�ťթM����� �T�{������*/
	bool meetPower = false;
	string variable = "";    /*�ܼƦW��*/

							 /*�^��3/operator2/�Ʀr1/�A��4*/
	int pre = 0;
	/*�^��3/operator2/�Ʀr1/�A��4*/
	int now = 0;

	/*�P�_�A����*/
	stack<char>parentheses;

	/*�����r��̫e�����ť� (ex:    5)*/
	while (strFormula[0] == ' ')
	{
		// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��
		strFormula.erase(0, 1);
	}

	for (int i = 0; i < strFormula.size(); i++)
	{
		/*�ť�*/
		if (strFormula[i] == ' ')
		{
			/*�e���p�G�O�I�I, �F�L��*/
			if (strFormula[i - 1] == '.')
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "remind your fucking dotttttttttt son of bitttch.\n";
#endif
				break;
			}

			/*�u�d�@�Ӫť�*/
			if (strFormula[i - 1] == ' ')
			{
				strFormula.erase(i - 1, 1);
				i -= 1;
			}
			number_Of_Dot = 0;
			meetPower = false;
			continue;
		}
		/*�Ʀr*/
		else if (strFormula[i] <= '9' && strFormula[i] >= '0')
		{
			now = 1;

			if (isVariable)
			{
				variable += strFormula[i];
			}
		}
		/*operator*/
		else if (strFormula[i] == '+' || strFormula[i] == '-' || strFormula[i] == '*' || strFormula[i] == '/' || strFormula[i] == '^' || strFormula[i] == '!')
		{
			now = 2;
		}
		/*�r��*/
		else if (strFormula[i] >= 'a' && strFormula[i] <= 'z' || strFormula[i] >= 'A' && strFormula[i] <= 'Z')
		{
			now = 1;
			if (i == 0 || (i >= 1 && strFormula[i - 1] == ' '))
			{
				isVariable = true;
			}

			if (isVariable)
			{
				variable += strFormula[i];
			}
		}
		/*�P�_�A�����L���*/
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
#ifdef ERROR_MSG
				cout << "remind your fucking parentheses\n";
#endif
				break;
			}
			else
			{
				parentheses.pop();
			}
		}
		/*�P�_'.'*/
		else if (strFormula[i] == '.')
		{
			number_Of_Dot++;
			/*�P�_1.5.3 �M 2 ^ 0.5�����p*/
			if ((meetPower && strFormula[i + 1] != '5' && strFormula[i + 1] != '0') || number_Of_Dot > 1)
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "Dot repeat or power error\n";
#endif
				break;
			}
			if (pre != 1 || isVariable)
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "DOT ERROR\n";
#endif
				// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��
				break;
			}
		}
		/*�D�Ʀr�B��l�r��*/
		else
		{
			illegal = true;
#ifdef ERROR_MSG
			cout << "Words not included\n";
#endif
			break;
		}


		/*�A��+�ť�*/
		if (strFormula[i] == '(' || strFormula[i] == ')')
		{
			if (i != 0 && strFormula[i - 1] != ' ')
			{
				number_Of_Dot = 0;
				strFormula.insert(i, " ");
				i++;
			}
			/*' ) '�e���i���B��l*/
			if (i >= 2 && strFormula[i] == ')' && (pre == 2 && strFormula[i - 2] != '!' || strFormula[i - 2] == '(' || strFormula[i - 2] == '.'))
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "Parentheses ERROR\n";
#endif
				break;
			}
			if (strFormula[i] == '(' && (pre == 1 || (i >= 2 && strFormula[i - 2] == '!')))
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "Parentheses ERROR\n";
#endif
				break;
			}
		}

		/*�B��l�᭱�S���F�� (�o�ͦb�r���)*/
		if ((i == strFormula.size() - 1) && ((now == 2 && strFormula[i] != '!') || strFormula[i] == '.'))
		{
			illegal = true;
#ifdef ERROR_MSG
			cout << "Need number or variable after operator\n";
#endif
			break;
		}


		/*�Ĥ@�Ӧr�� pre = now �B �P�_�Ĥ@�Ӧr���ର^*!/. �B�Ĥ@�Ӧr�����t�Ÿ�����sign */
		if (i == 0)
		{
			pre = now;
			if (strFormula[i] == '^' || strFormula[i] == '/' || strFormula[i] == '*' || strFormula[i] == '!' || strFormula[i] == '.')
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "Operator cna't be the first character\n";
#endif
				break;
			}
			else if (strFormula[i] == '+' || strFormula[i] == '-')
			{
				isSign = true;
			}
		}

		/*�����N+�ť� ��isSign�٭� �k�s.���ƶq*/
		if (now != pre)
		{
			isSign = false;
			meetPower = false;
			/*�����*/
			if (strFormula[i - 1] != ' ')
			{
				strFormula.insert(i, " ");
				number_Of_Dot = 0;
				i++;
			}

			// For case liek "1.!"
			if (now == 2 && pre == 1 && i >= 2 && strFormula[i - 2] == '.')
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "Fuck You\n";
#endif
				break;
			}

			/* �p�G�O�ܼƮ� */ 
			if (isVariable)
			{
				/*�ˬd�ܼƬO�_�s�b*/
				auto find = varList.find(variable);
				// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��
				if (find == varList.end())
				{
					illegal = true; 
#ifdef ERROR_MSG
					cout << "Variable doesn't exist!" << endl;
#endif
					break;
				}
				variable = "";
				isVariable = false;
			}
		}

		/*�Ʀr�Φr���e���ର' ) '*/
		if (i >= 2 && strFormula[i - 2] == ')' && now == 1)
		{
			illegal = true;
#ifdef ERROR_MSG
			cout << "Parentheses ERROR\n";
#endif
			break;
		}

		/*�s��operatorc�[�ť� �P�_ '(' �Ĥ@�Ӥ��ΰ� �e�@�ӭY�����h���ҥ~*/
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
#ifdef ERROR_MSG
					cout << "Can't continuous intput operator\n";
#endif
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
			/*�P�_�X���X�k*/
			else
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "Can't continuous intput operator\n";
#endif
				break;
			}
		}
		/*���t�Ÿ���@#*/
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

		/*�P�_�O�_�X�k (Ex a a + 5) �Ĥ@�Ӥ��P�_ ||�᭱�P�_���h�S��ר�*/
		if (i != 0 && strFormula[i - 1] == ' ' && now != 2 && now != 4)
		{
			if ((pre != 2 && pre != 4) || (i >= 2 && strFormula[i - 2] == '!'))
			{
				illegal = true;
#ifdef ERROR_MSG
				cout << "Can't continuous input variable or number\n";
#endif
				break;
			}
		}

		/*�P�_�O�_�J��^ */
		if (now == 1 && i >= 2 && strFormula[i - 2] == '^')
		{
			meetPower = true;
		}

		/*�����ŦA����s, QQQ*/
		if (i == strFormula.size() - 1 && isVariable)
		{
			/*�ˬd�ܼƬO�_�s�b*/
			auto find = varList.find(variable);
			if (find == varList.end())
			{
				// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��
				illegal = true;
#ifdef ERROR_MSG
				cout << "Variable doesn't exist!" << endl;
#endif
				break;
			}
			variable = "";
			isVariable = false;
		}

		/*now��pre*/
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

	/*�A�������*/
	if (parentheses.size() > 0 && illegal == false)
	{
		illegal = true;
#ifdef ERROR_MSG
		cout << "Parentheses ERROR\n";
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
					// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��
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
					// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��
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
					// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��

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
					// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��
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
		// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��
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





// ��h��Ժɵ{���X�b�� https://github.com/LJP-TW/NTUST_LabOOP_Project/ �����t��o��