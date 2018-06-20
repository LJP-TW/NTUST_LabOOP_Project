#pragma once
#include "Vessel.h"
#include "Missile.h"

namespace Project3_SeaBattleSim {

	public ref class LJP : public Vessel
	{
	public:
		// Constructor
		LJP(void);
		LJP(Coordinate location, std::string name, Team^ team);

		/*                   */
		/* Virtual Functions */
		/*                   */

		// �򥻯��u���� : ���� Weapon �æ^�Ǧ� Weapon �� Pointer
		// throw (VESSEL_ERROR::ATTACK_ERROR)
		virtual Weapon^ Attack(Coordinate target) override;

		// �i���ɼu���� : ���� Weapon �æ^�Ǧ� Weapon �� Pointer
		// throw (VESSEL_ERROR::ATTACK_ERROR)
		virtual Missile^ missileAttack(Vessel ^ vesselTarget);

		// �C�@�C�����s : ������, -CD �������Ʊ�
		virtual void Update() override;

		/*              */
		/* Data Members */
		/*              */

		// Cool Down of Missile Attacking
		unsigned int missileCD;

		// Current Missile attacking CD time
		unsigned int nowMissileCD;
		bool isMissileCD;
	};
}