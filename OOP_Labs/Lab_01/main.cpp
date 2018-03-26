// MainForm.cpp: ������� ���� �������.

#include "stdafx.h"
#include "MainForm.h"

#define FILE_PATH_INDEX 0

using namespace WinFormsTemplate;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	if (args->Length >= FILE_PATH_INDEX)
		Application::Run(gcnew MainForm(args[FILE_PATH_INDEX]));
	else
		Application::Run(gcnew MainForm());
	return 0;
}
