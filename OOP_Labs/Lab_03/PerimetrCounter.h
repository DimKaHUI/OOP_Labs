#pragma once

#include <cmath>
#include "Decorator.h"
#include "UserMessage.h"
#include "EdgeIterator.h"

class PerimetrCounter : public Decorator
{
public:
	void operation() override
	{
		Decorator::operation();

		double summ = 0;

		EdgeIterator *iterator = new EdgeIterator(component);

		Edge edge = iterator->First();

		do
		{
			edge = iterator->Next();
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
			
		} while (!iterator->isDone());

		delete iterator;
		String^ str = "Perimetr: ";
		str += Double(summ).ToString();
		ShowMessage(str);
	}
};