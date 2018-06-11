#include "Weapon.h"

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
		this->isError = false;
	}

	void Weapon::Update()
	{
		// Do something
	}
}