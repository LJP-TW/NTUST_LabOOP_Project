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

		// 每一遊戲秒更新 : 移動
		virtual void Update() override;

		// 判斷武器是否抵達
		virtual bool isArrival();

		// 判斷武器是否已接近目標
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

		// 是否記錄過靠近目標
		bool hasCloseLogged;
	};
}

#include "Missile.h"