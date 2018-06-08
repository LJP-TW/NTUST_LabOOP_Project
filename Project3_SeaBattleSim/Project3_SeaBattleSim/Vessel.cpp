#include "Vessel.h"

namespace Project3_SeaBattleSim
{
	Vessle::Vessle(void)
	{
		throw gcnew System::NotImplementedException();
	}

	Vessle::Vessle(std::string name, double hp, double maxSpeed, double maxAttackDistance, unsigned int attackCD, double maxDefenseDistance, unsigned int defenseCD, Point location)
	{
		// Initialization
		this->Name = gcnew String(name.c_str());
		this->Text = gcnew String(("¡¶" + name).c_str());
		this->Location = location;
		this->AutoSize = true;
		this->hp = hp;
		this->maxSpeed = maxSpeed;
		this->maxAttackDistance = maxAttackDistance;
		this->attackCD = attackCD;
		this->maxDefenseDistance = maxDefenseDistance;
		this->defenseCD = defenseCD;
		this->nowSpeed = 0;
		this->nowAngle = 0;
		this->nowAttackCD = 0;
		this->isAttackCD = true;
		this->nowDefenseCD = 0;
		this->isDefenseCD = true;
	}
}