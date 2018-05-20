#pragma once

#include <cmath>
#include "Decorator.h"
#include "UserMessage.h"

class PerimetrCounter : public Decorator
{
public:
	void operation() override
	{
		Decorator::operation();

		double summ = 0;
		for(int i = 0; i < component->getE(); i++)
		{
			Edge edge = component->getEdge(i);
			int i1 = edge.getEdgeStart();
			int i2 = edge.getEdgeEnd();
			int x1 = component->getVertex(i1).getX();
			int y1 = component->getVertex(i1).getY();
			int z1 = component->getVertex(i1).getZ();
			int x2 = component->getVertex(i2).getX();
			int y2 = component->getVertex(i2).getY();
			int z2 = component->getVertex(i2).getZ();
			
			int dx = x2 - x1;
			int dy = y2 - y1;
			int dz = z2 - z1;

			double length = sqrt(dx*dx + dy * dy + dz * dz);
			summ += length;
		}

		String^ str = "Perimetr: ";
		str += Double(summ).ToString();
		ShowMessage(str);
	}
};