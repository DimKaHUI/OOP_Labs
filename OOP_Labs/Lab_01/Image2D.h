#pragma once

typedef struct Vertex2D
{
	int x, y;
};

typedef struct Edge
{
	int start_index;
	int end_index;
};

typedef struct Image2D
{
	int vertexCount;
	int edgesCount;
	Vertex2D *points;
	Edge *edges;
};

typedef struct Vector3
{
	float x, y, z;
};