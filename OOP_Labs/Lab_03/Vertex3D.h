#pragma once

class Vertex3D
{
	float x, y, z;
public:
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	float getZ()
	{
		return z;
	}
	Vertex3D(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vertex3D()
	{
		x = 0; y = 0; z = 0;
	}
};