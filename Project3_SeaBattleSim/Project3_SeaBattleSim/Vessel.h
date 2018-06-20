#pragma once
#include <string>
#include "MovableObject.h"
#include "Team.h"
#include "CommonStruct.h"
#include "DefineMacros.h"

struct Corner;

namespace Project3_SeaBattleSim {

	ref class Weapon;
	ref class Missile;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	public ref class Vessel : public MovableObject
	{
	public:
		// Constructor
		Vessel(void);
		Vessel(Coordinate location, std::string name, Team^ team, double hp, double maxSpeed, double maxAttackDistance, unsigned int attackCD, double maxDefenseDistance, unsigned int defenseCD);

		/*                   */
		/* Virtual Functions */
		/*                   */

		// 設定速度
		// throw (VESSEL_ERROR::SET_SPEED_ERROR)
		virtual void setSpeed(double speed);

		// 設定角度
		virtual void setAngle(double angle);

		// 每一遊戲秒更新 : 做移動, -CD 之類的事情
		virtual void Update() override;

		// 基本砲彈攻擊 : 產生 Weapon 並回傳此 Weapon 的 Pointer
		virtual Weapon^ Attack(Coordinate target);

		// 進階導彈攻擊 : 產生 Weapon 並回傳此 Weapon 的 Pointer
		// throw (VESSEL_ERROR::ATTACK_ERROR)
		virtual Missile^ missileAttack(Vessel^ vesselTarget);

		// 防禦
		virtual void Defense();

		// 船艦受到傷害 ： 減少HP
		virtual void getDamage(double damage);

		// 判斷船艦死掉了沒
		virtual bool isDead();
		
		/*              */
		/* Data Members */
		/*              */

		// Team Pointer
		Team^ team;

		// Health Point
		double hp;

		// Max Speed (Distance per Minute)
		double maxSpeed;

		// Max Attacking Distance
		double maxAttackDistance;

		// Cool Down of Attacking
		unsigned int attackCD;

		// Max Defensing Distance
		double maxDefenseDistance;

		// Cool Down of Defensing
		unsigned int defenseCD;

		// Current Speed (Distance per Minute)
		double nowSpeed;

		// Current Sailing Angle
		double nowAngle;

		// Current attacking CD time
		unsigned int nowAttackCD;
		bool isAttackCD;

		// Current defensing CD time
		unsigned int nowDefenseCD;
		bool isDefenseCD;

	};
}

#include "CV.h"
#include "BB.h"
#include "CG.h"
#include "DD.h"
#include "FL.h"
#include "LJP.h"