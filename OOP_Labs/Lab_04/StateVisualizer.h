#pragma once

namespace BoilerImitator
{

	enum CoverState
	{
		Closed, Opened
	};

	enum LedState
	{
		On, Off
	};

	enum CoverLockState
	{
		Locked, Unlocked
	};

	ref class StateVisualizer
	{
	public:
		virtual void SetCoverState(CoverState state) = 0;
		virtual void SetLedState(LedState state) = 0;
		virtual void SetCoverLockState(CoverLockState state) = 0;
		virtual void SetWaterTemp(double temp) = 0;
	};
}

