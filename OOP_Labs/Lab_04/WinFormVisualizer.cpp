#include "stdafx.h"
#include "WinFormVisualizer.h"

namespace BoilerImitator
{
	BoilerImitator::WinFormVisualizer::WinFormVisualizer(Label ^ temp, Label ^ cover, Label ^ coverLock, Panel ^ led)
	{
		temperatureLabel = temp;
		coverLabel = cover;
		coverLockLabel = coverLock;
		ledPanel = led;
	}

	void BoilerImitator::WinFormVisualizer::SetCoverState(CoverState state)
	{
		switch (state)
		{
		case Opened:
			coverLabel->Text = "Opened";
			break;
		case Closed:
			coverLabel->Text = "Closed";
			break;
		default:
			throw gcnew System::ArgumentException();
		}
	}

	void BoilerImitator::WinFormVisualizer::SetLedState(LedState state)
	{
		switch (state)
		{
		case On:
			ledPanel->BackColor = System::Drawing::Color::Red;
			break;
		case Off:
			ledPanel->BackColor = System::Drawing::Color::Black;
			break;
		default:
			throw gcnew System::ArgumentException();
		}
	}

	void BoilerImitator::WinFormVisualizer::SetCoverLockState(CoverLockState state)
	{
		switch (state)
		{
		case Locked:
			coverLockLabel->Text = "Locked";
			break;
		case Unlocked:
			coverLockLabel->Text = "Unlocked";
			break;
		default:
			throw gcnew System::ArgumentException();
		}
	}

	void BoilerImitator::WinFormVisualizer::SetWaterTemp(double temp)
	{
		temperatureLabel->Text = System::String::Format("{0:0.0}", temp);
	}

}
