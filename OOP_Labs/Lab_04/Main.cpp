// Boiler.cpp: ������� ���� �������.

#include "stdafx.h"
#include "MainForm.h"

namespace BoilerImitator
{

	int main(array<System::String ^> ^args)
	{
		// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);

		// �������� �������� ���� � ��� ������
		Application::Run(gcnew Form1());
		return 0;
	}
}
