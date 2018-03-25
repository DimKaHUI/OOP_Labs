#pragma once

#include "Edge.h"

typedef struct Vertex2D
{
	int x, y;
};


typedef struct Image2D
{
	int vertexCount;
	int edgesCount;
	Vertex2D *points;
	Edge *edges;
};

void setupVertex2D(Vertex2D *vertex, int x, int y);
int getVertex2DX(Image2D *img, int ind);
int getVertex2DY(Image2D *img, int ind);
int getEdgeS(Image2D *img, int ind);
int getEdgeE(Image2D *img, int ind);

