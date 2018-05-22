#pragma once

#include "FrameMdlProjector.h"

ref class ModelBuilder
{

private:
	static void ReadVertexes(std::ifstream &file, Vertex3D *verts, int n);
	static void ReadEdges(std::ifstream &file, Edge *edges, int n);

public:
	static FrameModel* FromFile(char* str);
	static FrameModel* Empty();

};

