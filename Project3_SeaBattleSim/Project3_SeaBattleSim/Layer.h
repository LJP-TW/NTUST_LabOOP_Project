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

	// �ϼh
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

		// �C�@�C�����s�e��, Layer ���|�Q�����, �ҥH Layer::Update() ��������Ʊ�, ���~�Ӫ��l���O���O��@
		virtual void Update();

		// ���s�R�W
		virtual void Rename(std::string newName);
	};
}