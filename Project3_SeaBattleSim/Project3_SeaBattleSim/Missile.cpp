#include "Missile.h"

#define M_PI 3.14159265358979323846
#define DEGREE_TO_RADIAN(degree) (degree * M_PI / 180.0)
#define sin(x) sin(DEGREE_TO_RADIAN(x))
#define cos(x) cos(DEGREE_TO_RADIAN(x))

namespace Project3_SeaBattleSim
{
	Missile::Missile() :Weapon()
	{

	}

	Missile::Missile(Coordinate location, std::string name, double damage, double speed, double range, Vessel ^ targetVessel, Coordinate target) : Weapon(location, name, damage, speed, range, target)
	{
		this->targetVessel = targetVessel;
	}

	void Missile::Update()
	{
		// 更新目標船艦位置以及角度
		if (!targetVessel->isDead())
		{ 
			this->target->x = targetVessel->doubleLocation->x;
			this->target->y = targetVessel->doubleLocation->y;
			double radians = Math::Atan2(this->doubleLocation->y - this->target->y, this->target->x - this->doubleLocation->x);
			this->angle = radians * (180 / Math::PI);
		}

		// 移動
		double oldDX = this->doubleLocation->x;
		double oldDY = this->doubleLocation->y;

		// 如果到達目的地, 則停在目的地上
		if ((this->doubleLocation->x - this->target->x) * (this->doubleLocation->x - this->target->x) + (this->doubleLocation->y - this->target->y) * (this->doubleLocation->y - this->target->y) <= (this->speed / 60) * BATTLEGRID_SIZE)
		{
			this->doubleLocation->x = this->target->x;
			this->doubleLocation->y = this->target->y;
		}
		else
		{
			this->doubleLocation->x = this->doubleLocation->x + (this->speed / 60) * cos(angle) * BATTLEGRID_SIZE;
			this->doubleLocation->y = this->doubleLocation->y - (this->speed / 60) * sin(angle) * BATTLEGRID_SIZE;
		}

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
}
