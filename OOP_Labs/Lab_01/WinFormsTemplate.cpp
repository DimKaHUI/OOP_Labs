// WinFormsTemplate.cpp: ������� ���� �������.

#include "stdafx.h"
#include "MainForm.h"

using namespace WinFormsTemplate;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	if (args->Length >= 1)
		Application::Run(gcnew MainForm(args[0]));
	else
		Application::Run(gcnew MainForm());
	return 0;
}
