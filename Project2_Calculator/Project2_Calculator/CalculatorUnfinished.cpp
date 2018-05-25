#include <stack>
#include <string>
#include "Calculator.h"

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
	int checkPower = 0;

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
			checkPower = 0;
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
			/*運算子後不可接 ' ) '*/
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
			checkPower = 0;
			/*換單位*/
			if (strFormula[i - 1] != ' ')
			{
				strFormula.insert(i, " ");
				number_Of_Dot = 0;
				i++;
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
			/*判斷合不合法*/
			else
			{
				illegal = true;
				cout << "can't continuous intput operator\n";
				break;
			}
		}
		/*正負符號換PN*/
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
		/*乘冪若有小數只能是0.5的整數倍 遇到乘冪後又遇到小數點*/
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
