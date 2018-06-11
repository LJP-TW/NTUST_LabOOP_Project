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

		// �򥻯��u���� : ���� Weapon �æ^�Ǧ� Weapon �� Pointer
		virtual Weapon^ Attack(Coordinate target) override;
	};
}