#include "Weapon.h"

#define PRECISION 0.000001
#define M_PI 3.14159265358979323846
#define DEGREE_TO_RADIAN(degree) (degree * M_PI / 180.0)
#define sin(x) sin(DEGREE_TO_RADIAN(x))
#define cos(x) cos(DEGREE_TO_RADIAN(x))

namespace Project3_SeaBattleSim
{
	Weapon::Weapon() : MovableObject()
	{
	}

	Weapon::Weapon(Coordinate location, std::string name, double damage, double speed, double range, Coordinate target) : MovableObject(location, name, "★")
	{
		// Initialization
		this->damage = damage;
		this->speed = speed;
		this->range = range;
		this->target = new Coordinate(target.x * BATTLEGRID_SIZE, target.y * BATTLEGRID_SIZE);
		double radians = Math::Atan2(location.y - target.y, target.x - location.x);
		this->angle = radians *(180 / Math::PI);
	}

	void Weapon::Update()
	{
		// 移動
		
		// 如果這一秒可以到達目的地, 則停在目的地上
		if ((this->doubleLocation->x - this->target->x) * (this->doubleLocation->x - this->target->x) + (this->doubleLocation->y - this->target->y) * (this->doubleLocation->y - this->target->y) <= (this->speed / 60) * BATTLEGRID_SIZE)
		{
			this->doubleLocation->x = this->target->x;
			this->doubleLocation->y = this->target->y;
		}
		else
		{
			if (cos(angle) > PRECISION || cos(angle) < -PRECISION)
			{
				this->doubleLocation->x = this->doubleLocation->x + (this->speed / 60) * cos(angle) * BATTLEGRID_SIZE;
			}
			if (sin(angle) > PRECISION || sin(angle) < -PRECISION)
			{
				this->doubleLocation->y = this->doubleLocation->y - (this->speed / 60) * sin(angle) * BATTLEGRID_SIZE;
			}
		}

		// 如果爆出範圍, 則停在邊界範圍

		if (this->doubleLocation->x < 0)
		{
			this->doubleLocation->x = 0;
		}
		else if (this->doubleLocation->x > BATTLEGRID_NUM * BATTLEGRID_SIZE + 1)
		{
			this->doubleLocation->x = BATTLEGRID_NUM * BATTLEGRID_SIZE + 1;
		}
		if (this->doubleLocation->y < 0)
		{
			this->doubleLocation->y = 0;
		} 
		else if(this->doubleLocation->y > BATTLEGRID_NUM * BATTLEGRID_SIZE + 1)
		{
			this->doubleLocation->y = BATTLEGRID_NUM * BATTLEGRID_SIZE + 1;
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
		if (this->target->x == this->doubleLocation->x && this->target->y == this->doubleLocation->y)
		{
			return true;
		}
		return false;
	}

	bool Weapon::isClose()
	{
		double squareDistance = (this->doubleLocation->x - this->target->x) * (this->doubleLocation->x - this->target->x) + (this->doubleLocation->y - this->target->y) * (this->doubleLocation->y - this->target->y);
		if (squareDistance < (3 * BATTLEGRID_SIZE) * (3 * BATTLEGRID_SIZE))
		{
			return true;
		}
		return false;
	}
}