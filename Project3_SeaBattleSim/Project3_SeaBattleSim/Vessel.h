#pragma once
#include <string>
#include "MovableObject.h"
#include "Team.h"
#include "CommonStruct.h"
#include "DefineMacros.h"

struct Corner;

namespace Project3_SeaBattleSim {

	ref class Weapon;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	public ref class Vessel : public MovableObject
	{
	public:
		// Constructor
		Vessel(void);
		Vessel(Coordinate location, std::string name, Team^ team, double hp, double maxSpeed, double maxAttackDistance, unsigned int attackCD, double maxDefenseDistance, unsigned int defenseCD);

		/*                   */
		/* Virtual Functions */
		/*                   */

		// �]�w�t��, �^�ǬO�_�]�w���\
		virtual bool setSpeed(double speed);

		// �]�w����
		virtual void setAngle(double angle);

		// �C�@�C�����s : ������, -CD �������Ʊ�
		virtual void Update() override;

		// �򥻯��u���� : ���� Weapon �æ^�Ǧ� Weapon �� Pointer
		virtual Weapon^ Attack(Coordinate target);
		
		/*              */
		/* Data Members */
		/*              */

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