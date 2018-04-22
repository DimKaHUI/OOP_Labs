#pragma once

#include "Edge.h"

#define OK_IMG 0
#define ERROR_IMG_BAD_ALLOC -211

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
Vertex2D getVertex(const Image2D *img, int ind);
int getVertex2DX(const Image2D *img, int ind);
int getVertex2DY(const Image2D *img, int ind);
void free_image(Image2D *img);
int init_image(Image2D *img, int n, int e);