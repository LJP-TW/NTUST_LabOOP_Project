#pragma once
#include <string>
#include "Team.h"
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
	
	public ref class Vessel : public System::Windows::Forms::Panel
	{
	public:
		// Constructor
		Vessel(void);
		Vessel(Coordinate location, std::string name, Team^ team, double hp, double maxSpeed, double maxAttackDistance, unsigned int attackCD, double maxDefenseDistance, unsigned int defenseCD);
		
		/*                           */
		/* Functions called by Event */
		/*                           */
		
		// Do something that cannot write in constructor 
		System::Void Vessel_InitialPaint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);

		// Render the display
		System::Void Vessel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);

		/*                   */
		/* Virtual Functions */
		/*                   */

		// 設定速度, 回傳是否設定成功
		virtual bool setSpeed(double speed);

		// 設定角度
		virtual void setAngle(double angle);

		// 每一遊戲秒更新 : 做移動, -CD 之類的事情
		virtual void Update();
		
		/*              */
		/* Data Members */
		/*              */

		// The actual location of vessel
		Point^ location;

		// More preciser location
		Coordinate* doubleLocation;

		// The label that records the properties such as Location, Font, Text of string of vessel
		// This Label wiil not display out, it's just used to records some information.
		Label^ text;

		// The corner that actual location of vessel is located
		Corner* corner;

		// Team Pointer
		Team^ team;

		// Health Point
		double hp;

		// Max Speed (Distance per Minute)
		double maxSpeed;

		// Max Attacking Distance
		double maxAttackDistance;

		// Cool Down of Attacking
		unsigned int attackCD;

		// Max Defensing Distance
		double maxDefenseDistance;

		// Cool Down of Defensing
		unsigned int defenseCD;

		// Current Speed (Distance per Minute)
		double nowSpeed;

		// Current Sailing Angle
		double nowAngle;

		// Current attacking CD time
		unsigned int nowAttackCD;
		bool isAttackCD;

		// Current defensing CD time
		unsigned int nowDefenseCD;
		bool isDefenseCD;

	};
}

#include "CV.h"
#include "BB.h"
#include "CG.h"
#include "DD.h"