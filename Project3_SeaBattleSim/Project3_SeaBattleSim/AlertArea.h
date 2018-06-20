#pragma once
#include <string>
#include "Layer.h"
#include "CommonStruct.h"
#include "DefineMacros.h"
#include "GlobalVariable.h"

namespace Project3_SeaBattleSim {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// 圖層 : 針對飛彈即將降落的區域顯示警告
	public ref class AlertArea : public Layer
	{
	public:
		// Constructor
		AlertArea(void);
		virtual ~AlertArea() override;

		/*                           */
		/* Functions called by Event */
		/*                           */

		// Do something that cannot write in constructor 
		System::Void AlertArea_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);

	};
}