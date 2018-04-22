#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Image2D.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define ERROR_NO_SUCH_FILE -111
#define ERROR_FILE_PARSING -112
#define ERROR_BAD_ALLOC -113
#define ERROR_NO_DATA -114
#define OK_PROJ -115

#define DEG2RAD M_PI / 180

class Vertex3D
{
	float x, y, z;
public:
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	float getZ()
	{
		return z;
	}
	Vertex3D(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vertex3D()
	{
		x = 0; y = 0; z = 0;
	}
};

typedef struct TransformProps
{
	Vertex3D Rotation;
	Vertex3D Translation;
	double Scale;
};

class FrameModel
{
	int N;
	Vertex3D *vertexes;
	int E;
	Edge *edges;

public:
	int getN() const;
	int getE() const;
	Edge getEdge() const;
	Vertex3D getVertex() const;
	void setEdge(int i, int s, int e);
	void setVertex(int i, float x, float y, float z);
	FrameModel();
	~FrameModel();

	float getVertexX(int i) const;
	float getVertexY(int i) const;
	float getVertexZ(int i) const;

	static FrameModel *MdlParseFile(char *filename);

	void Rotate(float ax, float ay, float az);
	void Translate(Vertex3D tran);
	void Scale(double val);

	Image2D *Construct(TransformProps *props);

};

/* Структура файла:
 * int N - количество вершин
 * int x, int y, int z [Repeat N] - вершины
 * int E - количество рёбер
 * int i, int j [Repeat E] - рёбра
 */
