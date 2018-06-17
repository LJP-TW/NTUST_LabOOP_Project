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
#define PI 3.1415926
#define SRange 0
#define BRange 20
//#define DEBUG

#ifdef DEBUG
int debugInt = 0;
#endif

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

		ATeamVessels->Clear();
		BTeamVessels->Clear();
		PanelLayer.Clear();

		delete ATeamVessels;
		delete BTeamVessels;
		delete Weapons;
		delete ATeam;
		delete BTeam;
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
		// Initial
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
		ATeamVessels = gcnew Dictionary<String^, Vessel^>();
		BTeamVessels = gcnew Dictionary<String^, Vessel^>();
		Weapons = gcnew Dictionary<String^, Weapon^>();
		ATeam = gcnew Team("A");
		BTeam = gcnew Team("B");

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

		// Create Battle Grids Panel
		for (int i = 0; i <= BATTLEGRID_NUM; ++i)
		{
			battleGridsPanel->Controls->Add(battleGridsH[i]);
			battleGridsPanel->Controls->Add(battleGridsV[i]);
		}
		battleGridsPanel->Location = System::Drawing::Point(BATTLEGRID_PADDING, BATTLEGRID_PADDING);
		battleGridsPanel->Size = System::Drawing::Size(BATTLEGRID_SIZE * BATTLEGRID_NUM + 1, BATTLEGRID_SIZE * BATTLEGRID_NUM + 1);
		battleGridsPanel->Name = L"battleGridsGroupBox";

		// Create clock which show the time of game
		timeShower->BackColor = System::Drawing::Color::LightBlue;
		timeShower->Location = System::Drawing::Point(battleGridsFramePanel->Location.X, battleGridsFramePanel->Location.Y + battleGridsFramePanel->Size.Height + 10);
		timeShower->Size = System::Drawing::Size(75, 25);
		timeShower->AutoSize = false;
		timeShower->Text = "00:00";
		timeShower->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

		// Create Pause & Start Buttons
		pauseButton->Location = System::Drawing::Point(timeShower->Location.X + timeShower->Size.Width + 10, timeShower->Location.Y);
		pauseButton->Size = System::Drawing::Size(75, 25);
		pauseButton->AutoSize = false;
		pauseButton->Text = "Pause";
		pauseButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		pauseButton->Click += gcnew System::EventHandler(this, &MainForm::pauseButton_Click);
		pauseButton->Enabled = false;

		startButton->Location = System::Drawing::Point(pauseButton->Location.X + pauseButton->Size.Width + 10, pauseButton->Location.Y);
		startButton->Size = System::Drawing::Size(75, 25);
		startButton->AutoSize = false;
		startButton->Text = "Start";
		startButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		startButton->Click += gcnew System::EventHandler(this, &MainForm::startButton_Click);

		// Create Command Group Box
		commandGroupBox->Controls->Add(ATeamCommandTextBox);
		commandGroupBox->Controls->Add(BTeamCommandTextBox);
		commandGroupBox->Location = System::Drawing::Point(battleGridsFramePanel->Location.X + battleGridsFramePanel->Size.Width + 30, battleGridsFramePanel->Location.Y);
		commandGroupBox->Size = System::Drawing::Size(200, timeShower->Location.Y - battleGridsFramePanel->Location.Y + timeShower->Size.Height);
		commandGroupBox->Name = L"commandGroupBox";
		commandGroupBox->Text = L"Command";

		// Create Log Group Box
		logGroupBox->Controls->Add(LogTextBox);
		logGroupBox->Location = System::Drawing::Point(commandGroupBox->Location.X + commandGroupBox->Size.Width + 10, commandGroupBox->Location.Y);
		logGroupBox->Size = System::Drawing::Size(commandGroupBox->Size);
		logGroupBox->Name = L"logGroupBox";
		logGroupBox->Text = L"Battle Log";

		// Create A/BTeam Command TextBox
		ATeamCommandTextBox->Location = System::Drawing::Point(10, 20);
		ATeamCommandTextBox->Multiline = true;
		ATeamCommandTextBox->Name = L"ATeamCommandTextBox";
		ATeamCommandTextBox->Size = System::Drawing::Size(commandGroupBox->Size.Width - 20, (commandGroupBox->Size.Height - 40) / 2);

		BTeamCommandTextBox->Location = System::Drawing::Point(10, ATeamCommandTextBox->Location.Y + ATeamCommandTextBox->Size.Height + 10);
		BTeamCommandTextBox->Multiline = true;
		BTeamCommandTextBox->Name = L"BTeamCommandTextBox";
		BTeamCommandTextBox->Size = System::Drawing::Size(commandGroupBox->Size.Width - 20, (commandGroupBox->Size.Height - 40) / 2);

		// Create Log TextBox
		LogTextBox->Location = System::Drawing::Point(10, 20);
		LogTextBox->Multiline = true;
		LogTextBox->Name = L"LogTextBox";
		LogTextBox->Size = System::Drawing::Size(logGroupBox->Size.Width - 20, logGroupBox->Size.Height - 30);
		LogTextBox->Enabled = false;
		LogTextBox->BackColor = System::Drawing::Color::White;

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
		this->ClientSize = System::Drawing::Size(logGroupBox->Location.X + logGroupBox->Size.Width + 10, timeShower->Location.Y + timeShower->Size.Height + 10);

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

		// Test Line
		//Pen^ blackPen = gcnew Pen(Color::Black, 3.0f);
		//Graphics^ graphics = this->BTeamCommandTextBox->CreateGraphics();
		//graphics->DrawLine(blackPen, Point(0, 0), Point(5, 5));
		//delete blackPen;
		//delete graphics;
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

		// 每艘船跟每顆砲彈都是一個"圖層"
		// 用這個方法來消除 重疊物件會顯示不出來 的BUG

		// Weapon 更新
		for each(KeyValuePair<String^, Weapon^>^ kvp in Weapons)
		{
			/*同點上 船受到傷害 若生命歸零 則移除船*/
	/*		if (kvp->Value->isArrival())
			{
				for each(KeyValuePair<String^, Vessel^>^ kvn in ATeamVessels)
				{
					//Same Location Ship and Weapon
					if (isInAttackRange(kvp, kvn))
					{
						kvn->Value->hp -= kvp->Value->damage;
						//Remove From Dictionary
						if (kvn->Value->hp == 0)
						{
							ATeamVessels->Remove(kvn->Key);
						}
					}
				}
				for each(KeyValuePair<String^, Vessel^>^ kvn in BTeamVessels)
				{
					//Same Location Ship and Weapon
					if (isInAttackRange(kvp, kvn))
					{
						kvn->Value->hp -= kvp->Value->damage;
						//Remove From Dictionary
						if (kvn->Value->hp == 0)
						{
							ATeamVessels->Remove(kvn->Key);
						}
					}
				}
			}*/
			kvp->Value->Update();
		}

		// ATeam 船隻更新
		for each(KeyValuePair<String^, Vessel^>^ kvp in ATeamVessels)
		{
			kvp->Value->Update();
		}

		// BTeam 船隻更新
		for each(KeyValuePair<String^, Vessel^>^ kvp in BTeamVessels)
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
		
