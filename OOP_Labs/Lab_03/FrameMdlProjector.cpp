#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>

#include "FrameMdlProjector.h"
#include "Exceptions.h"

float FrameModel::getVertexX(int ind) const
{
	Vertex3D v = vertexes[ind];
	return v.getX();
}
float FrameModel::getVertexY(int ind) const
{
	Vertex3D v = vertexes[ind];
	return v.getY();
}
float FrameModel::getVertexZ(int ind) const
{
	Vertex3D v = vertexes[ind];
	return v.getZ();
}

int FrameModel::getN() const
{
	return N;
}

int FrameModel::getE() const
{
	return E;
}

Edge FrameModel::getEdge(int i) const
{
	return edges[i];
}

Vertex3D FrameModel::getVertex(int i) const
{
	return vertexes[i];
}

// Вращает модель
void FrameModel::Rotate(float ax, float ay, float az)
{
	if (vertexes == NULL)
		return;
	for (int i = 0; i < N; i++)
	{		
		double x = getVertexX(i);//getVertex3DX(rec, i);
		double y = getVertexY(i);
		double z = getVertexZ(i);

		y = getVertexY(i) * cos(ax) - getVertexZ(i) * sin(ax);
		z = getVertexY(i) * sin(ax) + getVertexZ(i) * cos(ax);

		//setupVertex3D(&(rec->vertexes[i]), x, y, z);
		vertexes[i] = Vertex3D(x, y, z);

		x = getVertexX(i) * cos(ay) + getVertexZ(i) * sin(ay);
		z = -getVertexX(i) * sin(ay) + getVertexZ(i) * cos(ay);

		//setupVertex3D(&(rec->vertexes[i]), x, y, z);
		vertexes[i] = Vertex3D(x, y, z);

		x = getVertexX(i) * cos(az) - getVertexY(i) * sin(az);
		y = getVertexX(i) * sin(az) + getVertexY(i) * cos(az);

		vertexes[i] = Vertex3D(x, y, z);
	}
}

void FrameModel::Translate(Vertex3D tran)
{
	if (vertexes == nullptr)
		return;
	for (int i = 0; i < N; i++)
	{
		float
			x = getVertexX(i),
			y = getVertexY(i),
			z = getVertexZ(i);
		//setupVertex3D(&(record->vertexes[i]), x + tran.x, y + tran.y, z + tran.z);
		vertexes[i] = Vertex3D(x + tran.getX(), y + tran.getY(), z + tran.getZ());
	}
}


// Однородно масштабирует модель
void FrameModel::Scale(double scale)
{
	if (vertexes == NULL)
		return;
	for (int i = 0; i < N; i++)
	{
		float 
			x = getVertexX(i), 
			y = getVertexY(i),
			z = getVertexZ(i);
		//setupVertex3D(&(record->vertexes[i]), x * scale, y * scale, z * scale);
		vertexes[i] = Vertex3D(x * scale, y * scale, z * scale);
	}
}

Vertex3D GetRotation(const TransformProps *props)
{
	return props->Rotation;
}

Vertex3D GetTranslation(const TransformProps *props)
{
	return props->Translation;
}

double GetScale(const TransformProps *props)
{
	return props->Scale;
}

// Применяет трансформации и конструирует проекцию по результату
Image2D* FrameModel::Construct(TransformProps *props)
{
	if (vertexes == nullptr)
		throw bad_memory();

	/*int err = init_image(img, record->N, record->E);
	if (err == ERROR_IMG_BAD_ALLOC)
		return ERROR_BAD_ALLOC;*/

	Image2D *img = new Image2D(N, E);

	Vertex3D rot = GetRotation(props);
	Vertex3D tran = GetTranslation(props);
	double scale = GetScale(props);

	// Трансформирование
	Rotate(DEG2RAD * rot.getX(), DEG2RAD * rot.getY(), DEG2RAD * rot.getZ());
	Translate(tran);
	Scale(scale);

	// Проецирование
	for (int i = 0; i < N; i++)
	{
		float
			x = getVertexX(i),
			y = getVertexY(i);
		//setupVertex2D(&(img->points[i]), x, y);
		//img->points[i] = Vertex2D(x, y);
		img->setVertex(i, x, y);
	}

	for (int i = 0; i < E; i++)
	{
		int start = edges[i].getEdgeStart();
		int end = edges[i].getEdgeEnd();
		//img->edges[i] = Edge(start, end);
		img->setEdge(i, start, end);
	}

	return img;
}

Image2D* FrameModel::Construct()
{
	if (vertexes == nullptr)
		throw bad_memory();

	Image2D *img = new Image2D(N, E);

	// Проецирование
	for (int i = 0; i < N; i++)
	{
		float
			x = getVertexX(i),
			y = getVertexY(i);
		//setupVertex2D(&(img->points[i]), x, y);
		//img->points[i] = Vertex2D(x, y);
		img->setVertex(i, x, y);
	}

	for (int i = 0; i < E; i++)
	{
		int start = edges[i].getEdgeStart();
		int end = edges[i].getEdgeEnd();
		//img->edges[i] = Edge(start, end);
		img->setEdge(i, start, end);
	}

	return img;
}


FrameModel::~FrameModel()
{
	//free(vertexes);
	delete[] vertexes;
	//free(edges);
	delete[] edges;
	vertexes = nullptr;
	edges = nullptr;
}

FrameModel::FrameModel(int n, int e, Vertex3D *verts, Edge *edges)
{
	N = n;
	E = e;
	vertexes = verts;
	this->edges = edges;
}

FrameModel::FrameModel()
{
	N = 0;
	E = 0;
	vertexes = nullptr;
	this->edges = nullptr;
}