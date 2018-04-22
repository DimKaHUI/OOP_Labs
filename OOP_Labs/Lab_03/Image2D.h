#pragma once

#include "Edge.h"

#define OK_IMG 0
#define ERROR_IMG_BAD_ALLOC -211

class Vertex2D
{
	int x, y;
public:
	int getX() const;
	int getY() const;
	Vertex2D(int x, int y);
};


class Image2D
{
private:
	int vertexCount;
	int edgesCount;
	Vertex2D *points;
	Edge *edges;

public:
	int getVertexCount() const;
	int getEdgesCount() const;
	Edge getEdge(int ind) const;
	void setEdge(int ind, int s, int e);
	Vertex2D getVertex(int ind) const;
	int getVertexX(int ind) const;
	int getVertexY(int ind) const;
	void setVertex(int ind, int x, int y);
	Image2D(int n, int e);
	Image2D();
	~Image2D();
	explicit Image2D(const Image2D&& obj);
};