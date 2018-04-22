#include "stdafx.h"
#include "Edge.h"

Edge::Edge(int s, int e)
{
	start_index = s;
	end_index = e;
}

int Edge::getEdgeStart() const
{
	return start_index;
}

int Edge::getEdgeEnd() const
{
	return end_index;
}