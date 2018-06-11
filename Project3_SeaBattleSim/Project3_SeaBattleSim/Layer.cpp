#include "Layer.h"

namespace Project3_SeaBattleSim
{
	Layer::Layer(void)
	{
	}

	Layer::Layer(std::string name)
	{
		// �ϼh�W��, ��m, Size, �Ψ�L�]�w
		this->Name = gcnew String(name.c_str());
		this->Location = Point(0, 0);
		this->Size = Drawing::Size(BATTLEGRID_NUM * BATTLEGRID_SIZE + 1, BATTLEGRID_NUM * BATTLEGRID_SIZE + 1);
		this->BackColor = Color::Transparent;
	}

	void Layer::Update()
	{	
	}
}