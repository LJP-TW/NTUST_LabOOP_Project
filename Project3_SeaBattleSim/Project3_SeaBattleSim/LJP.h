#pragma once
#include "Vessel.h"
#include "Missile.h"

namespace Project3_SeaBattleSim {

	public ref class LJP : public Vessel
	{
	public:
		// Constructor
		LJP(void);
		LJP(Coordinate location, std::string name, Team^ team);

		/*                   */
		/* Virtual Functions */
		/*                   */

		// 基本砲彈攻擊 : 產生 Weapon 並回傳此 Weapon 的 Pointer
		// throw (VESSEL_ERROR::ATTACK_ERROR)
		virtual Weapon^ Attack(Coordinate target) override;

		// 進階導彈攻擊 : 產生 Weapon 並回傳此 Weapon 的 Pointer
		// throw (VESSEL_ERROR::ATTACK_ERROR)
		virtual Missile^ missileAttack(Vessel ^ vesselTarget);

		// 每一遊戲秒更新 : 做移動, -CD 之類的事情
		virtual void Update() override;

		/*              */
		/* Data Members */
		/*              */

		// Cool Down of Missile Attacking
		unsigned int missileCD;

		// Current Missile attacking CD time
		unsigned int nowMissileCD;
		bool isMissileCD;
	};
}