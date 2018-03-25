#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>

#include "FrameMdlProjector.h"

void setupVertex3D(Vertex3D *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

float getVertex3DX(FrameModel *mdl, int ind)
{
	Vertex3D v = mdl->vertexes[ind];
	return v.x;
}
float getVertex3DY(FrameModel *mdl, int ind)
{
	Vertex3D v = mdl->vertexes[ind];
	return v.y;
}
float getVertex3DZ(FrameModel *mdl, int ind)
{
	Vertex3D v = mdl->vertexes[ind];
	return v.z;
}

// Загружает информацию о каркасной модели из указанного файла
int MdlParseFile(FrameModel **record, char *filename)
{
	if (*record != NULL)
	{
		DisposeFrameModel(*record);
		*record = NULL;
	}

	std::ifstream file = std::ifstream(filename);
	if (file.is_open() == false)
	{
		return ERROR_NO_SUCH_FILE;
	}
	*record = (FrameModel*)malloc(sizeof(FrameModel));
	if (*record == NULL)
	{
		file.close();
		return ERROR_BAD_ALLOC;
	}
	(*record)->vertexes = NULL;
	(*record)->edges = NULL;


	// Reading vertexes
	file >> (*record)->N;
	(*record)->vertexes = (Vertex3D*)malloc(sizeof(Vertex3D)* (*record)->N);
	for (int i = 0; i < (*record)->N; i++)
	{
		int x, y, z;
		file >> x;
		file >> y;
		file >> z;
		setupVertex3D(&(*record)->vertexes[i], x, y, z);
	}

	// Reading edges
	file >> (*record)->E;
	(*record)->edges = (Edge*)malloc(sizeof(Edge)* (*record)->E);
	for (int i = 0; i < (*record)->E; i++)
	{
		int s, e;
		file >> s;
		file >> e;
		setupEdge(&(*record)->edges[i], s, e);
	}

	file.close();
	return 0;
}

// Вращает модель
void Rotate(FrameModel *rec, float ax, float ay, float az)
{
	if (rec == NULL)
		return;
	if (rec->vertexes == NULL)
		return;
	for (int i = 0; i < rec->N; i++)
	{		
		double x = getVertex3DX(rec, i);
		double y = getVertex3DY(rec, i);
		double z = getVertex3DZ(rec, i);

		y = getVertex3DY(rec, i) * cos(ax) - getVertex3DZ(rec, i) * sin(ax);
		z = getVertex3DY(rec, i) * sin(ax) + getVertex3DZ(rec, i) * cos(ax);

		setupVertex3D(&(rec->vertexes[i]), x, y, z);

		x = getVertex3DX(rec, i) *cos(ay) + getVertex3DZ(rec, i) * sin(ay);
		z = -getVertex3DX(rec, i) * sin(ay) + getVertex3DZ(rec, i) * cos(ay);

		setupVertex3D(&(rec->vertexes[i]), x, y, z);

		x = getVertex3DX(rec, i) * cos(az) - getVertex3DY(rec, i) * sin(az);
		y = getVertex3DX(rec, i) * sin(az) + getVertex3DY(rec, i) * cos(az);

		setupVertex3D(&(rec->vertexes[i]), x, y, z);
	}
}

void Translate(FrameModel *record, Vertex3D tran)
{
	if (record == NULL)
		return;
	if (record->vertexes == NULL)
		return;
	for (int i = 0; i < record->N; i++)
	{
		float
			x = getVertex3DX(record, i),
			y = getVertex3DY(record, i),
			z = getVertex3DZ(record, i);
		setupVertex3D(&(record->vertexes[i]), x + tran.x, y + tran.y, z + tran.z);
	}
}


// Однородно масштабирует модель
void Scale(FrameModel *record, double scale)
{
	if (record == NULL)
		return;
	if (record->vertexes == NULL)
		return;
	for (int i = 0; i < record->N; i++)
	{
		float 
			x = getVertex3DX(record, i), 
			y = getVertex3DY(record, i),
			z = getVertex3DZ(record, i);
		setupVertex3D(&(record->vertexes[i]), x * scale, y * scale, z * scale);
	}
}

Vertex3D GetRotation(TransformProps *props)
{
	return props->Rotation;
}

Vertex3D GetTranslation(TransformProps *props)
{
	return props->Translation;
}

double GetScale(TransformProps *props)
{
	return props->scale;
}

// Применяет трансформации и конструирует проекцию по результату
void Construct(FrameModel *record, Image2D* img, TransformProps *props)
{
	if (record == NULL)
		return;
	if (record->vertexes == NULL)
		return;

	img->vertexCount = record->N;
	img->edgesCount = record->E;

	img->points = (Vertex2D*)malloc(sizeof(Vertex2D)*record->N);
	img->edges = (Edge*)malloc(sizeof(Edge)*record->E);

	Vertex3D rot = GetRotation(props);
	Vertex3D tran = GetTranslation(props);
	double scale = GetScale(props);

	// Трансформирование
	Rotate(record, DEG2RAD * rot.x, DEG2RAD * rot.y, DEG2RAD * rot.z);
	Translate(record, tran);
	Scale(record, scale);

	// Проецирование
	for (int i = 0; i < record->N; i++)
	{
		float 
		x = getVertex3DX(record, i), 
		y = getVertex3DY(record, i);
		setupVertex2D(&(img->points[i]), x, y);
	}

	for (int i = 0; i < record->E; i++)
	{
		int start = getEdgeStart(record->edges[i]);
		int end = getEdgeEnd(record->edges[i]);
		setupEdge(&(img->edges[i]), start, end);
	}
}

void DisposeFrameModel(FrameModel *record)
{
	if (record != NULL)
	{
		free(record->vertexes);
		free(record->edges);
		free(record);
	}
	record = NULL;
}