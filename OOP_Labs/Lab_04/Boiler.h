#pragma once
#include "StateVisualizer.h"
#include "BoilerCharacteristics.h"

#define WATER_BOILING 100.0

namespace BoilerImitator
{
	ref class Boiler
	{
	private:

		delegate void StartEvent();
		delegate void FinishEvent();
		
		event StartEvent^ OnStartEvent;
		event FinishEvent^ OnFinishEvent;

		CoverState coverState;
		CoverLockState coverLockState;
		LedState ledState;
		StateVisualizer^ visualizer;
		BoilerCharacteristics^ chars;

		System::Void Tick(System::Object^  sender, System::EventArgs^  e);

		void SetOn();
		void SetOff();

		BoilerState boilerState;
		double temp;
		void UpdateUi();
	public:
		Boiler(BoilerImitator::StateVisualizer^ visualizer, System::Windows::Forms::Timer^ timer, BoilerCharacteristics^ chars);

		System::Void SwitchClick(System::Object^  sender, System::EventArgs^  e);
		System::Void CoverButtonClick(System::Object^  sender, System::EventArgs^  e);
	};
}

