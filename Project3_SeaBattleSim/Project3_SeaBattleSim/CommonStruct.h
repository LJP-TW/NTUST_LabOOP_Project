#pragma once

struct Coordinate
{
	Coordinate(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	double x;
	double y;
};

enum class CMD_ERROR
{
	TYPE_NOT_EXIST,
};

// 所有艦種 定義在 Vessel.cpp
#define VESSEL_TYPE_NUM 4
extern std::string VESSEL_TYPE[VESSEL_TYPE_NUM];