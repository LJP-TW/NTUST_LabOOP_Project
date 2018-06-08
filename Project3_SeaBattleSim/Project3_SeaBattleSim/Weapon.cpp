#include "Weapon.h"

namespace Project3_SeaBattleSim
{

	Weapon::Weapon()
	{
		throw gcnew System::NotImplementedException();
	}

	Weapon::Weapon(std::string name, double damage, double speed, double range, Point location, Point target)
	{
		// Initialization
		this->Name = gcnew String(name.c_str());
		this->Text = gcnew String(("⚫" + name).c_str());
		this->Location = location;
		this->AutoSize = true;
		this->damage = damage;
		this->speed = speed;
		this->range = range;
		this->target = target;
	}

	void Weapon::update()
	{
		throw gcnew System::NotImplementedException();
	}
}