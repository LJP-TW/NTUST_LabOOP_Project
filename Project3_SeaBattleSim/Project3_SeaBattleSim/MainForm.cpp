#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include <map>
#include "MainForm.h"

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
		this->Text = L"®ü¾Ô¼ÒÀÀ¾¹";
		this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
		this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::MainForm_Paint);
		this->ResumeLayout(false);
	}

	System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
	{
		// Create Battle Grids by using the background color of labels
		battleGridsFramesH = gcnew array<System::Windows::Forms::Label^>(2);
		battleGridsFramesV = gcnew array<System::Windows::Forms::Label^>(2);
		battleGridsH = gcnew array<System::Windows::Forms::Label^>(21);
		battleGridsV = gcnew array<System::Windows::Forms::Label^>(21);

		System::Drawing::Point battleGridsFrameLocation(10, 10);
		System::Drawing::Point battleGridsLocation(battleGridsFrameLocation.X + 10, battleGridsFrameLocation.Y + 10);

		for (int i = 0; i < 2; ++i)
		{
			battleGridsFramesH[i] = gcnew System::Windows::Forms::Label();
			battleGridsFramesH[i]->BackColor = System::Drawing::Color::Black;
			battleGridsFramesH[i]->Location = System::Drawing::Point(battleGridsFrameLocation.X, battleGridsFrameLocation.Y + i * 320);
			battleGridsFramesH[i]->Size = System::Drawing::Size(320, 1);
			battleGridsFramesH[i]->AutoSize = false;
		}
		for (int i = 0; i < 2; ++i)
		{
			battleGridsFramesV[i] = gcnew System::Windows::Forms::Label();
			battleGridsFramesV[i]->BackColor = System::Drawing::Color::Black;
			battleGridsFramesV[i]->Location = System::Drawing::Point(battleGridsFrameLocation.X + i * 320, battleGridsFrameLocation.Y);
			battleGridsFramesV[i]->Size = System::Drawing::Size(1, 320);
			battleGridsFramesV[i]->AutoSize = false;
		}

		int gridSize = 15;
		for (int i = 0; i < 21; ++i)
		{
			battleGridsH[i] = gcnew System::Windows::Forms::Label();
			battleGridsH[i]->BackColor = System::Drawing::Color::Black;
			battleGridsH[i]->Location = System::Drawing::Point(battleGridsLocation.X, battleGridsLocation.Y + gridSize * i);
			battleGridsH[i]->Size = System::Drawing::Size(300, 1);
			battleGridsH[i]->AutoSize = false;
		}
		for (int i = 0; i < 21; ++i)
		{
			battleGridsV[i] = gcnew System::Windows::Forms::Label();
			battleGridsV[i]->BackColor = System::Drawing::Color::Black;
			battleGridsV[i]->Location = System::Drawing::Point(battleGridsLocation.X + gridSize * i, battleGridsLocation.Y);
			battleGridsV[i]->Size = System::Drawing::Size(1, 300);
			battleGridsV[i]->AutoSize = false;
		}

		// Create clock which show the time of game
		timeShower = gcnew System::Windows::Forms::Label();
		timeShower->BackColor = System::Drawing::Color::LightBlue;
		timeShower->Location = System::Drawing::Point(battleGridsFramesV[0]->Location.X, battleGridsFramesV[0]->Location.Y + battleGridsFramesV[0]->Size.Height + 10);
		timeShower->Size = System::Drawing::Size(75, 25);
		timeShower->AutoSize = false;
		timeShower->Text = "00:00";
		timeShower->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

		// Create Pause & Start Buttons
		pauseButton = gcnew System::Windows::Forms::Button();
		pauseButton->Location = System::Drawing::Point(timeShower->Location.X + timeShower->Size.Width + 10, battleGridsFramesV[0]->Location.Y + battleGridsFramesV[0]->Size.Height + 10);
		pauseButton->Size = System::Drawing::Size(75, 25);
		pauseButton->AutoSize = false;
		pauseButton->Text = "Pause";
		pauseButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		pauseButton->Click += gcnew System::EventHandler(this, &MainForm::pauseButton_Click);
		pauseButton->Enabled = false;

		startButton = gcnew System::Windows::Forms::Button();
		startButton->Location = System::Drawing::Point(pauseButton->Location.X + pauseButton->Size.Width + 10, battleGridsFramesV[0]->Location.Y + battleGridsFramesV[0]->Size.Height + 10);
		startButton->Size = System::Drawing::Size(75, 25);
		startButton->AutoSize = false;
		startButton->Text = "Start";
		startButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		startButton->Click += gcnew System::EventHandler(this, &MainForm::startButton_Click);

		// Create Command Group Box
		commandGroupBox = gcnew System::Windows::Forms::GroupBox();
		commandGroupBox->Location = System::Drawing::Point(battleGridsFramesH[0]->Location.X + battleGridsFramesH[0]->Size.Width + 30, battleGridsFramesH[0]->Location.Y);
		commandGroupBox->Size = System::Drawing::Size(200, timeShower->Location.Y - battleGridsFramesH[0]->Location.Y + timeShower->Size.Height);
		commandGroupBox->Name = L"commandGroupBox";
		commandGroupBox->TabIndex = 0;
		commandGroupBox->TabStop = false;
		commandGroupBox->Text = L"Command";

		// Create Log Group Box
		logGroupBox = gcnew System::Windows::Forms::GroupBox();
		logGroupBox->Location = System::Drawing::Point(commandGroupBox->Location.X + commandGroupBox->Size.Width + 10, commandGroupBox->Location.Y);
		logGroupBox->Size = System::Drawing::Size(commandGroupBox->Size);
		logGroupBox->Name = L"logGroupBox";
		logGroupBox->TabIndex = 0;
		logGroupBox->TabStop = false;
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
		commandGroupBox->Controls->Add(ATeamCommandTextBox);
		commandGroupBox->Controls->Add(BTeamCommandTextBox);

		logGroupBox->Controls->Add(LogTextBox);
		
		// Adding components to this form
		for (int i = 0; i < 2; ++i)
		{
			this->Controls->Add(battleGridsFramesH[i]);
			this->Controls->Add(battleGridsFramesV[i]);
		}
		for (int i = 0; i < 21; ++i)
		{
			this->Controls->Add(battleGridsH[i]);
			this->Controls->Add(battleGridsV[i]);
		}
		this->Controls->Add(timeShower);
		this->Controls->Add(pauseButton);
		this->Controls->Add(startButton);
		this->Controls->Add(commandGroupBox);
		this->Controls->Add(logGroupBox);
		this->ClientSize = System::Drawing::Size(logGroupBox->Location.X + logGroupBox->Size.Width + 10, timeShower->Location.Y + timeShower->Size.Height + 10);

		ATeam = gcnew Dictionary<String^, Vessle^>();
		BTeam = gcnew Dictionary<String^, Vessle^>();

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
		Vessle^ vessle = gcnew Vessle(name, 5, 5, 5, 5, 5, 5, Point(50, 50));
		if (!ATeam->ContainsKey(str))
		{
			ATeam->Add(str, vessle);
			this->Controls->Add(vessle);
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
		if (ATeam->ContainsKey(str))
		{
			this->Controls->Remove(ATeam[str]);
			ATeam->Remove(str);
		}
	}
}
