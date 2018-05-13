#pragma once

namespace BoilerImitator
{
	ref class BoilerCharacteristics
	{
	private:
		double inc, dec, roomTemp;
	public:
		BoilerCharacteristics(double tempInc, double tempDec, double roomT)
		{
			inc = tempInc;
			dec = tempDec;
			roomTemp = roomT;
		}

		double getInc()
		{
			return inc;
		}

		double getDec()
		{
			return dec;
		}

		double getRoomTemp()
		{
			return roomTemp;
		}
	};
}
