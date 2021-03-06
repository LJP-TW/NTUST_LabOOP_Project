#pragma once
#include "Vessel.h"
#include "Weapon.h"
#include "Team.h"
#include "AlertArea.h"
#include "GlobalVariable.h"

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
		System::ComponentModel::IContainer^ components;
		System::ComponentModel::ComponentResourceManager^ resources;
		array<System::Windows::Forms::Label^> ^battleGridsH;
		array<System::Windows::Forms::Label^> ^battleGridsV;
		System::Windows::Forms::Label^ timeShower;
		System::Windows::Forms::Button^ pauseButton;
		System::Windows::Forms::Button^ startButton;
		System::Windows::Forms::Panel^ battleGridsFramePanel;
		System::Windows::Forms::Panel^ battleGridsPanel;
		System::Windows::Forms::GroupBox^ commandGroupBox;
		System::Windows::Forms::GroupBox^ logGroupBox;
		System::Windows::Forms::TextBox^ ATeamCommandTextBox;
		System::Windows::Forms::TextBox^ BTeamCommandTextBox;
		System::Windows::Forms::TextBox^ LogTextBox;
		System::Windows::Forms::Timer^ gameTimer;

		Team^ ATeam;
		Team^ BTeam;

		List<String^>^ DeadATeamVessels;
		List<String^>^ DeadBTeamVessels;
		List<String^>^ HitATeamVessels;
		List<String^>^ HitBTeamVessels;
		List<String^>^ ArrivalWeapons;

		// 圖層
		List<Panel^> PanelLayer;
		AlertArea^ alertArea;
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

		void MainForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);

		void MainForm_Update(System::Object^ sender, System::EventArgs^ e);

		void pauseButton_Click(System::Object^ sender, System::EventArgs^ e);

		void startButton_Click(System::Object^ sender, System::EventArgs^ e);

		/*判斷砲彈攻擊範圍內是否有船隻*/
		bool isInAttackRange(KeyValuePair<String^, Weapon^>^ kvw, KeyValuePair<String^, Vessel^>^ kvv);

		/*判斷船艦防守範圍內是否有砲彈*/
		bool isInDefenseRange(Weapon^ kvw, Vessel^ kvv);
	};
}
