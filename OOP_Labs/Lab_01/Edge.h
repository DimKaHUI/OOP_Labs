#pragma once
#include "stdafx.h"

typedef struct Edge
{
	int start_index;
	int end_index;
};

void setupEdge(Edge *edge, int s, int e);

int getEdgeStart(Edge *edge);

int getEdgeEnd(Edge *edge);