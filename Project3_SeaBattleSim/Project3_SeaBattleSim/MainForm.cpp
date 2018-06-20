#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <msclr\marshal_cppstd.h>
#include "MainForm.h"
#include "CommonStruct.h"
#include "DefineMacros.h"

#define ToUpper(str) for (char & c : str) c = toupper(c)

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

		GlobalVariable::ATeamVessels->Clear();
		GlobalVariable::BTeamVessels->Clear();
		PanelLayer.Clear();

		delete GlobalVariable::ATeamVessels;
		delete GlobalVariable::BTeamVessels;
		delete GlobalVariable::Weapons;
		delete ATeam;
		delete BTeam;
	}

	void MainForm::InitializeComponent(void)
	{
		this->SuspendLayout();
		// 
		// MainForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(453, 462);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		this->Margin = System::Windows::Forms::Padding(4);
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Name = L"MainForm";
		this->Text = L"海戰模擬器";
		this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
		this->ResumeLayout(false);

	}

	System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
	{
		// Initial
		this->components = (gcnew System::ComponentModel::Container());
		this->resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
		battleGridsH = gcnew array<System::Windows::Forms::Label^>(BATTLEGRID_NUM + 1);
		for (int i = 0; i <= BATTLEGRID_NUM; ++i)
		{
			battleGridsH[i] = gcnew System::Windows::Forms::Label();
		}
		battleGridsV = gcnew array<System::Windows::Forms::Label^>(BATTLEGRID_NUM + 1);
		for (int i = 0; i <= BATTLEGRID_NUM; ++i)
		{
			battleGridsV[i] = gcnew System::Windows::Forms::Label();
		}
		battleGridsFramePanel = gcnew System::Windows::Forms::Panel();
		battleGridsPanel = gcnew System::Windows::Forms::Panel();
		timeShower = gcnew System::Windows::Forms::Label();
		pauseButton = gcnew System::Windows::Forms::Button();
		startButton = gcnew System::Windows::Forms::Button();
		commandGroupBox = gcnew System::Windows::Forms::GroupBox();
		logGroupBox = gcnew System::Windows::Forms::GroupBox();
		ATeamCommandTextBox = gcnew System::Windows::Forms::TextBox();
		BTeamCommandTextBox = gcnew System::Windows::Forms::TextBox();
		LogTextBox = gcnew System::Windows::Forms::TextBox();
		gameTimer = gcnew System::Windows::Forms::Timer(this->components);
		ATeam = gcnew Team("A");
		BTeam = gcnew Team("B");
		DeadATeamVessels = gcnew List<String^>();
		DeadBTeamVessels = gcnew List<String^>();
		ArrivalWeapons = gcnew List<String^>();
		HitATeamVessels = gcnew List<String^>();
		HitBTeamVessels = gcnew List<String^>();
		alertArea = gcnew AlertArea();

		GlobalVariable::ATeamVessels = gcnew Dictionary<String^, Vessel^>();
		GlobalVariable::BTeamVessels = gcnew Dictionary<String^, Vessel^>();
		GlobalVariable::Weapons = gcnew Dictionary<String^, Weapon^>();

		// Create Battle Grids by using the background color of labels

		for (int i = 0; i <= BATTLEGRID_NUM; ++i)
		{
			battleGridsH[i]->BackColor = System::Drawing::Color::Black;
			battleGridsH[i]->Location = System::Drawing::Point(0, BATTLEGRID_SIZE * i);
			battleGridsH[i]->Size = System::Drawing::Size(BATTLEGRID_SIZE * BATTLEGRID_NUM + 1, 1);
			battleGridsH[i]->AutoSize = false;
		}
		for (int i = 0; i <= BATTLEGRID_NUM; ++i)
		{
			battleGridsV[i]->BackColor = System::Drawing::Color::Black;
			battleGridsV[i]->Location = System::Drawing::Point(BATTLEGRID_SIZE * i, 0);
			battleGridsV[i]->Size = System::Drawing::Size(1, BATTLEGRID_SIZE * BATTLEGRID_NUM + 1);
			battleGridsV[i]->AutoSize = false;
		}

		// Create Battle Grids Frame Panel
		battleGridsFramePanel->Controls->Add(battleGridsPanel);
		battleGridsFramePanel->Location = System::Drawing::Point(BATTLEGRID_LOCATION_X, BATTLEGRID_LOCATION_Y);
		battleGridsFramePanel->Size = System::Drawing::Size(BATTLEGRID_PADDING * 2 + 3 + BATTLEGRID_SIZE * BATTLEGRID_NUM, BATTLEGRID_PADDING * 2 + 3 + BATTLEGRID_SIZE * BATTLEGRID_NUM);
		battleGridsFramePanel->Name = L"battleGridsGroupBox";
		battleGridsFramePanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		battleGridsFramePanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"BattleGrids_BackGround")));


		// Create Battle Grids Panel
		for (int i = 0; i <= BATTLEGRID_NUM; ++i)
		{
			battleGridsPanel->Controls->Add(battleGridsH[i]);
			battleGridsPanel->Controls->Add(battleGridsV[i]);
		}
		battleGridsPanel->Location = System::Drawing::Point(BATTLEGRID_PADDING, BATTLEGRID_PADDING);
		battleGridsPanel->Size = System::Drawing::Size(BATTLEGRID_SIZE * BATTLEGRID_NUM + 1, BATTLEGRID_SIZE * BATTLEGRID_NUM + 1);
		battleGridsPanel->Name = L"battleGridsGroupBox";
		battleGridsPanel->BackColor = Color::Transparent;

		// Create clock which show the time of game
		timeShower->BackColor = System::Drawing::Color::LightBlue;
		timeShower->Location = System::Drawing::Point(battleGridsFramePanel->Location.X, battleGridsFramePanel->Location.Y + battleGridsFramePanel->Size.Height + 10);
		timeShower->Size = System::Drawing::Size(75, 25);
		timeShower->AutoSize = false;
		timeShower->Text = "00:00";
		timeShower->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		timeShower->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

		// Create Pause & Start Buttons
		pauseButton->Location = System::Drawing::Point(timeShower->Location.X + timeShower->Size.Width + 10, timeShower->Location.Y);
		pauseButton->Size = System::Drawing::Size(75, 25);
		pauseButton->AutoSize = false;
		pauseButton->Text = "Pause";
		pauseButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		pauseButton->Click += gcnew System::EventHandler(this, &MainForm::pauseButton_Click);
		pauseButton->Enabled = false;
		pauseButton->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		pauseButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Button_BackGround")));

		startButton->Location = System::Drawing::Point(pauseButton->Location.X + pauseButton->Size.Width + 10, pauseButton->Location.Y);
		startButton->Size = System::Drawing::Size(75, 25);
		startButton->AutoSize = false;
		startButton->Text = "Start";
		startButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		startButton->Click += gcnew System::EventHandler(this, &MainForm::startButton_Click);
		startButton->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		startButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Button_BackGround")));

		// Create Command Group Box
		commandGroupBox->Controls->Add(ATeamCommandTextBox);
		commandGroupBox->Controls->Add(BTeamCommandTextBox);
		commandGroupBox->Location = System::Drawing::Point(battleGridsFramePanel->Location.X + battleGridsFramePanel->Size.Width + 30, battleGridsFramePanel->Location.Y);
		commandGroupBox->Size = System::Drawing::Size(200, timeShower->Location.Y - battleGridsFramePanel->Location.Y + timeShower->Size.Height);
		commandGroupBox->Name = L"commandGroupBox";
		commandGroupBox->Text = L"Command";
		commandGroupBox->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		commandGroupBox->BackColor = Color::Transparent;

		// Create Log Group Box
		logGroupBox->Controls->Add(LogTextBox);
		logGroupBox->Location = System::Drawing::Point(commandGroupBox->Location.X + commandGroupBox->Size.Width + 10, commandGroupBox->Location.Y);
		logGroupBox->Size = System::Drawing::Size(450, commandGroupBox->Size.Height);
		logGroupBox->Name = L"logGroupBox";
		logGroupBox->Text = L"Battle Log";
		logGroupBox->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 14, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		logGroupBox->BackColor = Color::Transparent;

		// Create A/BTeam Command TextBox
		ATeamCommandTextBox->Location = System::Drawing::Point(10, 30);
		ATeamCommandTextBox->Multiline = true;
		ATeamCommandTextBox->Name = L"ATeamCommandTextBox";
		ATeamCommandTextBox->Size = System::Drawing::Size(commandGroupBox->Size.Width - 20, (commandGroupBox->Size.Height - 50) / 2);
		ATeamCommandTextBox->Font = (gcnew System::Drawing::Font(L"Verdana", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));

		BTeamCommandTextBox->Location = System::Drawing::Point(10, ATeamCommandTextBox->Location.Y + ATeamCommandTextBox->Size.Height + 10);
		BTeamCommandTextBox->Multiline = true;
		BTeamCommandTextBox->Name = L"BTeamCommandTextBox";
		BTeamCommandTextBox->Size = System::Drawing::Size(commandGroupBox->Size.Width - 20, (commandGroupBox->Size.Height - 50) / 2);
		BTeamCommandTextBox->Font = (gcnew System::Drawing::Font(L"Verdana", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));

		// Create Log TextBox
		LogTextBox->Location = System::Drawing::Point(10, 30);
		LogTextBox->Multiline = true;
		LogTextBox->Name = L"LogTextBox";
		LogTextBox->Size = System::Drawing::Size(logGroupBox->Size.Width - 20, logGroupBox->Size.Height - 40);
		LogTextBox->Enabled = false;
		LogTextBox->BackColor = System::Drawing::Color::White;
		LogTextBox->Font = (gcnew System::Drawing::Font(L"Verdana", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));

		// Initial Game Timer
		gameTimer->Interval = 1000 / 15;
		gameTimer->Enabled = false;
		gameTimer->Tick += gcnew System::EventHandler(this, &MainForm::MainForm_Update);

		// Adding components to this form
		this->Controls->Add(battleGridsFramePanel);
		this->Controls->Add(timeShower);
		this->Controls->Add(pauseButton);
		this->Controls->Add(startButton);
		this->Controls->Add(commandGroupBox);
		this->Controls->Add(logGroupBox);
		this->ClientSize = System::Drawing::Size(logGroupBox->Location.X + logGroupBox->Size.Width + 24, timeShower->Location.Y + timeShower->Size.Height + 24);
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"Icon")));

		// Draw BackGroundImage
		this->Paint += gcnew PaintEventHandler(this, &MainForm::MainForm_Paint);

		// 底層 Layer
		PanelLayer.Add(alertArea);
		this->battleGridsPanel->Controls->Add(alertArea);

		isGameContinued = true;
		gameTime = 0;
	}

	void MainForm::MainForm_Paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs ^ e)
	{
		Image^ img = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"MainForm_BackGround")));
		e->Graphics->DrawImage(img, 0, 0);
		delete img;
	}

	void MainForm::MainForm_Update(System::Object^ sender, System::EventArgs^ e)
	{
		unsigned long long min;
		unsigned long long sec;
		bool alertAreaNeedRefresh = false;

		++gameTime;

		// Update timeShower
		min = gameTime / 60;
		sec = gameTime % 60;

		std::ostringstream out;
		out << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec;
		timeShower->Text = gcnew System::String(out.str().c_str());

		// 每艘船跟每顆砲彈都是一個"圖層"
		// 用這個方法來消除 重疊物件會顯示不出來 的BUG

		// Weapon 更新
		for each(KeyValuePair<String^, Weapon^>^ kvpw in GlobalVariable::Weapons)
		{
			/*同點上 船受到傷害 若生命歸零 則移除船*/
			if (kvpw->Value->isArrival())
			{
				ArrivalWeapons->Add(kvpw->Key);

				for each(KeyValuePair<String^, Vessel^>^ kvpv in GlobalVariable::ATeamVessels)
				{
					//Same Location Ship and Weapon
					if (isInAttackRange(kvpw, kvpv))
					{
						HitATeamVessels->Add(kvpv->Key);
						kvpv->Value->getDamage(kvpw->Value->damage);
						//Remove From Dictionary
						if (kvpv->Value->isDead())
						{
							DeadATeamVessels->Add(kvpv->Key);

							for (int i = 0; i < PanelLayer.Count; i++)
							{
								if (PanelLayer[i] == kvpv->Value)
								{
									if (i == 0)
									{
										this->battleGridsPanel->Controls->Remove(PanelLayer[i]);
									}
									else
									{
										PanelLayer[i - 1]->Controls->Remove(PanelLayer[i]);
									}

									if (i + 1 < PanelLayer.Count)
									{
										if (i == 0)
										{
											this->battleGridsPanel->Controls->Add(PanelLayer[i + 1]);
										}
										else
										{
											PanelLayer[i - 1]->Controls->Add(PanelLayer[i + 1]);
										}
									}
									PanelLayer.Remove(PanelLayer[i]);
									break;
								}
							}
						}
					}
				}

				for each(KeyValuePair<String^, Vessel^>^ kvpv in GlobalVariable::BTeamVessels)
				{
					//Same Location Ship and Weapon
					if (isInAttackRange(kvpw, kvpv))
					{
						HitBTeamVessels->Add(kvpv->Key);
						kvpv->Value->getDamage(kvpw->Value->damage);
						//Remove From Dictionary
						if (kvpv->Value->isDead())
						{
							DeadBTeamVessels->Add(kvpv->Key);

							for (int i = 0; i < PanelLayer.Count; i++)
							{
								if (PanelLayer[i] == kvpv->Value)
								{
									if (i == 0)
									{
										this->battleGridsPanel->Controls->Remove(PanelLayer[i]);
									}
									else
									{
										PanelLayer[i - 1]->Controls->Remove(PanelLayer[i]);
									}

									if (i + 1 < PanelLayer.Count)
									{
										if (i == 0)
										{
											this->battleGridsPanel->Controls->Add(PanelLayer[i + 1]);
										}
										else
										{
											PanelLayer[i - 1]->Controls->Add(PanelLayer[i + 1]);
										}
									}
									PanelLayer.Remove(PanelLayer[i]);
									break;
								}
							}
						}
					}
				}

				// Log
				if (HitATeamVessels->Count + HitBTeamVessels->Count == 0)
				{
					std::ostringstream out;
					out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << "] "
						<< msclr::interop::marshal_as<std::string>(kvpw->Key) << " arrived (" << (kvpw->Value->target->x / BATTLEGRID_SIZE) << ',' << (kvpw->Value->target->y / BATTLEGRID_SIZE) << ')'
						<< " -> miss";

					String^ msg = gcnew System::String(out.str().c_str());
					LogTextBox->AppendText(msg);
					LogTextBox->AppendText(Environment::NewLine);
					delete msg;
				}
				else
				{
					bool firstVessel = true;
					std::ostringstream out;
					out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << "] "
						<< msclr::interop::marshal_as<std::string>(kvpw->Key) << " arrived (" << (kvpw->Value->target->x / BATTLEGRID_SIZE) << ',' << (kvpw->Value->target->y / BATTLEGRID_SIZE) << ')'
						<< " -> hit { ";
					for (int i = 0; i < HitATeamVessels->Count; ++i)
					{
						if (firstVessel)
						{
							out << "TeamA " << msclr::interop::marshal_as<std::string>(HitATeamVessels[i]);
							firstVessel = false;
						}
						else
						{
							out << ", TeamA " << msclr::interop::marshal_as<std::string>(HitATeamVessels[i]);
						}
					}
					for (int i = 0; i < HitBTeamVessels->Count; ++i)
					{
						if (firstVessel)
						{
							out << "TeamB " << msclr::interop::marshal_as<std::string>(HitBTeamVessels[i]);
							firstVessel = false;
						}
						else
						{
							out << ", TeamB " << msclr::interop::marshal_as<std::string>(HitBTeamVessels[i]);
						}
					}
					out << '}';

					String^ msg = gcnew System::String(out.str().c_str());
					LogTextBox->AppendText(msg);
					LogTextBox->AppendText(Environment::NewLine);
					delete msg;

					HitATeamVessels->Clear();
					HitBTeamVessels->Clear();
				}

				for each(String^ name in DeadATeamVessels)
				{
					// Log
					std::ostringstream out;
					out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
						<< " TeamA " << msclr::interop::marshal_as<std::string>(name) << " destroyed";

					String^ msg = gcnew System::String(out.str().c_str());
					LogTextBox->AppendText(msg);
					LogTextBox->AppendText(Environment::NewLine);
					delete msg;

					delete GlobalVariable::ATeamVessels[name];
					GlobalVariable::ATeamVessels->Remove(name);
				}

				for each(String^ name in DeadBTeamVessels)
				{
					// Log
					std::ostringstream out;
					out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
						<< " TeamB " << msclr::interop::marshal_as<std::string>(name) << " destroyed";

					String^ msg = gcnew System::String(out.str().c_str());
					LogTextBox->AppendText(msg);
					LogTextBox->AppendText(Environment::NewLine);
					delete msg;

					delete GlobalVariable::BTeamVessels[name];
					GlobalVariable::BTeamVessels->Remove(name);
				}

				DeadATeamVessels->Clear();
				DeadBTeamVessels->Clear();

				for (int i = 0; i < PanelLayer.Count; i++)
				{
					if (PanelLayer[i] == kvpw->Value)
					{
						if (i == 0)
						{
							this->battleGridsPanel->Controls->Remove(PanelLayer[i]);
						}
						else
						{
							PanelLayer[i - 1]->Controls->Remove(PanelLayer[i]);
						}

						if (i + 1 < PanelLayer.Count)
						{
							if (i == 0)
							{
								this->battleGridsPanel->Controls->Add(PanelLayer[i + 1]);
							}
							else
							{
								PanelLayer[i - 1]->Controls->Add(PanelLayer[i + 1]);
							}
						}
						PanelLayer.Remove(PanelLayer[i]);
						break;
					}
				}

				alertAreaNeedRefresh = true;
			}
			else
			{
				kvpw->Value->Update();
			}
		}
		for each (String^ name in ArrivalWeapons)
		{
			delete GlobalVariable::Weapons[name];
			GlobalVariable::Weapons->Remove(name);
		}
		ArrivalWeapons->Clear();

		if (alertAreaNeedRefresh)
		{
			alertArea->Refresh();
		}

		// ATeam 船隻更新
		for each(KeyValuePair<String^, Vessel^>^ kvp in GlobalVariable::ATeamVessels)
		{
			kvp->Value->Update();
		}

		// BTeam 船隻更新
		for each(KeyValuePair<String^, Vessel^>^ kvp in GlobalVariable::BTeamVessels)
		{
			kvp->Value->Update();
		}
	}

	void MainForm::pauseButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		((System::Windows::Forms::Button ^)sender)->Enabled = false;
		startButton->Enabled = true;
		ATeamCommandTextBox->Enabled = true;
		BTeamCommandTextBox->Enabled = true;
		gameTimer->Enabled = false;
	}

	void MainForm::startButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		((System::Windows::Forms::Button ^)sender)->Enabled = false;
		pauseButton->Enabled = true;
		ATeamCommandTextBox->Enabled = false;
		BTeamCommandTextBox->Enabled = false;

		/*Log use min and sec*/
		unsigned long long min;
		unsigned long long sec;

		min = gameTime / 60;
		sec = gameTime % 60;

		// Handling Command
		// 處理 ATeam 指令
		std::stringstream ss(msclr::interop::marshal_as<std::string>(ATeamCommandTextBox->Text));
		std::string cmdLine, command;
		char skip1, skip2;

		while (std::getline(ss, cmdLine))
		{
			std::stringstream tempSS(cmdLine);
			tempSS >> command;

			ToUpper(command);

			try
			{
				if (command == "SET")
				{
					std::string vesselName, type;
					Coordinate coordinate(0, 0);
					bool isInType = false;

					// Get Input
					tempSS >> vesselName;
					tempSS >> type;
					tempSS >> skip1;
					tempSS >> coordinate.x;
					tempSS >> skip2;
					tempSS >> coordinate.y;

					try
					{
						// 判斷船艦不能重複
						String^ str = gcnew String(vesselName.c_str());																			
						if (GlobalVariable::ATeamVessels->ContainsKey(str))
						{
							throw CMD_SET_ERROR::VESSEL_NAME_ERROR;
						}
						
						// Type 必須出現在艦種裡
						for (const std::string& vt : VESSEL_TYPE)
						{
							if (type == vt)
							{
								isInType = true;
								break;
							}
						}
						if (isInType == false)
						{
							throw CMD_SET_ERROR::TYPE_NOT_EXIST;
						}

						// 座標的範圍在(0.0 ~ 20.0, 0.0 ~ 20.0)
						if (coordinate.x < 0 || coordinate.x > BATTLEGRID_NUM || coordinate.y < 0 || coordinate.y > BATTLEGRID_NUM)
						{
							throw CMD_SET_ERROR::COORDINATE_ERROR;
						}

						//skip1 = '(' ; skip2 = ','
						if (skip1 != '(' || skip2 != ',')
						{
							throw CMD_FORMAT_ERROR::FORMAT_ERROR;
						}			

						// 新增船艦圖層
						Vessel^ vessel;
						if (type == "CV")
						{
							vessel = gcnew CV(coordinate, vesselName, ATeam);
						}
						else if (type == "BB")
						{
							vessel = gcnew BB(coordinate, vesselName, ATeam);
						}
						else if (type == "CG")
						{
							vessel = gcnew CG(coordinate, vesselName, ATeam);
						}
						else if (type == "DD")
						{
							vessel = gcnew DD(coordinate, vesselName, ATeam);
						}
						else if (type == "FL")
						{
							vessel = gcnew FL(coordinate, vesselName, ATeam);
						}
						else if(type == "LJP")
						{
							vessel = gcnew LJP(coordinate, vesselName, ATeam);
						}

						// 設定船艦文字顏色
						vessel->text->ForeColor = Color::FromArgb(0, 255, 0);

						// 加入船艦圖層, 若此圖層為第一層, 則上一個容器為 this battleGridsPanel
						GlobalVariable::ATeamVessels->Add(str, vessel);
						if (PanelLayer.Count == 0)
						{
							this->battleGridsPanel->Controls->Add(vessel);
							PanelLayer.Add(vessel);
						}
						else
						{
							PanelLayer[PanelLayer.Count - 1]->Controls->Add(vessel);
							PanelLayer.Add(vessel);
						}
						
						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA SET " << vesselName << " with " << type << " at " << '(' << coordinate.x << ',' << coordinate.y
							<< ')' << " ->Success";
						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
					catch (...)
					{
						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA SET " << vesselName << " with " << type << " at " << '(' << coordinate.x << ',' << coordinate.y
							<< ')' << " ->Fail";
						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else if (command == "FIRE")
				{
					std::string vesselName;
					Coordinate coordinate(0, 0);

					// Get Input
					tempSS >> vesselName;
					tempSS >> skip1;
					tempSS >> coordinate.x;
					tempSS >> skip2;
					tempSS >> coordinate.y;

					try
					{
						// 該隊必須存在該船艦
						String^ str = gcnew String(vesselName.c_str());
						if (!GlobalVariable::ATeamVessels->ContainsKey(str))
						{
							throw CMD_FIRE_ERROR::VESSEL_NOT_EXIST;
						}

						// 座標的範圍在(0.0 ~ 20.0, 0.0 ~ 20.0)
						if (coordinate.x < 0 || coordinate.x > BATTLEGRID_NUM || coordinate.y < 0 || coordinate.y > BATTLEGRID_NUM)
						{
							throw CMD_FIRE_ERROR::COORDINATE_ERROR;
						}

						//skip1 = '(' ; skip2 = ','
						if (skip1 != '(' || skip2 != ',')
						{
							throw CMD_FORMAT_ERROR::FORMAT_ERROR;
						}

						// 產生 Weapon 並回傳 Pointer
						Weapon^ weapon = GlobalVariable::ATeamVessels[str]->Attack(coordinate);

						// 設定 Weapon 文字顏色
						weapon->text->ForeColor = Color::FromArgb(0, 255, 0);

						// 加入圖層
						GlobalVariable::Weapons->Add(weapon->Name, weapon);
						if (PanelLayer.Count == 0)
						{
							this->battleGridsPanel->Controls->Add(weapon);
							PanelLayer.Add(weapon);
						}
						else
						{
							PanelLayer[PanelLayer.Count - 1]->Controls->Add(weapon);
							PanelLayer.Add(weapon);
						}

						// Log
						std::string weaponName = msclr::interop::marshal_as<std::string>(weapon->Name);
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA " << vesselName << " Fire to " << '(' << coordinate.x << ',' << coordinate.y << ')' 
							<< " ->" << weaponName;

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
					catch (...)
					{
						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA " << vesselName << " Fire to " << '(' << coordinate.x << ',' << coordinate.y << ')'
							<< " -> Fail";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else if (command == "DEFENSE")
				{
					// Do something
					std::string vesselName;
					std::string weaponName;

					// Get Input
					tempSS >> vesselName;
					tempSS >> weaponName;
					try
					{
						// 該隊必須存在該船艦
						String^ strVessel = gcnew String(vesselName.c_str());
						if (!GlobalVariable::ATeamVessels->ContainsKey(strVessel))
						{
							throw CMD_DEFENSE_ERROR::VESSEL_NOT_EXIST;
						}

						//武器必須存在場上
						String^ strWeapon = gcnew String(weaponName.c_str());
						if (!GlobalVariable::Weapons->ContainsKey(strWeapon))
						{
							throw CMD_DEFENSE_ERROR::WEAPON_ILLEGAL;
						}

						GlobalVariable::ATeamVessels[strVessel]->Defense();

						//若無法攻擊到砲彈視為未命中
						if (!isInDefenseRange(GlobalVariable::Weapons[strWeapon], GlobalVariable::ATeamVessels[strVessel]))
						{
							throw CMD_DEFENSE_ERROR::NOT_IN_RANGE;
						}

						//刪除砲彈											
						for (int i = 0 ; i < PanelLayer.Count ; i++)
						{
							if (PanelLayer[i] == GlobalVariable::Weapons[strWeapon])
							{
								if (i == 0)
								{
									this->battleGridsPanel->Controls->Remove(PanelLayer[i]);
								}
								else
								{
									PanelLayer[i - 1]->Controls->Remove(PanelLayer[i]);
								}
								
								if ((i + 1) < PanelLayer.Count)
								{
									if (i == 0)
									{
										this->battleGridsPanel->Controls->Add(PanelLayer[i + 1]);
									}
									else
									{
										PanelLayer[i - 1]->Controls->Add(PanelLayer[i + 1]);
									}
								}
								PanelLayer.Remove(PanelLayer[i]);
							}
						}
						delete GlobalVariable::Weapons[strWeapon];
						GlobalVariable::Weapons->Remove(strWeapon);

						//Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << "] "
							<< vesselName << " DEFENSE " << weaponName << " -> Hit";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
					catch (...)
					{
						//Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << "] "
							<< vesselName << " DEFENSE " << weaponName << " -> Fail";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else if (command == "TAG")
				{
					// Do something
					std::string vesselName;
					std::string New_Name;

					// Get Input
					tempSS >> vesselName;
					tempSS >> New_Name;

					try
					{
						// 該隊必須存在該船艦
						String^ strVessel = gcnew String(vesselName.c_str());
						
						if (!GlobalVariable::ATeamVessels->ContainsKey(strVessel))
						{
							throw CMD_TAG_ERROR::VESSEL_NOT_EXIST;
						}

						//新名字不能跟場上同隊船艦名字相同
						String^ strNew = gcnew String(New_Name.c_str());
						if (GlobalVariable::ATeamVessels->ContainsKey(strNew))
						{
							throw CMD_TAG_ERROR::NEW_NAME_ILLEGAL;
						}
					
						//更換名字
						GlobalVariable::ATeamVessels[strVessel]->Rename(New_Name);
						Vessel^ vessel = GlobalVariable::ATeamVessels[strVessel];
						// 加入新名稱 , 刪除舊名稱
						GlobalVariable::ATeamVessels->Add(strNew, vessel);
						GlobalVariable::ATeamVessels->Remove(strVessel);
						GlobalVariable::ATeamVessels[strNew]->Refresh();

						//Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA RENAME " << vesselName << " to " << New_Name << " -> Success";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
					catch (...)
					{
						//Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA RENAME " << vesselName << " to " << New_Name << " -> Fail";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else if (command == "MOVE")
				{
					std::string vesselName;
					double speed;
					double angle;

					tempSS >> vesselName;
					tempSS >> speed;
					tempSS >> angle;

					try
					{
						// 判斷船艦是否存在
						String^ str = gcnew String(vesselName.c_str());
						if (!GlobalVariable::ATeamVessels->ContainsKey(str))
						{
							throw CMD_MOVE_ERROR::VESSEL_NOT_EXIST;
						}

						// 設定速度, 角度
						GlobalVariable::ATeamVessels[str]->setSpeed(speed);
						GlobalVariable::ATeamVessels[str]->setAngle(angle);

						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA " << vesselName << " MOVE to " << angle << " as " << speed << " -> Success";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
					catch (...)
					{
						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA " << vesselName << " MOVE to " << angle << " as " << speed << " -> Fail";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else if (command == "MISSILE")
				{
					std::string vesselName;
					std::string targetName;

					// Get Input
					tempSS >> vesselName;
					tempSS >> targetName;

					try
					{
						// 該隊必須存在vesselName
						String^ strVessel = gcnew String(vesselName.c_str());
						if (!GlobalVariable::ATeamVessels->ContainsKey(strVessel))
						{
							throw CMD_FIRE_ERROR::VESSEL_NOT_EXIST;
						}

						// targetName必須存在於敵隊中
						String^ strTarget = gcnew String(targetName.c_str());
						if (!GlobalVariable::BTeamVessels->ContainsKey(strTarget))
						{
							throw CMD_FIRE_ERROR::VESSEL_NOT_EXIST;
						}

						// 產生 missile 並回傳 Pointer
						Missile^ missile = GlobalVariable::ATeamVessels[strVessel]->missileAttack(GlobalVariable::BTeamVessels[strTarget]);

						// 設定 Weapon 文字顏色
						missile->text->ForeColor = Color::FromArgb(0, 255, 0);

						// 加入圖層
						GlobalVariable::Weapons->Add(missile->Name, missile);
						if (PanelLayer.Count == 0)
						{
							this->battleGridsPanel->Controls->Add(missile);
							PanelLayer.Add(missile);
						}
						else
						{
							PanelLayer[PanelLayer.Count - 1]->Controls->Add(missile);
							PanelLayer.Add(missile);
						}

						// Log
						std::string missileName = msclr::interop::marshal_as<std::string>(missile->Name);
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA " << vesselName << " Missile_Fire to " << targetName
							<< " ->" << missileName;

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
						
					}
					catch (...)
					{
						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA " << vesselName << " Missile_Fire to " << targetName
							<< " -> Fail";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else
				{
					throw CMD_FORMAT_ERROR::FORMAT_ERROR;
				}
			}
			catch (...)
			{
				// Command Format Error
				std::ostringstream out;
				out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << "] ";

				String^ msg = gcnew System::String(out.str().c_str());
				LogTextBox->AppendText(msg);
				LogTextBox->AppendText("Command Format Error");
				LogTextBox->AppendText(Environment::NewLine);
				delete msg;
			}
		}

		ATeamCommandTextBox->Text = "";

		// 處理 BTeam 指令
		ss = std::stringstream(msclr::interop::marshal_as<std::string>(BTeamCommandTextBox->Text));

		while (std::getline(ss, cmdLine))
		{
			std::stringstream tempSS(cmdLine);
			tempSS >> command;

			ToUpper(command);

			try
			{
				if (command == "SET")
				{
					std::string vesselName, type;
					Coordinate coordinate(0, 0);
					bool isInType = false;

					// Get Input
					tempSS >> vesselName;
					tempSS >> type;
					tempSS >> skip1;
					tempSS >> coordinate.x;
					tempSS >> skip2;
					tempSS >> coordinate.y;

					try
					{
						// 判斷船艦不能重複
						String^ str = gcnew String(vesselName.c_str());
						if (GlobalVariable::BTeamVessels->ContainsKey(str))
						{
							throw CMD_SET_ERROR::VESSEL_NAME_ERROR;
						}

						// Type 必須出現在艦種裡
						for (const std::string& vt : VESSEL_TYPE)
						{
							if (type == vt)
							{
								isInType = true;
								break;
							}
						}
						if (isInType == false)
						{
							throw CMD_SET_ERROR::TYPE_NOT_EXIST;
						}

						// 座標的範圍在(0.0 ~ 20.0, 0.0 ~ 20.0)
						if (coordinate.x < 0 || coordinate.x > BATTLEGRID_NUM || coordinate.y < 0 || coordinate.y > BATTLEGRID_NUM)
						{
							throw CMD_SET_ERROR::COORDINATE_ERROR;
						}

						//skip1 = '(' ; skip2 = ','
						if (skip1 != '(' || skip2 != ',')
						{
							throw CMD_FORMAT_ERROR::FORMAT_ERROR;
						}

						// 新增船艦圖層
						Vessel^ vessel;
						if (type == "CV")
						{
							vessel = gcnew CV(coordinate, vesselName, BTeam);
						}
						else if (type == "BB")
						{
							vessel = gcnew BB(coordinate, vesselName, BTeam);
						}
						else if (type == "CG")
						{
							vessel = gcnew CG(coordinate, vesselName, BTeam);
						}
						else if (type == "DD")
						{
							vessel = gcnew DD(coordinate, vesselName, BTeam);
						}
						else if (type == "FL")
						{
							vessel = gcnew FL(coordinate, vesselName, BTeam);
						}
						else if (type == "LJP")
						{
							vessel = gcnew LJP(coordinate, vesselName, BTeam);
						}

						// 設定船艦文字顏色
						vessel->text->ForeColor = Color::FromArgb(0, 0, 255);

						// 加入船艦圖層, 若此圖層為第一層, 則上一個容器為 this battleGridsPanel
						GlobalVariable::BTeamVessels->Add(str, vessel);
						if (PanelLayer.Count == 0)
						{
							this->battleGridsPanel->Controls->Add(vessel);
							PanelLayer.Add(vessel);
						}
						else
						{
							PanelLayer[PanelLayer.Count - 1]->Controls->Add(vessel);
							PanelLayer.Add(vessel);
						}

						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamB SET " << vesselName << " with " << type << " at " << '(' << coordinate.x << ',' << coordinate.y
							<< ')' << " ->Success";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
					catch (...)
					{
						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamB SET " << vesselName << " with " << type << " at " << '(' << coordinate.x << ',' << coordinate.y
							<< ')' << " ->Fail";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else if (command == "FIRE")
				{
					std::string vesselName;
					Coordinate coordinate(0, 0);

					// Get Input
					tempSS >> vesselName;
					tempSS >> skip1;
					tempSS >> coordinate.x;
					tempSS >> skip2;
					tempSS >> coordinate.y;

					try
					{
						// 該隊必須存在該船艦
						String^ str = gcnew String(vesselName.c_str());
						if (!GlobalVariable::BTeamVessels->ContainsKey(str))
						{
							throw CMD_FIRE_ERROR::VESSEL_NOT_EXIST;
						}

						// 座標的範圍在(0.0 ~ 20.0, 0.0 ~ 20.0)
						if (coordinate.x < 0 || coordinate.x > BATTLEGRID_NUM || coordinate.y < 0 || coordinate.y > BATTLEGRID_NUM)
						{
							throw CMD_FIRE_ERROR::COORDINATE_ERROR;
						}

						//skip1 = '(' ; skip2 = ','
						if (skip1 != '(' || skip2 != ',')
						{
							throw CMD_FORMAT_ERROR::FORMAT_ERROR;
						}

						// 產生 Weapon 並回傳 Pointer
						Weapon^ weapon = GlobalVariable::BTeamVessels[str]->Attack(coordinate);

						// 設定 Weapon 文字顏色
						weapon->text->ForeColor = Color::FromArgb(0, 0, 255);

						// 加入圖層
						GlobalVariable::Weapons->Add(weapon->Name, weapon);
						if (PanelLayer.Count == 0)
						{
							this->battleGridsPanel->Controls->Add(weapon);
							PanelLayer.Add(weapon);
						}
						else
						{
							PanelLayer[PanelLayer.Count - 1]->Controls->Add(weapon);
							PanelLayer.Add(weapon);
						}

						// Log
						std::string weaponName = msclr::interop::marshal_as<std::string>(weapon->Name);
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamB " << vesselName << " Fire to " << '(' << coordinate.x << ',' << coordinate.y << ')'
							<< " ->" << weaponName;

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
					catch (...)
					{
						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamB " << vesselName << " Fire to " << '(' << coordinate.x << ',' << coordinate.y << ')'
							<< " -> Fail";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else if (command == "DEFENSE")
				{
					// Do something
					std::string vesselName;
					std::string weaponName;

					// Get Input
					tempSS >> vesselName;
					tempSS >> weaponName;
					try
					{
						// 該隊必須存在該船艦
						String^ strVessel = gcnew String(vesselName.c_str());
						if (!GlobalVariable::BTeamVessels->ContainsKey(strVessel))
						{
							throw CMD_DEFENSE_ERROR::VESSEL_NOT_EXIST;
						}

						//武器必須存在場上
						String^ strWeapon = gcnew String(weaponName.c_str());
						if (!GlobalVariable::Weapons->ContainsKey(strWeapon))
						{
							throw CMD_DEFENSE_ERROR::WEAPON_ILLEGAL;
						}

						GlobalVariable::BTeamVessels[strVessel]->Defense();

						//若無法攻擊到砲彈視為未命中
						if (!isInDefenseRange(GlobalVariable::Weapons[strWeapon], GlobalVariable::BTeamVessels[strVessel]))
						{
							throw CMD_DEFENSE_ERROR::NOT_IN_RANGE;
						}

						//刪除砲彈											
						for (int i = 0; i < PanelLayer.Count; i++)
						{
							if (PanelLayer[i] == GlobalVariable::Weapons[strWeapon])
							{
								if (i == 0)
								{
									this->battleGridsPanel->Controls->Remove(PanelLayer[i]);
								}
								else
								{
									PanelLayer[i - 1]->Controls->Remove(PanelLayer[i]);
								}

								if ((i + 1) < PanelLayer.Count)
								{
									if (i == 0)
									{
										this->battleGridsPanel->Controls->Add(PanelLayer[i + 1]);
									}
									else
									{
										PanelLayer[i - 1]->Controls->Add(PanelLayer[i + 1]);
									}
								}
								PanelLayer.Remove(PanelLayer[i]);
							}
						}
						delete GlobalVariable::Weapons[strWeapon];
						GlobalVariable::Weapons->Remove(strWeapon);

						//Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << "] "
							<< vesselName << " DEFENSE " << weaponName << " -> Hit";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
					catch (...)
					{
						//Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << "] "
							<< vesselName << " DEFENSE " << weaponName << " -> Fail";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else if (command == "TAG")
				{
					// Do something
					std::string vesselName;
					std::string New_Name;

					// Get Input
					tempSS >> vesselName;
					tempSS >> New_Name;

					try
					{
						// 該隊必須存在該船艦
						String^ strVessel = gcnew String(vesselName.c_str());

						if (!GlobalVariable::BTeamVessels->ContainsKey(strVessel))
						{
							throw CMD_TAG_ERROR::VESSEL_NOT_EXIST;
						}

						//新名字不能跟場上同隊船艦名字相同
						String^ strNew = gcnew String(New_Name.c_str());
						if (GlobalVariable::BTeamVessels->ContainsKey(strNew))
						{
							throw CMD_TAG_ERROR::NEW_NAME_ILLEGAL;
						}

						//更換名字
						GlobalVariable::BTeamVessels[strVessel]->Rename(New_Name);
						Vessel^ vessel = GlobalVariable::BTeamVessels[strVessel];
						// 加入新名稱 , 刪除舊名稱
						GlobalVariable::BTeamVessels->Add(strNew, vessel);
						GlobalVariable::BTeamVessels->Remove(strVessel);
						GlobalVariable::BTeamVessels[strNew]->Refresh();

						//Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamB RENAME " << vesselName << " to " << New_Name << " -> Success";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
					catch (...)
					{
						//Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamB RENAME " << vesselName << " to " << New_Name << " -> Fail";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else if (command == "MOVE")
				{
					std::string vesselName;
					double speed;
					double angle;

					tempSS >> vesselName;
					tempSS >> speed;
					tempSS >> angle;

					try
					{
						// 判斷船艦是否存在
						String^ str = gcnew String(vesselName.c_str());
						if (!GlobalVariable::BTeamVessels->ContainsKey(str))
						{
							throw CMD_MOVE_ERROR::VESSEL_NOT_EXIST;
						}

						// 設定速度, 角度
						GlobalVariable::BTeamVessels[str]->setSpeed(speed);
						GlobalVariable::BTeamVessels[str]->setAngle(angle);

						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamB " << vesselName << " MOVE to " << angle << " as " << speed << " -> Success";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
					catch (...)
					{
						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamB " << vesselName << " MOVE to " << angle << " as " << speed << " -> Fail";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else if (command == "MISSILE")
				{
					std::string vesselName;
					std::string targetName;

					// Get Input
					tempSS >> vesselName;
					tempSS >> targetName;

					try
					{
						// 該隊必須存在vesselName
						String^ strVessel = gcnew String(vesselName.c_str());
						if (!GlobalVariable::BTeamVessels->ContainsKey(strVessel))
						{
							throw CMD_FIRE_ERROR::VESSEL_NOT_EXIST;
						}

						// targetName必須存在於敵隊中
						String^ strTarget = gcnew String(targetName.c_str());
						if (!GlobalVariable::ATeamVessels->ContainsKey(strTarget))
						{
							throw CMD_FIRE_ERROR::VESSEL_NOT_EXIST;
						}

						// 產生 missile 並回傳 Pointer
						Missile^ missile = GlobalVariable::BTeamVessels[strVessel]->missileAttack(GlobalVariable::ATeamVessels[strTarget]);

						// 設定 Weapon 文字顏色
						missile->text->ForeColor = Color::FromArgb(0, 0, 255);

						// 加入圖層
						GlobalVariable::Weapons->Add(missile->Name, missile);
						if (PanelLayer.Count == 0)
						{
							this->battleGridsPanel->Controls->Add(missile);
							PanelLayer.Add(missile);
						}
						else
						{
							PanelLayer[PanelLayer.Count - 1]->Controls->Add(missile);
							PanelLayer.Add(missile);
						}

						// Log
						std::string missileName = msclr::interop::marshal_as<std::string>(missile->Name);
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamB " << vesselName << " Missile_Fire to " << targetName
							<< " ->" << missileName;

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
					catch (...)
					{
						// Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA " << vesselName << " Missile_Fire to " << targetName
							<< " -> Fail";

						String^ msg = gcnew System::String(out.str().c_str());
						LogTextBox->AppendText(msg);
						LogTextBox->AppendText(Environment::NewLine);
						delete msg;
					}
				}
				else
				{
					throw CMD_FORMAT_ERROR::FORMAT_ERROR;
				}
			}
			catch (...)
			{
				// Command Format Error
				std::ostringstream out;
				out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << "] ";

				String^ msg = gcnew System::String(out.str().c_str());
				LogTextBox->AppendText(msg);
				LogTextBox->AppendText("Command Format Error");
				LogTextBox->AppendText(Environment::NewLine);
				delete msg;
			}
		}

		BTeamCommandTextBox->Text = "";

		gameTimer->Enabled = true;
	}

	bool MainForm::isInAttackRange(KeyValuePair<String^, Weapon^>^ kvw, KeyValuePair<String^, Vessel^>^ kvv)
	{
		/*isInAttackRange*/
		if (pow(pow((kvv->Value->doubleLocation->x - kvw->Value->target->x),2) + pow((kvv->Value->doubleLocation->y - kvw->Value->target->y),2),0.5) <= kvw->Value->range * BATTLEGRID_SIZE)
		{
			return true;
		}
		return false;
	}

	bool MainForm::isInDefenseRange(Weapon^ kvw,Vessel^ kvv)
	{
		/*isInDefenseRange*/
		if (pow(pow((kvw->doubleLocation->x - kvv->doubleLocation->x), 2) + pow((kvw->doubleLocation->y - kvv->doubleLocation->y), 2), 0.5) <= kvv->maxDefenseDistance * BATTLEGRID_SIZE)
		{
			return true;
		}
		return false;
	}
	
}
