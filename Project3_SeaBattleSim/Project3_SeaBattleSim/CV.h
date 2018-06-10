#pragma once
#include "Vessel.h"

namespace Project3_SeaBattleSim {

	public ref class CV : public Vessel
	{
	public:
		// Constructor
		CV(void);
		CV(Coordinate location, std::string name, Team^ team);

	};
}