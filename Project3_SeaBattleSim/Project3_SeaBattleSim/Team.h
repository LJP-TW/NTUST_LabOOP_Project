#pragma once
#include <string>

ref class Team
{
public:
	// Constructor
	Team();
	Team(std::string name);

	// Data members
	// ����W��
	System::String^ name;

	// �ĴX�ӯ��u
	unsigned int weaponID;
};