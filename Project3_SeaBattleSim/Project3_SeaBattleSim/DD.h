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

		// �򥻯��u���� : ���� Weapon �æ^�Ǧ� Weapon �� Pointer
		// throw (VESSEL_ERROR::ATTACK_ERROR)
		virtual Weapon^ Attack(Coordinate target) override;
	};
}