#pragma once

#include "Iterator.h"
#include "Edge.h"
#include "FrameMdlProjector.h"
#include "Exceptions.h"

class EdgeIterator : public Iterator<Edge>
{
private:
	FrameModel* aggregator;
	int current = 0;
public:
	EdgeIterator(FrameModel* mdl)
	{
		aggregator = mdl;
	}
	~EdgeIterator()
	{
		
	}

	Edge First() override
	{
		return aggregator->getEdge(0);
	}

	Edge Next() override
	{
		current++;
		if (current >= aggregator->getE())
			throw index_out_of_range();
		return aggregator->getEdge(current);
	}

	Edge CurrentItem() override
	{
		return aggregator->getEdge(current);
	}

	bool isDone() override
	{
		bool isDone = false;
		if (current >= aggregator->getE())
			isDone = true;
		return isDone;
	}
};