#ifdef DEBUG
		// Testing Code :
		std::string name = "GG" + std::to_string(debugInt);
		String^ str = gcnew String(name.c_str());
		CV^ vessel = gcnew CV(Coordinate(20 - debugInt * 0.5, 0 + debugInt * 0.5), name, ATeam);
		if (!ATeamVessels->ContainsKey(str))
		{
			ATeamVessels->Add(str, vessel);
			if (debugInt == 0)
			{
				this->battleGridsPanel->Controls->Add(vessel);
			}
			else
			{
				String^ temp = gcnew String(("GG" + std::to_string(debugInt - 1)).c_str());
				ATeamVessels[temp]->Controls->Add(vessel);
			}
			++debugInt;
		}

		// Add a new Vessel to MainForm
		//std::string name1 = "GG1";
		//std::string name2 = "GG2";
		//std::string name3 = "GG3";
		//std::string name4 = "GG4";
		//std::string name5 = "GG5";
		//String^ str1 = gcnew String(name1.c_str());
		//String^ str2 = gcnew String(name2.c_str());
		//String^ str3 = gcnew String(name3.c_str());
		//String^ str4 = gcnew String(name4.c_str());
		//String^ str5 = gcnew String(name5.c_str());
		//Vessel^ Vessel1 = gcnew Vessel(this->battleGridsPanel, Coordinate(0, 0), name1, ATeam, 5, 5, 5, 5, 5, 5);
		//Vessel^ Vessel2 = gcnew Vessel(this->battleGridsPanel, Coordinate(0.5, 0.5), name2, ATeam, 5, 5, 5, 5, 5, 5);
		//Vessel^ Vessel3 = gcnew Vessel(this->battleGridsPanel, Coordinate(1, 1), name3, ATeam, 5, 5, 5, 5, 5, 5);
		//Vessel^ Vessel4 = gcnew Vessel(this->battleGridsPanel, Coordinate(1.5, 1.5), name4, ATeam, 5, 5, 5, 5, 5, 5);
		//Vessel^ Vessel5 = gcnew Vessel(this->battleGridsPanel, Coordinate(2, 2), name5, ATeam, 5, 5, 5, 5, 5, 5);
		//if (!ATeamVessels->ContainsKey(str1))
		//{
		//	ATeamVessels->Add(str1, Vessel1);
		//	ATeamVessels->Add(str2, Vessel2);
		//	ATeamVessels->Add(str3, Vessel3);
		//	ATeamVessels->Add(str4, Vessel4);
		//	ATeamVessels->Add(str5, Vessel5);
		//	this->battleGridsPanel->Controls->Add(Vessel1);
		//	this->battleGridsPanel->Controls->Add(Vessel2);
		//	this->battleGridsPanel->Controls->Add(Vessel3);
		//	this->battleGridsPanel->Controls->Add(Vessel4);
		//	this->battleGridsPanel->Controls->Add(Vessel5);
		//}
