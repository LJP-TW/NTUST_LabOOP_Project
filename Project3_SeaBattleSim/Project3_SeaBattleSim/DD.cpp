#include <string>
#include <msclr\marshal_cppstd.h>
#include "DD.h"
#include "Weapon.h"

namespace Project3_SeaBattleSim
{
	DD::DD(void) :Vessel()
	{
	}

	DD::DD(Coordinate location, std::string name, Team ^ team) : Vessel(location, name, team, 2, 3, 10, 15, 20, 60)
	{
	}

	Weapon ^ DD::Attack(Coordinate target)
	{
		// �P�_�n�������y�ЬO�_�b�����d��
		if (target.x < 0 || target.x > 20 ||
			target.y < 0 || target.y > 20 ||
			(target.x - (this->location->X) / BATTLEGRID_SIZE) * (target.x - this->location->X / BATTLEGRID_SIZE) + (target.y - this->location->Y / BATTLEGRID_SIZE) * (target.y - this->location->Y / BATTLEGRID_SIZE) > this->maxAttackDistance * this->maxAttackDistance)
		{
			throw VESSEL_ERROR::ATTACK_ERROR;
		}

		// �гy Weapon �æ^��

		// weaponName = "Shell_[team][id]"
		std::string weaponName = "Shell_" + msclr::interop::marshal_as<std::string>(this->team->name->ToString()) + std::to_string(this->team->weaponID);

		++this->team->weaponID;

		return gcnew Weapon(Coordinate(this->location->X / BATTLEGRID_SIZE, this->location->Y / BATTLEGRID_SIZE), weaponName, 1, 3, 1.5, Coordinate(target.x, target.y));
	}
}