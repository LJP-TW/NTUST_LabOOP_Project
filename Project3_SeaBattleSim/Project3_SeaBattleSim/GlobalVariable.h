#pragma once

namespace Project3_SeaBattleSim
{
	ref class Vessel;
	ref class Weapon;

	public ref class GlobalVariable
	{
	public:
		// A/BTeam Dictionary, which like 'map' of native c++
		static System::Collections::Generic::Dictionary<System::String^, Vessel^>^ ATeamVessels;
		static System::Collections::Generic::Dictionary<System::String^, Vessel^>^ BTeamVessels;
		static System::Collections::Generic::Dictionary<System::String^, Weapon^>^ Weapons;
	};
}