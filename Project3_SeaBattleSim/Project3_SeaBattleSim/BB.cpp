#include <string>
#include <msclr\marshal_cppstd.h>
#include "BB.h"
#include "Weapon.h"

namespace Project3_SeaBattleSim
{
	BB::BB(void) :Vessel()
	{
	}

	BB::BB(Coordinate location, std::string name, Team ^ team) : Vessel(location, name, team, 4, 1, 20, 30, 10, 30)
	{
	}

	Weapon ^ BB::Attack(Coordinate target)
	{
		// �P�_�n�������y�ЬO�_�b�����d��
		if (target.x < 0 || target.x > BATTLEGRID_NUM ||
			target.y < 0 || target.y > BATTLEGRID_NUM ||
			(target.x - this->location->X / BATTLEGRID_SIZE) * (target.x - this->location->X / BATTLEGRID_SIZE) + (target.y - this->location->Y / BATTLEGRID_SIZE) * (target.y - this->location->Y / BATTLEGRID_SIZE) > this->maxAttackDistance * this->maxAttackDistance)
		{
			throw VESSEL_ERROR::ATTACK_ERROR;
		}

		// �Y�٦bCD
		if (!isAttackCD)
		{
			throw VESSEL_ERROR::ATTACK_ERROR;
		}

		// �i�JCD�ɶ�
		nowAttackCD = attackCD;
		isAttackCD = false;

		// �гy Weapon �æ^��
		// weaponName = "Shell_[team][id]"
		std::string weaponName = "Shell_" + msclr::interop::marshal_as<std::string>(this->team->name->ToString()) + std::to_string(this->team->weaponID);

		++this->team->weaponID;

		return gcnew Weapon(Coordinate(this->location->X / BATTLEGRID_SIZE, this->location->Y / BATTLEGRID_SIZE), weaponName, 3, 2, 1.5, Coordinate(target.x, target.y));
	}
}