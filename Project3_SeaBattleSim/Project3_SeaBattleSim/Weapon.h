#pragma once
#include <string>
#include "MovableObject.h"
#include "CommonStruct.h"
#include "DefineMacros.h"

struct Corner;

namespace Project3_SeaBattleSim {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Basic Weapon
	public ref class Weapon : public MovableObject
	{
	public:
		// Constructor
		Weapon();
		Weapon(Coordinate location, std::string name, double damage, double speed, double range, Coordinate target);

		/*                   */
		/* Virtual Functions */
		/*                   */

		// �C�@�C�����s : ����
		virtual void Update() override;

		/*              */
		/* Data Members */
		/*              */

		// Weapon Damage
		double damage;

		// Weapon Speed (Distance per Minute)
		double speed;

		// Damagine Range
		double range;

		// Attacking Target
		Coordinate* target;

		// Error Flag
		bool isError;
	};
}
