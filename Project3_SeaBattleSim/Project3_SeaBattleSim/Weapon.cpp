#include "Weapon.h"

#define DEGREE_TO_RADIAN(degree) (degree * 3.14159265359 / 180.0)
#define sin(x) sin(DEGREE_TO_RADIAN(x))
#define cos(x) cos(DEGREE_TO_RADIAN(x))

namespace Project3_SeaBattleSim
{
	Weapon::Weapon() : MovableObject()
	{
		this->isError = true;
	}

	Weapon::Weapon(Coordinate location, std::string name, double damage, double speed, double range, Coordinate target) : MovableObject(location, name, "●")
	{
		// Initialization
		this->damage = damage;
		this->speed = speed;
		this->range = range;
		this->target = new Coordinate(target.x, target.y);
		double radians = Math::Atan2(target.y - location.y, location.x - target.x);
		this->angle = radians *(180 / Math::PI);
		this->isError = false;
	}

	void Weapon::Update()
	{
		// 移動
		double oldDX = this->doubleLocation->x;
		double oldDY = this->doubleLocation->y;
		this->doubleLocation->x = this->doubleLocation->x + (this->speed / 60) * cos(angle) * BATTLEGRID_SIZE;
		this->doubleLocation->y = this->doubleLocation->y - (this->speed / 60) * sin(angle) * BATTLEGRID_SIZE;

		// 如果爆出範圍, 則不動
		if (this->doubleLocation->x < 0 || this->doubleLocation->x > BATTLEGRID_NUM * BATTLEGRID_SIZE + 1 ||
			this->doubleLocation->y < 0 || this->doubleLocation->y > BATTLEGRID_NUM * BATTLEGRID_SIZE + 1)
		{
			this->doubleLocation->x = oldDX;
			this->doubleLocation->y = oldDY;
		}

		int oldX = this->location->X;
		int oldY = this->location->Y;
		this->location->X = this->doubleLocation->x;
		this->location->Y = this->doubleLocation->y;

		// 如果有移動, 則需重新繪畫
		if (oldX != this->location->X || oldY != this->location->Y)
		{
			this->Refresh();
		}
	}
	bool Weapon::isArrival()
	{
		if (this->target->x * BATTLEGRID_SIZE == this->doubleLocation->x && this->target->y*BATTLEGRID_SIZE == this->doubleLocation->y)
		{
			return true;
		}
		return false;
	}
}