#include "stdafx.h"
#include "Boiler.h"
#include "StateVisualizer.h"

namespace BoilerImitator
{
	System::Void Boiler::Tick(System::Object ^ sender, System::EventArgs ^ e)
	{
		if (temp >= WATER_BOILING)
		{
			OnFinishEvent();
		}

		double delta = temp - chars->getRoomTemp();
		if(delta > 0)
		{
			temp -= chars->getDec();
		}
		
		if (boilerState == Heating)
		{
			temp += chars->getInc();
		}		

		UpdateUi();
	}
	void Boiler::SetOn()
	{
		boilerState = Heating;
		ledState = On;
		coverLockState = Locked;
	}
	void Boiler::SetOff()
	{
		boilerState = Suspending;
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
		coverLockState = Unlocked;
		ledState = Off;
		boilerState = Suspending;

		OnStartEvent += gcnew StartEvent(this, &Boiler::SetOn);
		OnFinishEvent += gcnew FinishEvent(this, &Boiler::SetOff);
	}


	System::Void Boiler::SwitchClick(System::Object ^ sender, System::EventArgs ^ e)
	{
		if (boilerState == Suspending) // Turning on
		{
			if(coverState == Closed)
			{
				OnStartEvent();
			}
		}
		else
		{
			OnFinishEvent();
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
