#pragma once
#include "Vessel.h"

namespace Project3_SeaBattleSim {

	public ref class DD : public Vessel
	{
	public:
		// Constructor
		DD(void);
		DD(Coordinate location, std::string name, Team^ team);

		/*                   */
		/* Virtual Functions */
		/*                   */

		// 基本砲彈攻擊 : 產生 Weapon 並回傳此 Weapon 的 Pointer
		// throw (VESSEL_ERROR::ATTACK_ERROR)
		virtual Weapon^ Attack(Coordinate target) override;
	};
}