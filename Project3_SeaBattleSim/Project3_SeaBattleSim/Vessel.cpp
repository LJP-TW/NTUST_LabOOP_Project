#include <math.h>
#include "Vessel.h"
#include "Weapon.h"

#define DEGREE_TO_RADIAN(degree) (degree * 3.14159265359 / 180.0)
#define sin(x) sin(DEGREE_TO_RADIAN(x))
#define cos(x) cos(DEGREE_TO_RADIAN(x))

extern std::string VESSEL_TYPE[VESSEL_TYPE_NUM] =
{
	"CV",
	"BB",
	"CG",
	"DD"
};

namespace Project3_SeaBattleSim
{
	Vessel::Vessel(void) : MovableObject()
	{
	}

	Vessel::Vessel(Coordinate location, std::string name, Team^ team, double hp, double maxSpeed, double maxAttackDistance, unsigned int attackCD, double maxDefenseDistance, unsigned int defenseCD) : MovableObject(location, name, "��")
	{
		// Initialization
		this->team = team;
		this->hp = hp;
		this->maxSpeed = maxSpeed;
		this->maxAttackDistance = maxAttackDistance;
		this->attackCD = attackCD;
		this->maxDefenseDistance = maxDefenseDistance;
		this->defenseCD = defenseCD;
		this->nowSpeed = 0;
		this->nowAngle = 0;
		this->nowAttackCD = 0;
		this->isAttackCD = true;
		this->nowDefenseCD = 0;
		this->isDefenseCD = true;
	}

	bool Vessel::setSpeed(double speed)
	{
		if (speed > this->maxSpeed || speed < 0)
		{
			return false;
		}

		this->nowSpeed = speed;

		return true;
	}

	void Vessel::setAngle(double angle)
	{
		this->nowAngle = angle;

		// �N this->nowAngle ���⦨ ���̤p�P�쨤
		// Do something

	}

	void Vessel::Update()
	{
		// ����
		this->nowSpeed;
		this->nowAngle;
		double oldDX = this->doubleLocation->x;
		double oldDY = this->doubleLocation->y;
		this->doubleLocation->x = this->doubleLocation->x + (this->nowSpeed / 60) * cos(nowAngle) * BATTLEGRID_SIZE;
		this->doubleLocation->y = this->doubleLocation->y - (this->nowSpeed / 60) * sin(nowAngle) * BATTLEGRID_SIZE;

		// �p�G�z�X�d��, �h����
		if (this->doubleLocation->x < 0 || this->doubleLocation->x > BATTLEGRID_NUM * BATTLEGRID_SIZE + 1 ||
			this->doubleLocation->y < 0 || this->doubleLocation->y > BATTLEGRID_NUM * BATTLEGRID_SIZE + 1)
		{
			this->doubleLocation->x = oldDX;
			this->doubleLocation->y = oldDY;
		}

		int oldX = this->location->X;
		int oldY = this->location->Y;
		this->location->X = this->doubleLocation->x;
		this->location->Y = this->doubleLocation->y;

		// �p�G������, �h�ݭ��sø�e
		if (oldX != this->location->X || oldY != this->location->Y)
		{
			this->Refresh();
		}

		// ��CD
		if (!this->isAttackCD)
		{
			this->nowAttackCD -= 1;
			if (this->nowAttackCD <= 0)
			{
				isAttackCD = true;
			}
		}

		if (!this->isDefenseCD)
		{
			this->nowDefenseCD -= 1;
			if (this->nowDefenseCD <= 0)
			{
				nowDefenseCD = true;
			}
		}
	}

	Weapon^ Vessel::Attack(Coordinate target)
	{
		// Vessel ���|�Q�Ψӳгy����, �Y�Q�гy, �h Attack �|�^�ǳQ�]�w errorFlag �� Weapon
		// The Default Constructor of Weapon will set the errorFlag
		return gcnew Weapon();
	}
}