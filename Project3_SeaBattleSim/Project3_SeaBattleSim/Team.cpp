#include "Team.h"

using namespace System;

Team::Team()
{
	throw gcnew System::NotImplementedException();
}

Team::Team(std::string name)
{
	this->name = gcnew String(name.c_str());
	this->weaponID = 1;
}
