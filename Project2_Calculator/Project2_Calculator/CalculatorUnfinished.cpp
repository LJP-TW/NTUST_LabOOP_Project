#include "Calculator.h"

bool Calculator::preProcess(string& strFormula)
{
	return false;
}

NumObject* Calculator::calculate(stringstream& formula)
{
	return nullptr;
}

NumObject* Calculator::calculate(stringstream& formula, int mode)
{
	return nullptr;
}

string Calculator::toPostfixExpression(stringstream& formula)
{
	return string();
}

int Calculator::getOpPriority(char op)
{
	return 0;
}
