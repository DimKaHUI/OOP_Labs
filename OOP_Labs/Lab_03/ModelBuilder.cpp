#include "stdafx.h"
#include "ModelBuilder.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>


void ModelBuilder::ReadVertexes(std::ifstream &file, Vertex3D *verts, int n)
{
	for (int i = 0; i < n; i++)
	{
		int x, y, z;
		file >> x;
		file >> y;
		file >> z;
		//setupVertex3D(&verts[i], x, y, z);
		verts[i] = Vertex3D(x, y, z);
	}
}

void ModelBuilder::ReadEdges(std::ifstream &file, Edge *edges, int n)
{
	for (int i = 0; i < n; i++)
	{
		int s, e;
		file >> s;
		file >> e;
		//setupEdge(&edges[i], s, e);
		edges[i] = Edge(s, e);
	}
}

FrameModel* ModelBuilder::FromFile(char* str)
{
	//std::ifstream file = std::ifstream(filename);
	std::ifstream file;
	file.open(str);

	if (file.is_open() == false)
	{
		throw no_such_file();
	}

	int n, e;


	// Reading vertexes
	file >> n;
	Vertex3D *vertexes = new Vertex3D[n];
	if (vertexes == nullptr)
	{
		file.close();
		throw bad_memory();
	}
	ReadVertexes(file, vertexes, n);

	// Reading edges
	file >> e;
	Edge *edges = new Edge[e];
	if (edges == nullptr)
	{
		file.close();

		delete[] vertexes;
		throw bad_memory();
	}
	ReadEdges(file,edges,e);
	 
	file.close();

	FrameModel *record = new FrameModel(n, e, vertexes, edges);

	if (record == nullptr)
	{
		delete[] vertexes;
		delete[] edges;
		file.close();
		throw bad_memory();
	}

	return record;
}

FrameModel* ModelBuilder::Empty()
{
	return new FrameModel();
}