#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <Windows.h>
#include <vector>

#include "NumObject.h"
#include "Integer.h"
#include "Decimal.h"
#include "Calculator.h"

#define API_TESTING

using namespace std;

extern HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	SetConsoleTextAttribute(hConsole, 10);

	Calculator calculator;
	string strFormula;
	string result;

#ifdef API_TESTING
	/* API Testing */
	//Integer x;
	//Decimal y;

	//cin >> x; // ¿é¤J 123456789
	//cin >> y; // ¿é¤J 3.1415926

	//cout << x + y << endl;
	//cout << x - y << endl;
	//cout << x * y << endl;
	//cout << x / y << endl;

	Integer x = "123 * 8 + 456";
	Decimal y = "-1.0 / 3 - 45 / 13.0";

	vector<NumObject*> nums;
	nums.push_back(&x);
	nums.push_back(&y);
	for (const auto& num : nums)
	{
		if (num->getType() == "Integer")
			cout << *(Integer *)num << endl;
		else
			cout << *(Decimal *)num << endl;
	}
#else
	while (getline(cin, strFormula))
	{
		result = calculator.process(strFormula);
		cout << result << endl;

		SetConsoleTextAttribute(hConsole, 10);
	}

#endif

	return 0;
}
