#pragma once
namespace BoilerImitator
{
	ref class UserInterface
	{
	public:
		virtual System::Void SwitchClick(System::Object^  sender, System::EventArgs^  e) = 0;
		virtual System::Void CoverButtonClick(System::Object^  sender, System::EventArgs^  e) = 0;
	};
}

