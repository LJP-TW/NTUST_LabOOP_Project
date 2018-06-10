#include "CV.h"

Project3_SeaBattleSim::CV::CV(void) : Vessel()
{
}

Project3_SeaBattleSim::CV::CV(Coordinate location, std::string name, Team^ team) : Vessel(location, name, team, 5, 1, 25, 60, 5, 15)
{

}

