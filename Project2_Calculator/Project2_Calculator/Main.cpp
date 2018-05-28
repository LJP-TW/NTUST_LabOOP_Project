// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <Windows.h>

#include "NumObject.h"
#include "Integer.h"
#include "Decimal.h"
#include "Calculator.h"

//#define API_TESTING

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
	// Constructor
	Integer i = "(-1 0)";
	Decimal d = "2.0+5";

	cout << i << endl;
	cout << d << endl;

	while (cin >> i >> d)
	{
		cout << i << endl;
		cout << d << endl;

		cout << endl;

		cout << i + i << endl;
		cout << i + d << endl;
		cout << d + i << endl;
		cout << d + d << endl;

		cout << endl;

		cout << i - i << endl;
		cout << i - d << endl;
		cout << d - i << endl;
		cout << d - d << endl;

		cout << endl;

		cout << i * i << endl;
		cout << i * d << endl;
		cout << d * i << endl;
		cout << d * d << endl;

		cout << endl;

		cout << i / i << endl;
		cout << i / d << endl;
		cout << d / i << endl;
		cout << d / d << endl;
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
