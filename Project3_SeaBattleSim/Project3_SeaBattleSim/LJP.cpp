#include <string>
#include <msclr\marshal_cppstd.h>
#include "LJP.h"
#include "Weapon.h"

namespace Project3_SeaBattleSim
{
	LJP::LJP(void) :Vessel()
	{
	}

	LJP::LJP(Coordinate location, std::string name, Team ^ team) : Vessel(location, name, team, 10, 5, 30, 15, 20, 15)
	{
		this->missileCD = 25;
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
		// 判斷要攻擊的座標是否在攻擊範圍
		if (vesselTarget->doubleLocation->x < 0 || vesselTarget->doubleLocation->x > BATTLEGRID_NUM ||
			vesselTarget->doubleLocation->y < 0 || vesselTarget->doubleLocation->y > BATTLEGRID_NUM ||
			(vesselTarget->doubleLocation->x - this->location->X / BATTLEGRID_SIZE) * (vesselTarget->doubleLocation->x - this->location->X / BATTLEGRID_SIZE) + 
			(vesselTarget->doubleLocation->y - this->location->Y / BATTLEGRID_SIZE) * (vesselTarget->doubleLocation->y - this->location->Y / BATTLEGRID_SIZE) > this->maxAttackDistance * this->maxAttackDistance)
		{
			throw VESSEL_ERROR::ATTACK_ERROR;
		}

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

		return gcnew Missile(Coordinate(this->location->X / BATTLEGRID_SIZE, this->location->Y / BATTLEGRID_SIZE), weaponName, 3, 3, 0.1, vesselTarget, Coordinate(vesselTarget->doubleLocation->x, vesselTarget->doubleLocation->y));
	}
	void LJP::Update()
	{
		// 移動
		double oldDX = this->doubleLocation->x;
		double oldDY = this->doubleLocation->y;
		this->doubleLocation->x = this->doubleLocation->x + (this->nowSpeed / 60) * cos(nowAngle) * BATTLEGRID_SIZE;
		this->doubleLocation->y = this->doubleLocation->y - (this->nowSpeed / 60) * sin(nowAngle) * BATTLEGRID_SIZE;

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

		// 減CD
		if (!this->isAttackCD)
		{
			this->nowAttackCD -= 1;
			if (this->nowAttackCD <= 0)
			{
				isAttackCD = true;
			}
		}

		if (!this->isMissileCD)
		{
			this->nowMissileCD -= 1;
			if (this->nowMissileCD <= 0)
			{
				isMissileCD = true;
			}
		}

		if (!this->isDefenseCD)
		{
			this->nowDefenseCD -= 1;
			if (this->nowDefenseCD <= 0)
			{
				isDefenseCD = true;
			}
		}
	}
}