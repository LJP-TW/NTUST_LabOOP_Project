#include <cmath>
#include "Weapon.h"
#include "AlertArea.h"

namespace Project3_SeaBattleSim
{
	AlertArea::AlertArea(void) : Layer("AlertArea")
	{
		this->Paint += gcnew PaintEventHandler(this, &AlertArea::AlertArea_Paint);
	}

	AlertArea::~AlertArea()
	{
	}

	System::Void AlertArea::AlertArea_Paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs ^ e)
	{
		Graphics^ graph = e->Graphics;

		for each(KeyValuePair<String^, Weapon^>^ kvpw in GlobalVariable::Weapons)
		{
			int distance = sqrt((kvpw->Value->doubleLocation->x - kvpw->Value->target->x) * (kvpw->Value->doubleLocation->x - kvpw->Value->target->x) + (kvpw->Value->doubleLocation->y - kvpw->Value->target->y) * (kvpw->Value->doubleLocation->y - kvpw->Value->target->y));
			int g = distance < 255 ? distance : 255;
			int b = g;
			SolidBrush^ brush = gcnew SolidBrush(Color::FromArgb(255, g, b));

			// FillEllipse 有兩種多載
			// FillEllipse(Brust^, int * 4)
			// FillEllipse(Brust^, float * 4)
			// 強轉成 float 走第二種多載
			float w = kvpw->Value->range * BATTLEGRID_SIZE * 2;
			float h = kvpw->Value->range * BATTLEGRID_SIZE * 2;
			float x = kvpw->Value->target->x - w / 2;
			float y = kvpw->Value->target->y - h / 2;
			graph->FillEllipse(brush, x, y, w, h);

			delete brush;
		}
	}
}
