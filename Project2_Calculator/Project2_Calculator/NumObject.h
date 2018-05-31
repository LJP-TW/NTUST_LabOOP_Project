#pragma once
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class NumObject
{
public:
	NumObject();
	virtual ~NumObject();

	// Other functions
	virtual const string getType() const = 0;
	virtual const string getOutput() const = 0;
	virtual const bool isError() const = 0;
	virtual const void setError(char error) = 0;
	virtual const char getError() const = 0;

	friend ostream& operator << (ostream&, const NumObject&);
};