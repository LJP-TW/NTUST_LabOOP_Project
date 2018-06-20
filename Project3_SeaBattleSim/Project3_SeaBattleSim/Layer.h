#pragma once
#include <string>
#include "CommonStruct.h"
#include "DefineMacros.h"

namespace Project3_SeaBattleSim {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// 圖層
	public ref class Layer : public System::Windows::Forms::Panel
	{
	public:
		// Constructor
		Layer(void);
		Layer(std::string name);
		virtual ~Layer();

		/*                   */
		/* Virtual Functions */
		/*                   */

		// 每一遊戲秒更新畫面, Layer 不會被實體化, 所以 Layer::Update() 不做任何事情, 由繼承的子類別分別實作
		virtual void Update();

		// 重新命名
		virtual void Rename(std::string newName);
	};
}