#include "stdafx.h"
#include "Edge.h"

void setupEdge(Edge *edge, int s, int e)
{
	edge->start_index = s;
	edge->end_index = e;
}

int getEdgeStart(Edge edge)
{
	return edge.start_index;
}

int getEdgeEnd(Edge edge)
{
	return edge.end_index;
}