#endif
		
	}

	void MainForm::startButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		((System::Windows::Forms::Button ^)sender)->Enabled = false;
		pauseButton->Enabled = true;
		ATeamCommandTextBox->Enabled = false;
		BTeamCommandTextBox->Enabled = false;

		// Handling Command
		// 處理 ATeam 指令
		std::stringstream ss(msclr::interop::marshal_as<std::string>(ATeamCommandTextBox->Text));
		std::string cmdLine, command;
		char skip;

		while (std::getline(ss, cmdLine))
		{
			std::stringstream tempSS(cmdLine);
			tempSS >> command;

			ToUpper(command);

			/*Log use min and sec*/
			unsigned long long min;
			unsigned long long sec;

			min = gameTime / 60;
			sec = gameTime % 60;


			try
			{
				if (command == "SET")
				{
					std::string vesselName, type;
					Coordinate coordinate(0, 0);
					bool isInType = false;
					/*Repeat Vessel Name*/
					bool isRepeat = false;
					

					// Get Input
					tempSS >> vesselName;
					tempSS >> type;
					tempSS >> skip;
					tempSS >> coordinate.x;
					tempSS >> skip;
					tempSS >> coordinate.y;

					try
					{
						// 判斷船艦不能重複
						// Do something (錯誤偵測)			
						String^ str = gcnew String(vesselName.c_str());																			
						if (ATeamVessels->ContainsKey(str))
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
						// Do something (錯誤偵測)
						if (coordinate.x < SRange || coordinate.x > BRange || coordinate.y < SRange || coordinate.y > BRange)
						{
							throw CMD_SET_ERROR::COORDINATE_ERROR;
						}

						/*艦種未完成*/
						if (type == "CV")
						{
							// 新增船艦圖層
							String^ str = gcnew String(vesselName.c_str());
							CV^ vessel = gcnew CV(coordinate, vesselName, ATeam);

							// 加入船艦圖層, 若此圖層為第一層, 則上一個容器為 this battleGridsPanel
							ATeamVessels->Add(str, vessel);
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
						}
/*						else if(type == "BB")
						{
							// 新增船艦圖層
							String^ str = gcnew String(vesselName.c_str());
							BB^ vessel = gcnew BB(coordinate, vesselName, ATeam);

							// 加入船艦圖層, 若此圖層為第一層, 則上一個容器為 this battleGridsPanel
							ATeamVessels->Add(str, vessel);
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
						}
						else if (type == "CG")
						{
							// 新增船艦圖層
							String^ str = gcnew String(vesselName.c_str());
							CG^ vessel = gcnew CG(coordinate, vesselName, ATeam);

							// 加入船艦圖層, 若此圖層為第一層, 則上一個容器為 this battleGridsPanel
							ATeamVessels->Add(str, vessel);
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
						}
						else if (type == "DD")
						{
							// 新增船艦圖層
							String^ str = gcnew String(vesselName.c_str());
							DD^ vessel = gcnew DD(coordinate, vesselName, ATeam);

							// 加入船艦圖層, 若此圖層為第一層, 則上一個容器為 this battleGridsPanel
							ATeamVessels->Add(str, vessel);
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
						}
*/						
						// Log
						// Do something (指令紀錄)
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA SET " << vesselName << " with " << type << " at " << '(' << coordinate.x << ',' << coordinate.y
							<< ')' << " ->Success" << std::endl;
						LogTextBox->Text += gcnew System::String(out.str().c_str());

					}
					catch (...)
					{
						// Log
						// Do something (指令紀錄)
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA SET " << vesselName << " with " << type << " at " << '(' << coordinate.x << ',' << coordinate.y
							<< ')' << " ->Fail" << std::endl;
						LogTextBox->Text += gcnew System::String(out.str().c_str());

						throw;
					}
				}
				else if (command == "FIRE")
				{
					std::string vesselName;
					Coordinate coordinate(0, 0);

					// Get Input
					tempSS >> vesselName;
					tempSS >> skip;
					tempSS >> coordinate.x;
					tempSS >> skip;
					tempSS >> coordinate.y;

					try
					{
						// 該隊必須存在該船艦
						String^ str = gcnew String(vesselName.c_str());
						if (!ATeamVessels->ContainsKey(str))
						{
							throw CMD_FIRE_ERROR::VESSEL_NOT_EXIST;
						}

						// 座標的範圍在(0.0 ~ 20.0, 0.0 ~ 20.0)
						// Do something (錯誤偵測)
						if (coordinate.x < SRange || coordinate.x > BRange || coordinate.y < SRange || coordinate.y > BRange)
						{
							throw CMD_FIRE_ERROR::COORDINATE_ERROR;
						}

						// 產生 Weapon 並回傳 Pointer
						Weapon^ weapon = ATeamVessels[str]->Attack(coordinate);

						// 加入圖層
						Weapons->Add(str, weapon);
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
						// Do something (指令紀錄)
						std::string weaponName = msclr::interop::marshal_as<std::string>(weapon->Name);
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA " << vesselName << " Fire to " << '(' << coordinate.x << ',' << coordinate.y << ')' 
							<< " ->" << weaponName << std::endl;

						LogTextBox->Text += gcnew System::String(out.str().c_str());
					}
					catch (...)
					{
						// Log
						// Do something (指令紀錄)
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA " << vesselName << " Fire to " << '(' << coordinate.x << ',' << coordinate.y << ')'
							<< " -> Fail" << std::endl;

						LogTextBox->Text += gcnew System::String(out.str().c_str());
						throw;
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
						if (!ATeamVessels->ContainsKey(strVessel))
						{
							throw CMD_DEFENSE_ERROR::VESSEL_NOT_EXIST;
						}

						//武器必須存在場上
						if (!Weapons->ContainsKey(strVessel))
						{
							throw CMD_DEFENSE_ERROR::WEAPON_ILLEGAL;
						}

						//若無法攻擊到砲彈視為未命中 Weapons發射時 視使用VesselName當key
						if (isInDefenseRange(Weapons[strVessel],ATeamVessels[strVessel]))
						{
							throw CMD_DEFENSE_ERROR::NOT_IN_RANGE;
						}

						//刪除砲彈
						Weapons->Remove(strVessel);

						//Log						
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< vesselName << " DEFENSE " << weaponName << " -> Hit" << std::endl;

						LogTextBox->Text += gcnew System::String(out.str().c_str());
					}
					catch (...)
					{
						//Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< vesselName << " DEFENSE " << weaponName << " -> Fail" << std::endl;

						LogTextBox->Text += gcnew System::String(out.str().c_str());
						throw;
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
						if (!ATeamVessels->ContainsKey(strVessel))
						{
							throw CMD_TAG_ERROR::VESSEL_NOT_EXIST;
						}

						//新名字不能跟場上同隊船艦名字相同
						String^ strNew = gcnew String(New_Name.c_str());
						if (ATeamVessels->ContainsKey(strNew))
						{
							throw CMD_TAG_ERROR::NEW_NAME_ILLEGAL;
						}
					
						//更換名字
						Vessel^ vessel = ATeamVessels[strVessel];
						// 加入新名稱 , 刪除舊名稱
						ATeamVessels->Add(strNew, vessel);
						ATeamVessels->Remove(strVessel);

						//Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA RENAME " << vesselName << " to " << New_Name << " -> Success" << std::endl;

						LogTextBox->Text += gcnew System::String(out.str().c_str());
					}
					catch (...)
					{
						//Log
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA RENAME " << vesselName << " to " << New_Name << " -> Fail" << std::endl;

						LogTextBox->Text += gcnew System::String(out.str().c_str());
						throw;
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
						if (!ATeamVessels->ContainsKey(str))
						{
							throw CMD_MOVE_ERROR::VESSEL_NOT_EXIST;
						}

						// 設定速度, 角度
						ATeamVessels[str]->setSpeed(speed);
						ATeamVessels[str]->setAngle(angle);

						// Log
						// Do something (指令紀錄)
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA " << vesselName << " MOVE to " << angle << " as " << speed << " -> Success" << std::endl;

						LogTextBox->Text += gcnew System::String(out.str().c_str());
					}
					catch (...)
					{
						// Log
						// Do something (指令紀錄)
						std::ostringstream out;
						out << '[' << std::setw(2) << std::setfill('0') << min << ':' << std::setw(2) << std::setfill('0') << sec << ']'
							<< " TeamA " << vesselName << " MOVE to " << angle << " as " << speed << " -> Fail" << std::endl;

						LogTextBox->Text += gcnew System::String(out.str().c_str());
						throw;
					}
				}
			}
			catch (...)
			{
				// Command Format Error
				// Do something (錯誤紀錄)				
			}
		}

		ATeamCommandTextBox->Text = "";

		// 處理 BTeam 指令
		ss = std::stringstream(msclr::interop::marshal_as<std::string>(BTeamCommandTextBox->Text));

		while (std::getline(ss, cmdLine))
		{
			// Do something
		}

		BTeamCommandTextBox->Text = "";

		gameTimer->Enabled = true;

