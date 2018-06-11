#include <string>
#include <msclr\marshal_cppstd.h>
#include "CV.h"
#include "Weapon.h"

namespace Project3_SeaBattleSim
{
	CV::CV(void) : Vessel()
	{
	}

	CV::CV(Coordinate location, std::string name, Team^ team) : Vessel(location, name, team, 5, 1, 25, 60, 5, 15)
	{
	}

	Weapon^ CV::Attack(Coordinate target) 
	{	
		// 判斷要攻擊的座標是否在攻擊範圍
		if (target.x < 0 || target.x > 20 ||
			target.y < 0 || target.y > 20 ||
			(target.x - (this->location->X) / BATTLEGRID_SIZE) * (target.x - this->location->X / BATTLEGRID_SIZE) + (target.y - this->location->Y / BATTLEGRID_SIZE) * (target.y - this->location->Y / BATTLEGRID_SIZE) > this->maxAttackDistance * this->maxAttackDistance)
		{
			// The Default Constructor of Weapon will set the errorFlag
			return gcnew Weapon();
		}

		// 創造 Weapon 並回傳
		
		// weaponName = "Shell_[team][id]"
		std::string weaponName = "Shell_" + msclr::interop::marshal_as<std::string>(this->team->name->ToString()) + std::to_string(this->team->weaponID);

		++this->team->weaponID;

		return gcnew Weapon(Coordinate(this->location->X / BATTLEGRID_SIZE, this->location->Y / BATTLEGRID_SIZE), weaponName, 3, 4, 1.5, Coordinate(target.x, target.y));
	}
}