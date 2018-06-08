#pragma once
#include <string>

namespace Project3_SeaBattleSim {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Basic Weapon
	public ref class Weapon : public System::Windows::Forms::Label
	{
	public:
		// Constructor
		Weapon();
		Weapon(std::string name, double damage, double speed, double range, Point location, Point target);

		// Other Functions
		void update();

		// Data Member
		// Weapon Damage
		double damage;

		// Weapon Speed (Distance per Minute)
		double speed;

		// Damagine Range
		double range;

		// Attacking Target
		Point target;
	};
}
