#include "CV.h"

namespace Project3_SeaBattleSim
{
	CV::CV(void) : Vessel()
	{
	}

	CV::CV(Coordinate location, std::string name, Team^ team) : Vessel(location, name, team, 5, 1, 25, 60, 5, 15)
	{

	}
}