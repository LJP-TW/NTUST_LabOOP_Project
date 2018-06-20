#pragma once
#include "Weapon.h"
#include "Vessel.h"

namespace Project3_SeaBattleSim {

	public ref class Missile : public Weapon
	{
	public:
		// Constructor
		Missile();
		Missile(Coordinate location, std::string name, double damage, double speed, double range, Vessel^ targetVessel ,Coordinate target);

		/*                   */
		/* Virtual Functions */
		/*                   */

		// 每一遊戲秒更新 : 移動
		virtual void Update() override;

		/*              */
		/* Data Members */
		/*              */

		// Target Vessel
		Vessel^ targetVessel;
	};
}