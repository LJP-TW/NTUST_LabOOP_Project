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

		// �P�_�Z���O�_��F
		virtual bool isArrival();

		// �P�_�Z���O�_�w����ؼ�
		virtual bool isClose();

		/*              */
		/* Data Members */
		/*              */

		// Weapon Damage
		double damage;

		// Weapon Speed (Distance per Minute)
		double speed;

		// Weapon Angle
		double angle;

		// Damagine Range
		double range;

		// Attacking Target
		Coordinate* target;

		// �O�_�O���L�a��ؼ�
		bool hasCloseLogged;
	};
}

#include "Missile.h"