#ifdef DEBUG
#endif
		// Testing Code :
		// Remove Vessel from MainForm
		//std::string name1 = "GG1";
		//std::string name2 = "GG2";
		//std::string name3 = "GG3";
		//std::string name4 = "GG4";
		//std::string name5 = "GG5";
		//String^ str1 = gcnew String(name1.c_str());
		//String^ str2 = gcnew String(name2.c_str());
		//String^ str3 = gcnew String(name3.c_str());
		//String^ str4 = gcnew String(name4.c_str());
		//String^ str5 = gcnew String(name5.c_str());
		//if (ATeamVessels->ContainsKey(str2))
		//{
		//	this->battleGridsPanel->Controls->Remove(ATeamVessels[str1]);
		//	this->battleGridsPanel->Controls->Remove(ATeamVessels[str2]);
		//	this->battleGridsPanel->Controls->Remove(ATeamVessels[str3]);
		//	this->battleGridsPanel->Controls->Remove(ATeamVessels[str4]);
		//	this->battleGridsPanel->Controls->Remove(ATeamVessels[str5]);
		//	ATeamVessels->Remove(str1);
		//	ATeamVessels->Remove(str2);
		//	ATeamVessels->Remove(str3);
		//	ATeamVessels->Remove(str4);
		//	ATeamVessels->Remove(str5);
		//}
	}
	bool MainForm::isInAttackRange(KeyValuePair<String^, Weapon^>^ kvw, KeyValuePair<String^, Vessel^>^ kvv)
	{
		/*isInAttackRange*/
		if (pow(pow((kvv->Value->doubleLocation->x - kvw->Value->target->x),2) + pow((kvv->Value->doubleLocation->y - kvw->Value->target->y),2),0.5) <= kvw->Value->range)
		{
			return true;
		}
		return false;
	}

	bool MainForm::isInDefenseRange(Weapon^ kvw,Vessel^ kvv)
	{
		/*isInDefenseRange*/
		if (pow(pow((kvw->doubleLocation->x - kvv->doubleLocation->x), 2) + pow((kvw->doubleLocation->y - kvv->doubleLocation->y), 2), 0.5) <= kvv->maxDefenseDistance)
		{
			return true;
		}
		return false;
	}
	
}
