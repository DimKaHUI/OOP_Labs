#pragma once

#include "StateVisualizer.h"

namespace BoilerImitator
{
	using namespace System::Windows::Forms;
	ref class WinFormVisualizer : public StateVisualizer
	{
	private:
		Label ^ temperatureLabel;
		Label^ coverLabel;
		Label^ coverLockLabel;
		Panel^ ledPanel;
	public:
		WinFormVisualizer(Label^ temp, Label^ cover, Label^ coverLock, Panel^ led);
		void SetCoverState(CoverState state) override;
		void SetLedState(LedState state)override;
		void SetCoverLockState(CoverLockState state)override;
		void SetWaterTemp(double temp) override;
	};

}

