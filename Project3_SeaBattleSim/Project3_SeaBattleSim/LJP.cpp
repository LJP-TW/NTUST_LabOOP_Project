#include <string>
#include <msclr\marshal_cppstd.h>
#include "LJP.h"
#include "Weapon.h"

#define M_PI 3.14159265358979323846
#define DEGREE_TO_RADIAN(degree) (degree * M_PI / 180.0)
#define sin(x) sin(DEGREE_TO_RADIAN(x))
#define cos(x) cos(DEGREE_TO_RADIAN(x))

namespace Project3_SeaBattleSim
{
	LJP::LJP(void) :Vessel()
	{
	}

	LJP::LJP(Coordinate location, std::string name, Team ^ team) : Vessel(location, name, team, 10, 5, 30, 15, 20, 15)
	{
		this->missileCD = 60;
		this->nowMissileCD = 0;
		this->isMissileCD = true;
	}

	Weapon ^ LJP::Attack(Coordinate target)
	{
		// 判斷要攻擊的座標是否在攻擊範圍
		if (target.x < 0 || target.x > BATTLEGRID_NUM ||
			target.y < 0 || target.y > BATTLEGRID_NUM ||
			(target.x - this->location->X / BATTLEGRID_SIZE) * (target.x - this->location->X / BATTLEGRID_SIZE) + (target.y - this->location->Y / BATTLEGRID_SIZE) * (target.y - this->location->Y / BATTLEGRID_SIZE) > this->maxAttackDistance * this->maxAttackDistance)
		{
			throw VESSEL_ERROR::ATTACK_ERROR;
		}

		// 若還在CD
		if (!isAttackCD)
		{
			throw VESSEL_ERROR::ATTACK_ERROR;
		}

		// 進入CD時間
		nowAttackCD = attackCD;
		isAttackCD = false;

		// 創造 Weapon 並回傳
		// weaponName = "Shell_[team][id]"
		std::string weaponName = "Shell_" + msclr::interop::marshal_as<std::string>(this->team->name->ToString()) + std::to_string(this->team->weaponID);

		++this->team->weaponID;

		return gcnew Weapon(Coordinate(this->location->X / BATTLEGRID_SIZE, this->location->Y / BATTLEGRID_SIZE), weaponName, 5, 5, 1.5, Coordinate(target.x, target.y));
	}

	Missile ^ LJP::missileAttack(Vessel ^ vesselTarget)
	{
		// 若還在CD
		if (!isMissileCD)
		{
			throw VESSEL_ERROR::ATTACK_ERROR;
		}

		// 進入CD時間
		nowMissileCD = missileCD;
		isMissileCD = false;

		// 創造 Weapon 並回傳
		// weaponName = "Missile_[team][id]"
		std::string weaponName = "Missile_" + msclr::interop::marshal_as<std::string>(this->team->name->ToString()) + std::to_string(this->team->weaponID);

		++this->team->weaponID;

		// 導彈攻擊範圍需要大於所有艦種的最高秒速
		return gcnew Missile(Coordinate(this->location->X / BATTLEGRID_SIZE, this->location->Y / BATTLEGRID_SIZE), weaponName, 3, 12, 0.2, vesselTarget, Coordinate(vesselTarget->doubleLocation->x, vesselTarget->doubleLocation->y));
	}

	void LJP::Update()
	{
		Vessel::Update();

		if (!this->isMissileCD)
		{
			this->nowMissileCD -= 1;
			if (this->nowMissileCD <= 0)
			{
				isMissileCD = true;
			}
		}
	}
}