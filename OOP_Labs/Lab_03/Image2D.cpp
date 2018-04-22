#include "stdafx.h"
#include "Image2D.h"
#include "Exceptions.h"

#include <stdlib.h>

Vertex2D::Vertex2D(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Vertex2D::getX() const
{
	return x;
}

int Vertex2D::getY() const
{
	return y;
}

int Image2D::getVertexX(int ind) const
{
	Vertex2D v = getVertex(ind);
	return v.getX();
}

int Image2D::getVertexY(int ind) const
{
	Vertex2D v = getVertex(ind);
	return v.getY();
}

Vertex2D Image2D::getVertex(int ind) const
{
	return points[ind];
}

Edge Image2D::getEdge(int ind) const
{
	return edges[ind];
}

Image2D::~Image2D()
{
	free(points);
	free(edges);
	points = nullptr;
	edges = nullptr;
}

Image2D::Image2D(const Image2D&& obj)
{
	vertexCount = obj.vertexCount;
	edgesCount = obj.edgesCount;
	points = obj.points;
	edges = obj.edges;
}

Image2D::Image2D(int n, int e)
{
	vertexCount = n;
	edgesCount = e;

	points = (Vertex2D*)malloc(sizeof(Vertex2D)* n);
	edges = (Edge*)malloc(sizeof(Edge)*e);

	int err = OK_IMG;
	if (points == NULL || edges == NULL)
		throw bad_memory();
}

Image2D::Image2D()
{
	vertexCount = 0;
	edgesCount = 0;

	points = nullptr;
	edges = nullptr;
}

int Image2D::getVertexCount() const
{
	return vertexCount;
}

int Image2D::getEdgesCount() const
{
	return edgesCount;
}

void Image2D::setEdge(int ind, int s, int e)
{
	edges[ind] = Edge(s, e);
}

void Image2D::setVertex(int ind, int x, int y)
{
	points[ind] = Vertex2D(x, y);
}