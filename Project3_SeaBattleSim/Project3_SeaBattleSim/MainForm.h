#pragma once
#include "Vessel.h"
#include "Weapon.h"
#include "Team.h"
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
	/// MainForm ���K�n
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void);

		void update();

		void render();

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~MainForm();
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		/// </summary>

		// Components

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

		// �ϼh
		List<Panel^> PanelLayer;
		bool isGameContinued;

			 unsigned long long gameTime;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void);
#pragma endregion

		System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);

		void MainForm_Update(System::Object^ sender, System::EventArgs^ e);

		void pauseButton_Click(System::Object^ sender, System::EventArgs^ e);

		void startButton_Click(System::Object^ sender, System::EventArgs^ e);

		/*�P�_���u�����d�򤺬O�_���*/
		bool isInAttackRange(KeyValuePair<String^, Weapon^>^ kvw, KeyValuePair<String^, Vessel^>^ kvv);

		/*�P�_��ĥ���u�d�򤺬O�_�����u*/
		bool isInDefenseRange(Weapon^ kvw, Vessel^ kvv);
	};
}
