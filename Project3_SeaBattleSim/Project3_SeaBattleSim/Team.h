#pragma once
#include <string>

ref class Team
{
public:
	// Constructor
	Team();
	Team(std::string name);

	// Data members
	// 隊伍名稱
	System::String^ name;

	// 第幾個砲彈
	unsigned int weaponID;
};