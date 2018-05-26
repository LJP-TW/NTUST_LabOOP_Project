// Student ID: 
// Date: May 17, 2018
// Last Update: May 18, 2018
// Problem statement: This C++ program about a calculator.
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "NumObject.h"
#include "Integer.h"
#include "Decimal.h"
#include "Calculator.h"

#define API_TESTING

using namespace std;

int main()
{
	Calculator calculator;
	string strFormula;
	string result;

#ifdef API_TESTING
	/* API Testing */
	Integer i;
	Decimal d;
	while (cin >> i >> d)
	{
		cout << i + i << endl;
		cout << i + d << endl;
		cout << d + i << endl;
		cout << d + d << endl;

		cout << i - i << endl;
		cout << i - d << endl;
		cout << d - i << endl;
		cout << d - d << endl;

		cout << i * i << endl;
		cout << i * d << endl;
		cout << d * i << endl;
		cout << d * d << endl;

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
	}

#endif

	return 0;
}
