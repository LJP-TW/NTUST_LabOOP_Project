#include "Missile.h"

#define PRECISION 0.000001
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

		Weapon::Update();
	}
}
