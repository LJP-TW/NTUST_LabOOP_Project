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

	// Accessor
	virtual const char getErrorFlag() const = 0;

	// Mutator
	virtual const void setErrorFlag(char error) = 0;

	// Other functions
	virtual const string getType() const = 0;
	virtual const string getOutput() const = 0;
	virtual const void setInput(string) = 0;
	virtual const bool isError() const = 0;
	virtual const string getErrorString() const = 0;

	// Operator Overloading
	friend ostream& operator << (ostream&, const NumObject&);
	friend istream& operator >> (istream&, NumObject&);
};