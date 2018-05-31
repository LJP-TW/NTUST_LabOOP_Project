#include <Windows.h>
#include "NumObject.h"

using namespace std;

extern HANDLE hConsole;

NumObject::NumObject()
{
}

NumObject::~NumObject()
{
}

ostream& operator << (ostream& output, const NumObject& obj)
{
	if (obj.isError())
	{
		SetConsoleTextAttribute(hConsole, 12);
		output << obj.getErrorString();
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 10);
		output << obj.getOutput();
	}

	return output;
}

istream & operator>>(istream& input, NumObject& obj)
{
	string formula;
	
	input >> formula;

	obj.setInput(formula);

	return input;
}
