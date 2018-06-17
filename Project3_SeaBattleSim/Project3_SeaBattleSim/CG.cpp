#include <string>
#include <msclr\marshal_cppstd.h>
#include "CG.h"
#include "Weapon.h"

namespace Project3_SeaBattleSim
{
	CG::CG(void) :Vessel()
	{
	}

	CG::CG(Coordinate location, std::string name, Team ^ team) : Vessel(location, name, team, 3, 2, 15, 30, 15, 30)
	{
	}

	Weapon ^ CG::Attack(Coordinate target)
	{
		// 判斷要攻擊的座標是否在攻擊範圍
		if (target.x < 0 || target.x > 20 ||
			target.y < 0 || target.y > 20 ||
			(target.x - (this->location->X) / BATTLEGRID_SIZE) * (target.x - this->location->X / BATTLEGRID_SIZE) + (target.y - this->location->Y / BATTLEGRID_SIZE) * (target.y - this->location->Y / BATTLEGRID_SIZE) > this->maxAttackDistance * this->maxAttackDistance)
		{
			throw VESSEL_ERROR::ATTACK_ERROR;
		}

		// 創造 Weapon 並回傳

		// weaponName = "Shell_[team][id]"
		std::string weaponName = "Shell_" + msclr::interop::marshal_as<std::string>(this->team->name->ToString()) + std::to_string(this->team->weaponID);

		++this->team->weaponID;

		return gcnew Weapon(Coordinate(this->location->X / BATTLEGRID_SIZE, this->location->Y / BATTLEGRID_SIZE), weaponName, 2, 3, 1.5, Coordinate(target.x, target.y));
	}
}