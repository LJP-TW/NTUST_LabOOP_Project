#include <math.h>
#include "Vessel.h"
#include "Weapon.h"

#define M_PI 3.14159265358979323846
#define DEGREE_TO_RADIAN(degree) (degree * M_PI / 180.0)
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

	void Vessel::setSpeed(double speed)
	{
		if (speed > this->maxSpeed || speed < 0)
		{
			throw VESSEL_ERROR::SET_SPEED_ERROR;
		}

		this->nowSpeed = speed;
	}

	void Vessel::setAngle(double angle)
	{
		this->nowAngle = angle;

		// �N this->nowAngle ���⦨ ���̤p�P�쨤 ( �D���n, �i�H���I�A�� )
		// Do something
	}

	void Vessel::Update()
	{
		// ����
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
				isDefenseCD = true;
			}
		}
	}

	Weapon^ Vessel::Attack(Coordinate target)
	{
		// Vessel ���|�Q�Ψӳгy����
		throw VESSEL_ERROR::ATTACK_ERROR;
	}

	void Vessel::Defense()
	{
		// �Y�٦bCD
		if (!isDefenseCD)
		{
			throw VESSEL_ERROR::DEFENSE_ERROR;
		}

		// �i�JCD�ɶ�
		nowDefenseCD = defenseCD;
		isDefenseCD = false;
	}

	void Vessel::getDamage(double damage)
	{
		this->hp -= damage;
	}

	bool Vessel::isDead()
	{
		if (this->hp<=0)
		{
			return true;
		}
		return false;
	}
}