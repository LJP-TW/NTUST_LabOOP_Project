#include <math.h>
#include "Vessel.h"

#define DEGREE_TO_RADIAN(degree) (degree * 3.14159265359 / 180.0)
#define sin(x) sin(DEGREE_TO_RADIAN(x))
#define cos(x) cos(DEGREE_TO_RADIAN(x))

// Used to draw line
#define VECTOR1_X 4
#define VECTOR1_Y 7
#define VECTOR2_X 6
#define VECTOR2_Y 0

extern std::string VESSEL_TYPE[VESSEL_TYPE_NUM] =
{
	"CV",
	"BB",
	"CG",
	"DD"
};

enum XSide
{
	LEFT_SIDE = false,
	RIGHT_SIDE = true
};

enum YSide
{
	UPPER_SIDE = false,
	LOWER_SIDE = true
};

struct Corner
{
	Corner()
	{
		X = LEFT_SIDE;
		Y = UPPER_SIDE;
	}

	// True : Right Side, or Left Side
	bool X;

	// True : Bottom Side, or Top Side
	bool Y;
};

namespace Project3_SeaBattleSim
{
	Vessel::Vessel(void)
	{
		throw gcnew System::NotImplementedException();
	}

	Vessel::Vessel(Coordinate location, std::string name, Team^ team, double hp, double maxSpeed, double maxAttackDistance, unsigned int attackCD, double maxDefenseDistance, unsigned int defenseCD)
	{
		// Initialization
		this->text = gcnew Label();

		// 圖層名稱, 位置, Size, 及其他設定
		this->Name = gcnew String(name.c_str());
		this->Location = Point(0, 0);
		this->Size = Drawing::Size(BATTLEGRID_NUM * BATTLEGRID_SIZE + 1, BATTLEGRID_NUM * BATTLEGRID_SIZE + 1);
		this->BackColor = Color::Transparent;

		// Vessel 顯示的文字的一些相關屬性
		this->text->Text = gcnew String(("▲" + name).c_str());
		this->text->Location = Point(location.x * BATTLEGRID_SIZE, location.y * BATTLEGRID_SIZE);

		// Other Data Members
		this->location = Point(location.x * BATTLEGRID_SIZE, location.y * BATTLEGRID_SIZE);
		this->doubleLocation = new Coordinate(this->location->X, this->location->Y);
		this->corner = new Corner();
		this->corner->X = LEFT_SIDE;
		this->corner->Y = UPPER_SIDE;
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

		// Event
		this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Vessel::Vessel_InitialPaint);
		this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Vessel::Vessel_Paint);
	}

	System::Void Vessel::Vessel_InitialPaint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
	{
		// This function will only be called once when Paint event is invoked at first time
		this->Paint -= gcnew System::Windows::Forms::PaintEventHandler(this, &Vessel::Vessel_InitialPaint);

		// Fixing the size of text
		SizeF tempSize = e->Graphics->MeasureString(this->text->Text, this->text->Font);
		this->text->Size = Drawing::Size(tempSize.Width, tempSize.Height);
	}

	System::Void Vessel::Vessel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
	{
		Pen^ blackPen = gcnew Pen(Color::FromArgb(110, 110, 110), 2.0f);
		SolidBrush^ blackBrush = gcnew SolidBrush(Color::Black);
		Graphics^ graphics = e->Graphics;

		// Draw the information and keep the information be in the battleGrid

		// Draw Line

		// Out of range : Left Side
		bool OOR_L = false;

		// Out of range : Right Side
		bool OOR_R = false;

		// Out of range : Top Side
		bool OOR_T = false;

		// Out of range : Bottom Side
		bool OOR_B = false;

		if (this->text->Location.X + this->text->Size.Width > BATTLEGRID_NUM * BATTLEGRID_SIZE + 1)
		{
			OOR_R = true;
		}
		else if (this->text->Location.X < 0)
		{
			OOR_L = true;
		}

		if (this->text->Location.Y + this->text->Size.Height > BATTLEGRID_NUM * BATTLEGRID_SIZE + 1)
		{
			OOR_B = true;
		}
		else if (this->text->Location.Y < 0)
		{
			OOR_T = true;
		}

		if (OOR_T || OOR_R || OOR_B || OOR_L)
		{
			if (OOR_L && OOR_T)
			{
				this->corner->X = LEFT_SIDE;
				this->corner->Y = UPPER_SIDE;
			}
			else if (OOR_T && OOR_R)
			{
				this->corner->X = RIGHT_SIDE;
				this->corner->Y = UPPER_SIDE;
			}
			else if (OOR_R && OOR_B)
			{
				this->corner->X = RIGHT_SIDE;
				this->corner->Y = LOWER_SIDE;
			}
			else if (OOR_B && OOR_L)
			{
				this->corner->X = LEFT_SIDE;
				this->corner->Y = LOWER_SIDE;
			}
			else if (OOR_T)
			{
				this->corner->Y = UPPER_SIDE;
			}
			else if (OOR_R)
			{
				this->corner->X = RIGHT_SIDE;
			}
			else if (OOR_B)
			{
				this->corner->Y = LOWER_SIDE;
			}
			else if (OOR_L)
			{
				this->corner->X = LEFT_SIDE;
			}
		}

		if (this->corner->Y == UPPER_SIDE)
		{
			if (this->corner->X == LEFT_SIDE)
			{
				graphics->DrawLine(blackPen, Point(location->X, location->Y), Point(location->X + VECTOR1_X, location->Y + VECTOR1_Y));
				graphics->DrawLine(blackPen, Point(location->X + VECTOR1_X, location->Y + VECTOR1_Y), Point(location->X + VECTOR1_X + VECTOR2_X,location->Y + VECTOR1_Y + VECTOR2_Y));
				this->text->Location = Point(location->X + VECTOR1_X + VECTOR2_X, location->Y);
			}
			else
			{
				graphics->DrawLine(blackPen, Point(location->X, location->Y), Point(location->X - VECTOR1_X, location->Y + VECTOR1_Y));
				graphics->DrawLine(blackPen, Point(location->X - VECTOR1_X, location->Y + VECTOR1_Y), Point(location->X - VECTOR1_X - VECTOR2_X, location->Y + VECTOR1_Y + VECTOR2_Y));
				this->text->Location = Point(location->X - (VECTOR1_X + VECTOR2_X) - this->text->Size.Width, location->Y);
			}
		}
		else
		{
			if (this->corner->X == LEFT_SIDE)
			{
				graphics->DrawLine(blackPen, Point(location->X, location->Y), Point(location->X + VECTOR1_X, location->Y - VECTOR1_Y));
				graphics->DrawLine(blackPen, Point(location->X + VECTOR1_X, location->Y - VECTOR1_Y), Point(location->X + VECTOR1_X + VECTOR2_X, location->Y - VECTOR1_Y - VECTOR2_Y));
				this->text->Location = Point(location->X + VECTOR1_X + VECTOR2_X, location->Y - this->text->Size.Height);
			}
			else
			{
				graphics->DrawLine(blackPen, Point(location->X, location->Y), Point(location->X - VECTOR1_X, location->Y - VECTOR1_Y));
				graphics->DrawLine(blackPen, Point(location->X - VECTOR1_X, location->Y - VECTOR1_Y), Point(location->X - VECTOR1_X - VECTOR2_X, location->Y - VECTOR1_Y - VECTOR2_Y));
				this->text->Location = Point(location->X - (VECTOR1_X + VECTOR2_X) - this->text->Size.Width, location->Y - this->text->Size.Height);
			}
		}

		// Draw Text
		graphics->DrawString(this->text->Text, this->text->Font, blackBrush, this->text->Location);

		delete blackPen;
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

		// 將 this->nowAngle 換算成 正最小同位角
		// Do something

	}

	void Vessel::Update()
	{
		// 移動
		this->nowSpeed;
		this->nowAngle;
		double oldDX = this->doubleLocation->x;
		double oldDY = this->doubleLocation->y;
		this->doubleLocation->x = this->doubleLocation->x + (this->nowSpeed / 60) * cos(nowAngle) * BATTLEGRID_SIZE;
		this->doubleLocation->y = this->doubleLocation->y - (this->nowSpeed / 60) * sin(nowAngle) * BATTLEGRID_SIZE;

		// 如果爆出範圍, 則不動
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

		// 如果有移動, 則需重新繪畫
		if (oldX != this->location->X || oldY != this->location->Y)
		{
			this->Refresh();
		}

		// 減CD
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
}