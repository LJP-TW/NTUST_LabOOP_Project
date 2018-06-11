#pragma once
#include "Vessel.h"

namespace Project3_SeaBattleSim {

	public ref class CV : public Vessel
	{
	public:
		// Constructor
		CV(void);
		CV(Coordinate location, std::string name, Team^ team);

		/*                   */
		/* Virtual Functions */
		/*                   */

		// 基本砲彈攻擊 : 產生 Weapon 並回傳此 Weapon 的 Pointer
		virtual Weapon^ Attack(Coordinate target) override;
	};
}