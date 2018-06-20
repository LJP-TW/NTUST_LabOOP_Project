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

// 丟出例外

enum class LAYER_ERROR
{
	RENAME_ERROR,
};

enum class MOVABLEOBJECT_ERROR
{
	RENAME_ERROR,
};

enum class VESSEL_ERROR
{
	SET_SPEED_ERROR,
	ATTACK_ERROR,
	DEFENSE_ERROR,
};

enum class CMD_SET_ERROR
{
	TYPE_NOT_EXIST,
	/*新增重複名稱錯誤*/
	VESSEL_NAME_ERROR,
	/*新增座標錯誤*/
	COORDINATE_ERROR,
};

enum class CMD_FIRE_ERROR
{
	VESSEL_NOT_EXIST,
	WEAPON_ILLEGAL,
	/*新增座標錯誤*/
	COORDINATE_ERROR,
};

enum class CMD_MOVE_ERROR
{
	VESSEL_NOT_EXIST,
	SPEED_ILLEGAL,
};

/*新增防守錯誤*/
enum class CMD_DEFENSE_ERROR
{
	VESSEL_NOT_EXIST,
	WEAPON_ILLEGAL,
	NOT_IN_RANGE,
};

enum class CMD_TAG_ERROR
{
	VESSEL_NOT_EXIST,
	NEW_NAME_ILLEGAL,
};

// 所有艦種 定義在 Vessel.cpp
#define VESSEL_TYPE_NUM 6
extern std::string VESSEL_TYPE[VESSEL_TYPE_NUM];