#pragma once

#include "States.h"

namespace BoilerImitator
{
	ref class StateVisualizer
	{
	public:
		virtual void SetCoverState(CoverState state) = 0;
		virtual void SetLedState(LedState state) = 0;
		virtual void SetCoverLockState(CoverLockState state) = 0;
		virtual void SetWaterTemp(double temp) = 0;
	};
}

