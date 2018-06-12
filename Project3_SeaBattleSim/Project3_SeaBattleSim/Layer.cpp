#include "Layer.h"

namespace Project3_SeaBattleSim
{
	Layer::Layer(void)
	{
	}

	Layer::Layer(std::string name)
	{
		// 圖層名稱, 位置, Size, 及其他設定
		this->Name = gcnew String(name.c_str());
		this->Location = Point(0, 0);
		this->Size = Drawing::Size(BATTLEGRID_NUM * BATTLEGRID_SIZE + 1, BATTLEGRID_NUM * BATTLEGRID_SIZE + 1);
		this->BackColor = Color::Transparent;
	}

	Layer::~Layer()
	{
	}

	void Layer::Update()
	{	
	}

	void Layer::Rename(std::string newName)
	{
		String^ newNameStr = gcnew String(newName.c_str());
		
		if (this->Name->CompareTo(newNameStr))
		{
			delete newNameStr;
			throw LAYER_ERROR::RENAME_ERROR;
		}

		this->Name = newNameStr;
	}
}