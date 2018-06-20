#pragma once
#include "Vessel.h"

namespace Project3_SeaBattleSim {

	public ref class FL : public Vessel
	{
	public:
		// Constructor
		FL(void);
		FL(Coordinate location, std::string name, Team^ team);

		/*                   */
		/* Virtual Functions */
		/*                   */

		// �򥻯��u���� : ���� Weapon �æ^�Ǧ� Weapon �� Pointer
		// throw (VESSEL_ERROR::ATTACK_ERROR)
		virtual Weapon^ Attack(Coordinate target) override;
	};
}