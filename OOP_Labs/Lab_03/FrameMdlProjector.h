#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Image2D.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vertex3D.h"
#include "TransformProps.h"

#define ERROR_NO_SUCH_FILE -111
#define ERROR_FILE_PARSING -112
#define ERROR_BAD_ALLOC -113
#define ERROR_NO_DATA -114
#define OK_PROJ -115

#define DEG2RAD M_PI / 180

class FrameModel
{
protected:
	int N;
	Vertex3D *vertexes;
	int E;
	Edge *edges;

public:

	static FrameModel *MdlParseFile(char *filename);

	FrameModel();

	int getN() const;
	int getE() const;
	Edge getEdge(int i) const;
	Vertex3D getVertex(int i) const;
	void setEdge(int i, int s, int e);
	void setVertex(int i, float x, float y, float z);
	
	~FrameModel();

	float getVertexX(int i) const;
	float getVertexY(int i) const;
	float getVertexZ(int i) const;	

	void Rotate(float ax, float ay, float az);
	void Translate(Vertex3D tran);
	void Scale(double val);

	Image2D *Construct(TransformProps *props);

	virtual void operation()
	{
		return;
	}

};

/* Структура файла:
 * int N - количество вершин
 * int x, int y, int z [Repeat N] - вершины
 * int E - количество рёбер
 * int i, int j [Repeat E] - рёбра
 */
