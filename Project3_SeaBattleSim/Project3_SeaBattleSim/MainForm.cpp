#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include <map>
#include <msclr\marshal_cppstd.h>
#include "MainForm.h"
#include "CommonStruct.h"
#include "DefineMacros.h"

namespace Project3_SeaBattleSim
{
	MainForm::MainForm(void)
	{
		InitializeComponent();
	}

	void MainForm::update()
	{
	}

	void MainForm::render()
	{
	}

	MainForm::~MainForm()
	{
		if (components)
		{
			delete components;
		}
	}

	void MainForm::InitializeComponent(void)
	{
		this->components = (gcnew System::ComponentModel::Container());
		this->SuspendLayout();
		// 
		// MainForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(340, 370);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Name = L"MainForm";
		this->Text = L"海戰模擬器";
		this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
		this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::MainForm_Paint);
		this->ResumeLayout(false);
	}

	System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
	{
		// Create Battle Grids by using the background color of labels
		battleGridsH = gcnew array<System::Windows::Forms::Label^>(BATTLEGRID_NUM + 1);
		battleGridsV = gcnew array<System::Windows::Forms::Label^>(BATTLEGRID_NUM + 1);

		for (int i = 0; i <= BATTLEGRID_NUM; ++i)
		{
			battleGridsH[i] = gcnew System::Windows::Forms::Label();
			battleGridsH[i]->BackColor = System::Drawing::Color::Black;
			battleGridsH[i]->Location = System::Drawing::Point(BATTLEGRID_PADDING, BATTLEGRID_PADDING + BATTLEGRID_SIZE * i);
			battleGridsH[i]->Size = System::Drawing::Size(BATTLEGRID_SIZE * BATTLEGRID_NUM + 1, 1);
			battleGridsH[i]->AutoSize = false;
		}
		for (int i = 0; i <= BATTLEGRID_NUM; ++i)
		{
			battleGridsV[i] = gcnew System::Windows::Forms::Label();
			battleGridsV[i]->BackColor = System::Drawing::Color::Black;
			battleGridsV[i]->Location = System::Drawing::Point(BATTLEGRID_PADDING + BATTLEGRID_SIZE * i, BATTLEGRID_PADDING);
			battleGridsV[i]->Size = System::Drawing::Size(1, BATTLEGRID_SIZE * BATTLEGRID_NUM + 1);
			battleGridsV[i]->AutoSize = false;
		}

		// Create Battle Grids Group Box
		battleGridsPanel = gcnew System::Windows::Forms::Panel();
		battleGridsPanel->Location = System::Drawing::Point(BATTLEGRID_LOCATION_X, BATTLEGRID_LOCATION_Y);
		battleGridsPanel->Size = System::Drawing::Size(BATTLEGRID_PADDING * 2 + 3 + BATTLEGRID_SIZE * BATTLEGRID_NUM, BATTLEGRID_PADDING * 2 + 3 + BATTLEGRID_SIZE * BATTLEGRID_NUM);
		battleGridsPanel->Name = L"battleGridsGroupBox";
		battleGridsPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

		// Create clock which show the time of game
		timeShower = gcnew System::Windows::Forms::Label();
		timeShower->BackColor = System::Drawing::Color::LightBlue;
		timeShower->Location = System::Drawing::Point(battleGridsPanel->Location.X, battleGridsPanel->Location.Y + battleGridsPanel->Size.Height + 10);
		timeShower->Size = System::Drawing::Size(75, 25);
		timeShower->AutoSize = false;
		timeShower->Text = "00:00";
		timeShower->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

		// Create Pause & Start Buttons
		pauseButton = gcnew System::Windows::Forms::Button();
		pauseButton->Location = System::Drawing::Point(timeShower->Location.X + timeShower->Size.Width + 10, timeShower->Location.Y);
		pauseButton->Size = System::Drawing::Size(75, 25);
		pauseButton->AutoSize = false;
		pauseButton->Text = "Pause";
		pauseButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		pauseButton->Click += gcnew System::EventHandler(this, &MainForm::pauseButton_Click);
		pauseButton->Enabled = false;

		startButton = gcnew System::Windows::Forms::Button();
		startButton->Location = System::Drawing::Point(pauseButton->Location.X + pauseButton->Size.Width + 10, pauseButton->Location.Y);
		startButton->Size = System::Drawing::Size(75, 25);
		startButton->AutoSize = false;
		startButton->Text = "Start";
		startButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		startButton->Click += gcnew System::EventHandler(this, &MainForm::startButton_Click);

		// Create Command Group Box
		commandGroupBox = gcnew System::Windows::Forms::GroupBox();
		commandGroupBox->Location = System::Drawing::Point(battleGridsPanel->Location.X + battleGridsPanel->Size.Width + 30, battleGridsPanel->Location.Y);
		commandGroupBox->Size = System::Drawing::Size(200, timeShower->Location.Y - battleGridsPanel->Location.Y + timeShower->Size.Height);
		commandGroupBox->Name = L"commandGroupBox";
		commandGroupBox->Text = L"Command";

		// Create Log Group Box
		logGroupBox = gcnew System::Windows::Forms::GroupBox();
		logGroupBox->Location = System::Drawing::Point(commandGroupBox->Location.X + commandGroupBox->Size.Width + 10, commandGroupBox->Location.Y);
		logGroupBox->Size = System::Drawing::Size(commandGroupBox->Size);
		logGroupBox->Name = L"logGroupBox";
		logGroupBox->Text = L"Battle Log";

		// Create A/BTeam Command TextBox
		ATeamCommandTextBox = gcnew System::Windows::Forms::TextBox();
		ATeamCommandTextBox->Location = System::Drawing::Point(10, 20);
		ATeamCommandTextBox->Multiline = true;
		ATeamCommandTextBox->Name = L"ATeamCommandTextBox";
		ATeamCommandTextBox->Size = System::Drawing::Size(commandGroupBox->Size.Width - 20, (commandGroupBox->Size.Height - 40) / 2);

		BTeamCommandTextBox = gcnew System::Windows::Forms::TextBox();
		BTeamCommandTextBox->Location = System::Drawing::Point(10, ATeamCommandTextBox->Location.Y + ATeamCommandTextBox->Size.Height + 10);
		BTeamCommandTextBox->Multiline = true;
		BTeamCommandTextBox->Name = L"BTeamCommandTextBox";
		BTeamCommandTextBox->Size = System::Drawing::Size(commandGroupBox->Size.Width - 20, (commandGroupBox->Size.Height - 40) / 2);

		// Create Log TextBox
		LogTextBox = gcnew System::Windows::Forms::TextBox();
		LogTextBox->Location = System::Drawing::Point(10, 20);
		LogTextBox->Multiline = true;
		LogTextBox->Name = L"LogTextBox";
		LogTextBox->Size = System::Drawing::Size(logGroupBox->Size.Width - 20, logGroupBox->Size.Height - 30);
		LogTextBox->Enabled = false;
		LogTextBox->BackColor = System::Drawing::Color::White;

		// Initial Game Timer
		gameTimer = gcnew System::Windows::Forms::Timer(this->components);
		gameTimer->Interval = 15 / 15;
		gameTimer->Enabled = false;
		gameTimer->Tick += gcnew System::EventHandler(this, &MainForm::MainForm_Update);

		// Adding components to GroupBox
		for (int i = 0; i <= BATTLEGRID_NUM; ++i)
		{
			battleGridsPanel->Controls->Add(battleGridsH[i]);
			battleGridsPanel->Controls->Add(battleGridsV[i]);
		}

		commandGroupBox->Controls->Add(ATeamCommandTextBox);
		commandGroupBox->Controls->Add(BTeamCommandTextBox);

		logGroupBox->Controls->Add(LogTextBox);
		
		// Adding components to this form
		this->Controls->Add(battleGridsPanel);
		this->Controls->Add(timeShower);
		this->Controls->Add(pauseButton);
		this->Controls->Add(startButton);
		this->Controls->Add(commandGroupBox);
		this->Controls->Add(logGroupBox);
		this->ClientSize = System::Drawing::Size(logGroupBox->Location.X + logGroupBox->Size.Width + 10, timeShower->Location.Y + timeShower->Size.Height + 10);

		
		ATeamVessles = gcnew Dictionary<String^, Vessle^>();
		BTeamVessles = gcnew Dictionary<String^, Vessle^>();
		Weapons = gcnew Dictionary<String^, Weapon^>();
		ATeam = gcnew Team("A");
		BTeam = gcnew Team("B");

		isGameContinued = true;
		gameTime = 0;
	}

	System::Void MainForm::MainForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		// Test Ellipse
		// System::Drawing::SolidBrush^ testBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Red);
		// System::Drawing::Graphics^ formGraphics;
		// formGraphics = this->CreateGraphics();
		// formGraphics->FillEllipse(testBrush, 20, 20, 50, 50);
		// delete testBrush;
		// delete formGraphics;
	}

	void MainForm::MainForm_Update(System::Object^ sender, System::EventArgs^ e)
	{
		++gameTime;

		// Update timeShower
		unsigned long long min;
		unsigned long long sec;

		min = gameTime / 60;
		sec = gameTime % 60;

		std::ostringstream out;
		out << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec;
		timeShower->Text = gcnew System::String(out.str().c_str());

		// 處理 ATeam 指令
		std::stringstream ss(msclr::interop::marshal_as<std::string>(ATeamCommandTextBox->Text));
		std::string cmd;
		while (std::getline(ss, cmd))
		{
			cmd;
		}
		ATeamCommandTextBox->Text = "";
		

		// 處理 BTeam 指令
		ss = std::stringstream(msclr::interop::marshal_as<std::string>(BTeamCommandTextBox->Text));
		while (std::getline(ss, cmd))
		{
			cmd;
		}
		BTeamCommandTextBox->Text = "";

		// 更新所有船隻, 武器
		
	}

	void MainForm::pauseButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		((System::Windows::Forms::Button ^)sender)->Enabled = false;
		startButton->Enabled = true;
		ATeamCommandTextBox->Enabled = true;
		BTeamCommandTextBox->Enabled = true;
		gameTimer->Enabled = false;

		// Testing Code :
		// Add a new vessle to MainForm
		std::string name = "GG";
		String^ str = gcnew String(name.c_str());
		Vessle^ vessle = gcnew Vessle(name, ATeam, 5, 5, 5, 5, 5, 5, Coordinate(2, 2));
		if (!ATeamVessles->ContainsKey(str))
		{
			ATeamVessles->Add(str, vessle);
			this->battleGridsPanel->Controls->Add(vessle);
		}
	}

	void MainForm::startButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		((System::Windows::Forms::Button ^)sender)->Enabled = false;
		pauseButton->Enabled = true;
		ATeamCommandTextBox->Enabled = false;
		BTeamCommandTextBox->Enabled = false;
		gameTimer->Enabled = true;

		// Testing Code :
		// Remove vessle from MainForm
		std::string name = "GG";
		String^ str = gcnew String(name.c_str());
		if (ATeamVessles->ContainsKey(str))
		{
			this->battleGridsPanel->Controls->Remove(ATeamVessles[str]);
			ATeamVessles->Remove(str);
		}
	}
}
