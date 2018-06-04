#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Project3_SeaBattleSim;

[STAThread]

int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Project3_SeaBattleSim::MainForm());
}