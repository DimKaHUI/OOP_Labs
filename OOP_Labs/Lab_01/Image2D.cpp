#include "stdafx.h"
#include "Image2D.h"

#include <stdlib.h>

void setupVertex2D(Vertex2D *vertex, int x, int y)
{
	vertex->x = x;
	vertex->y = y;
}
int getVertex2DX(const Image2D *img, int ind)
{
	Vertex2D v = getVertex(img, ind);
	return v.x;
}
int getVertex2DY(const Image2D *img, int ind)
{
	Vertex2D v = getVertex(img, ind);
	return v.y;
}

Vertex2D getVertex(const Image2D *img, int ind)
{
	return img->points[ind];
}

Edge getEdge(const Image2D *img, int ind)
{
	return img->edges[ind];
}

void free_image(Image2D *img)
{
	if (img != NULL)
	{
		free(img->points);
		free(img->edges);
	}
}

int init_image(Image2D *img, int n, int e)
{
	img->vertexCount = n;
	img->edgesCount = e;

	img->points = (Vertex2D*)malloc(sizeof(Vertex2D)* n);
	img->edges = (Edge*)malloc(sizeof(Edge)*e);

	int err = OK_IMG;
	if (img->points == NULL || img->edges == NULL)
		err =  ERROR_IMG_BAD_ALLOC;
	return err;
}