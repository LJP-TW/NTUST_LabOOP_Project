#pragma once
#include "Vessel.h"
#include "Weapon.h"

namespace Project3_SeaBattleSim {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MainForm 的摘要
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void);

		void update();

		void render();

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MainForm();

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>

		// Components
		System::ComponentModel::Container ^components;
		array<System::Windows::Forms::Label^>^ battleGridsFramesH;
		array<System::Windows::Forms::Label^>^ battleGridsFramesV;
		array<System::Windows::Forms::Label^>^ battleGridsH;
		array<System::Windows::Forms::Label^>^ battleGridsV;
		System::Windows::Forms::Label^ timeShower;
		System::Windows::Forms::Button^ pauseButton;
		System::Windows::Forms::Button^ startButton;
		System::Windows::Forms::GroupBox^ commandGroupBox;
		System::Windows::Forms::GroupBox^ logGroupBox;
		System::Windows::Forms::TextBox^ ATeamCommandTextBox;
		System::Windows::Forms::TextBox^ BTeamCommandTextBox;
		System::Windows::Forms::TextBox^ LogTextBox;
		System::Windows::Forms::Timer^ gameTimer;

		// A/BTeam Dictionary, which like 'map' of native c++
		Dictionary<String^, Vessle^>^ ATeam;
		Dictionary<String^, Vessle^>^ BTeam;
		bool isGameContinued;
		unsigned long long gameTime;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void);
#pragma endregion

		System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);

		System::Void MainForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);

		void MainForm_Update(System::Object^ sender, System::EventArgs^ e);

		void pauseButton_Click(System::Object^ sender, System::EventArgs^ e);

		void startButton_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
