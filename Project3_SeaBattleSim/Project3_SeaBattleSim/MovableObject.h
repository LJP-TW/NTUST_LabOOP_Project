#pragma once
#include <string>
#include "Layer.h"
#include "CommonStruct.h"
#include "DefineMacros.h"

struct Corner;

namespace Project3_SeaBattleSim {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// 圖層
	public ref class MovableObject : public Layer
	{
	public:
		// Constructor
		MovableObject(void);
		MovableObject(Coordinate location, std::string name, std::string text);
		virtual ~MovableObject() override;

		/*                           */
		/* Functions called by Event */
		/*                           */

		// Do something that cannot write in constructor 
		System::Void MoveableObject_InitialPaint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);

		// Render the display
		System::Void MoveableObject_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);

		/*                   */
		/* Virtual Functions */
		/*                   */

		// 每一遊戲秒更新畫面 : 由各個衍生類別決定如何移動
		virtual void Update() override;

		// 重新命名
		virtual void Rename(std::string newName) override;

		/*              */
		/* Data Members */
		/*              */

		// The actual location of this object
		Point^ location;

		// More preciser location
		Coordinate* doubleLocation;

		// The label that records the properties such as Location, Font, Information of this object
		// This Label wiil not display out, it's just used to recording.
		Label^ text;

		// The corner that actual location of this object is located
		Corner* corner;

	};
}