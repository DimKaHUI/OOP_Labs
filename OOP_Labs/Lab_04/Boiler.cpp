#include "stdafx.h"
#include "Boiler.h"
#include "StateVisualizer.h"
#include "UserInterface.h"

namespace BoilerImitator
{
	System::Void Boiler::Tick(System::Object ^ sender, System::EventArgs ^ e)
	{
		double delta = temp - chars->getRoomTemp();
		if(delta > 0)
		{
			temp -= chars->getDec();
		}
		
		if(isOn)
		{
			temp += chars->getInc();
		}

		if(temp >= WATER_BOILING)
		{
			SetOff();
		}

		UpdateUi();
	}
	void Boiler::SetOn()
	{
		isOn = 1;
		ledState = On;
		coverLockState = Locked;
	}
	void Boiler::SetOff()
	{
		isOn = 0;
		ledState = Off;
		coverLockState = Unlocked;
	}
	void Boiler::UpdateUi()
	{
		visualizer->SetCoverState(coverState);
		visualizer->SetCoverLockState(coverLockState);
		visualizer->SetLedState(ledState);
		visualizer->SetWaterTemp(temp);
	}
	Boiler::Boiler(BoilerImitator::StateVisualizer^ visualizer, System::Windows::Forms::Timer^ timer, BoilerCharacteristics^ chars)
	{		
		// Setting up time-controller
		timer->Tick += gcnew System::EventHandler(this, &Boiler::Tick);
		// Setting up visualizer
		this->visualizer = visualizer;
		this->chars = chars;
		temp = chars->getRoomTemp();
		coverState = Closed;
		SetOff();
	}


	System::Void Boiler::SwitchClick(System::Object ^ sender, System::EventArgs ^ e)
	{
		if(isOn == 0) // Turning on
		{
			if(coverState == Closed)
			{
				SetOn();
			}
		}
		else
		{
			SetOff();
		}
	}
	System::Void Boiler::CoverButtonClick(System::Object ^ sender, System::EventArgs ^ e)
	{
		if(coverLockState == Unlocked)
		{
			if (coverState == Closed)
				coverState = Opened;
			else
				coverState = Closed;
		}
	}
}
