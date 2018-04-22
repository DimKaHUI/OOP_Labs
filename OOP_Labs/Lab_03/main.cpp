// MainForm.cpp: главный файл проекта.

#include "stdafx.h"
#include "MainForm.h"

#define FILE_PATH_INDEX 0

using namespace WinFormsTemplate;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Создание главного окна и его запуск
	if (args->Length > FILE_PATH_INDEX)
		Application::Run(gcnew MainForm(args[FILE_PATH_INDEX]));
	else
		Application::Run(gcnew MainForm());
	return 0;
}
