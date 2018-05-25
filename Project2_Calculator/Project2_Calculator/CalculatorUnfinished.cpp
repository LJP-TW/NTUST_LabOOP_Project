#include <stack>
#include <string>
#include "Calculator.h"

bool Calculator::preProcess(string& strFormula)
{
	// �W�h:
	// ����X�{���F�r��, �Ʀr, �B��l ���r		[complete]
	// �ܼƤ���۾F								[complete]
	// �B��l����۾F(���t���e�i�J��B��l)		[complete]
	// �S�w�B��l�n�ŦX�S�w��m���X�{�Ʀr		[complete]
	// �B��l�᭱�i�H�� ���� �t�� �Ʀr			[complete]
	// �p�Ƥ��๳ .xxxx , �@�w�n yyyy.xxxx		[complete]
	// �A���n��									[complete]
	// ���t�^�� P,N								[complete]

	bool illegal = false;	/*�ˬd���X�k*/
	int number_Of_Dot = 0;	/*�P�_.�b�@��줤�X�{�X��*/
	bool isSign = false;	/*�P�_�O�_�����t*/
	bool meetParentheses = false;
	/*�k�s�b�J�ťթM����� �T�{������*/
	bool meetPower = false;
	int checkPower = 0;

	/*�^��3/operator2/�Ʀr1/�A��4*/
	int pre = 0;
	/*�^��3/operator2/�Ʀr1/�A��4*/
	int now = 0;

	/*�P�_�A����*/
	stack<char>parentheses;

	/*�����r��̫e�����ť� (ex:    5)*/
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
		/*�ť�*/
		if (strFormula[i] == ' ')
		{
			/*�u�d�@�Ӫť�*/
			if (strFormula[i - 1] == ' ')
			{
				strFormula.erase(i - 1, 1);
				i -= 1;
			}
			number_Of_Dot = 0;
			checkPower = 0;
			meetPower = false;
			continue;
		}
		/*�Ʀr*/
		else if (strFormula[i] <= '9' && strFormula[i] >= '0')
		{
			now = 1;
		}
		/*operator*/
		else if (strFormula[i] == '+' || strFormula[i] == '-' || strFormula[i] == '*' || strFormula[i] == '/' || strFormula[i] == '^' || strFormula[i] == '!')
		{
			now = 2;
		}
		/*�r��*/
		else if (strFormula[i] >= 'a' && strFormula[i] <= 'z' || strFormula[i] >= 'A' && strFormula[i] <= 'Z')
		{
			now = 3;
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
				cout << "remind your fucking parentheses\n";
				break;
			}
			else
			{
				parentheses.pop();
			}
		}
		/*�P�_'.'���L����*/
		else if (strFormula[i] == '.')
		{
			number_Of_Dot++;
			/*�P�_1.5.3 �M 2 ^ 0.5�����p*/
			if ((meetPower && strFormula[i + 1] != '5') || number_Of_Dot > 1)
			{
				illegal = true;
				cout << "Dot repeat or power error\n";
				break;
			}
		}
		/*�D�Ʀr�B��l�r��*/
		else
		{
			illegal = true;
			cout << "word not included\n";
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
			/*�B��l�ᤣ�i�� ' ) '*/
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

		/*�B��l�᭱�S���F�� (�o�ͦb�r���)*/
		if ((i == strFormula.size() - 1) && now == 2 && strFormula[i] != '!')
		{
			illegal = true;
			cout << "need number or variable after operator\n";
			break;
		}


		/*�Ĥ@�Ӧr�� pre = now �B �P�_�Ĥ@�Ӧr���ର^*!/. �B�Ĥ@�Ӧr�����t�Ÿ�����sign */
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

		/*�����N+�ť� ��isSign�٭� �k�s.���ƶq*/
		if (now != pre)
		{
			isSign = false;
			meetPower = false;
			checkPower = 0;
			/*�����*/
			if (strFormula[i - 1] != ' ')
			{
				strFormula.insert(i, " ");
				number_Of_Dot = 0;
				i++;
			}
		}

		/*�Ʀr�Φr���e���ର' ) '*/
		if (i >= 2 && strFormula[i - 2] == ')' && now == 1)
		{
			illegal = true;
			cout << "remind your fucking parentheses\n";
			break;
		}

		/*�s��operatorc�[�ť� �P�_ '(' �Ĥ@�Ӥ��ΰ� �e�@�ӭY�����h���ҥ~*/
		if (now == 2 && i != 0 && (pre == 2 || (i >= 2 && strFormula[i - 2] == '(')))
		{
			if (strFormula[i] == '+' || strFormula[i] == '-' || strFormula[i - 1] == '!')
			{
				if (strFormula[i - 1] == '!')
				{
					isSign = false;
				}
				else
				{
					isSign = true;
				}
				if (strFormula[i - 1] != ' ')
				{
					strFormula.insert(i, " ");
					i++;
				}
			}
			/*�P�_�X���X�k*/
			else
			{
				illegal = true;
				cout << "can't continuous intput operator\n";
				break;
			}
		}
		/*���t�Ÿ���PN*/
		if (isSign)
		{
			if (strFormula[i] == '+')
			{
				strFormula.replace(i, 1, "P");
			}
			else if (strFormula[i] == '-')
			{
				strFormula.replace(i, 1, "N");
			}
		}

		/*�P�_�O�_�X�k (Ex a a + 5) �Ĥ@�Ӥ��P�_ ||�᭱�P�_���h�S��ר�*/
		if (i != 0 && strFormula[i - 1] == ' ' && now != 2 && now != 4)
		{
			if ((pre != 2 && pre != 4) || (strFormula[i - 2] == '!' && i > 1))
			{
				illegal = true;
				cout << "can't continuous input variable or number\n";
				break;
			}
		}

		/*�P�_�O�_�J��^ */
		if (now == 1 && i >= 2 && strFormula[i - 2] == '^')
		{
			meetPower = true;
		}
		/*�����Y���p�ƥu��O0.5����ƭ� �J�쭼����S�J��p���I*/
		if (meetPower && number_Of_Dot == 1)
		{
			if (checkPower > 1)
			{
				cout << checkPower << endl;
				illegal = true;
				cout << "error power input\n";
				break;
			}
			else
			{
				checkPower++;
			}
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
		cout << "remind your fucking parentheses\n";
	}
	if (illegal)
	{
		return false;
	}
	return true;
}
