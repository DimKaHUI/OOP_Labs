// WinFormsTemplate.cpp: главный файл проекта.

#include "stdafx.h"
#include "MainForm.h"

using namespace WinFormsTemplate;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Создание главного окна и его запуск
	if (args->Length >= 1)
		Application::Run(gcnew MainForm(args[0]));
	else
		Application::Run(gcnew MainForm());
	return 0;
}
