#include <string>
#include <msclr\marshal_cppstd.h>
#include "FL.h"
#include "Weapon.h"

namespace Project3_SeaBattleSim
{
	FL::FL(void) :Vessel()
	{
	}

	FL::FL(Coordinate location, std::string name, Team ^ team) : Vessel(location, name, team, 1, 10, 0, 0, 5, 15)
	{
	}

	Weapon ^ FL::Attack(Coordinate target)
	{
		// Vessel FL doesn't have attack ability.
		throw VESSEL_ERROR::ATTACK_ERROR;
	}
}