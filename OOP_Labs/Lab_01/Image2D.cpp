#include "stdafx.h"
#include "Image2D.h"

void setupVertex2D(Vertex2D *vertex, int x, int y)
{
	vertex->x = x;
	vertex->y = y;
}
int getVertex2DX(Image2D *img, int ind)
{
	Vertex2D v = getVertex(img, ind);
	return v.x;
}
int getVertex2DY(Image2D *img, int ind)
{
	Vertex2D v = getVertex(img, ind);
	return v.y;
}

Vertex2D getVertex(Image2D *img, int ind)
{
	return img->points[ind];
}

Edge getEdge(Image2D *img, int ind)
{
	return img->edges[ind];
}