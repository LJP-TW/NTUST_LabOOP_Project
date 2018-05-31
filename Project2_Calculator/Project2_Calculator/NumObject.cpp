#include "NumObject.h"

NumObject::NumObject()
{
}

NumObject::~NumObject()
{
}

ostream& operator<< (ostream& output, const NumObject& obj)
{
	output << obj.getOutput();
	return output;
}