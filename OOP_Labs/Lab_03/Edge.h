#pragma once
#include "stdafx.h"

class Edge
{
	int start_index;
	int end_index;

public:
	Edge(int s, int e);
	int getEdgeStart() const;
	int getEdgeEnd() const;
};