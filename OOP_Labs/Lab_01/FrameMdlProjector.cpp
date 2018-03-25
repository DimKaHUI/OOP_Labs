#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>

#include "FrameMdlProjector.h"

void setupVertex3D(Vertex3D *v, int x, int y, int z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

int getVertex3DX(FrameModel *mdl, int ind)
{
	Vertex3D v = mdl->vertexes[ind];
	return v.x;
}
int getVertex3DY(FrameModel *mdl, int ind)
{
	Vertex3D v = mdl->vertexes[ind];
	return v.y;
}
int getVertex3DZ(FrameModel *mdl, int ind)
{
	Vertex3D v = mdl->vertexes[ind];
	return v.y;
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

		//y = rec->vertexes[i].y * cos(ax) - rec->vertexes[i].z * sin(ax);
		y = getVertex3DY(rec, i) * cos(ax) - getVertex3DZ(rec, i) * sin(ax);

		z = getVertex3DY(rec, i) * sin(ax) + getVertex3DZ(rec, i) * cos(ax);

		//rec->vertexes[i].y = y;
		//rec->vertexes[i].z = z;
		setupVertex3D(&(rec->vertexes[i]), x, y, z);

		x = getVertex3DX(rec, i) * cos(ay) + getVertex3DZ(rec, i) * sin(ay);
		z = -getVertex3DX(rec, i) * sin(ay) + getVertex3DZ(rec, i) * cos(ay);

		//rec->vertexes[i].x = x;
		//rec->vertexes[i].z = z;
		setupVertex3D(&(rec->vertexes[i]), x, y, z);

		x = getVertex3DX(rec, i) * cos(az) - getVertex3DY(rec, i) * sin(az);
		y = getVertex3DX(rec, i) * sin(az) + getVertex3DY(rec, i) * cos(az);

		//rec->vertexes[i].x = x;;
		//rec->vertexes[i].y = y;
		setupVertex3D(&(rec->vertexes[i]), x, y, z);
	}
}

#ifndef RELATIVE_TRANSFORMATION
// Дублирует данные модели
FrameModel *CopyRecord(FrameModel *rec)
{
	FrameModel *copy = (FrameModel*)malloc(sizeof(FrameModel));
	copy->N = record->N;
	copy->E = record->E;
	copy->vertexes = (Vertex3D*)malloc(sizeof(Vertex3D) * copy->N);
	copy->edges = (Edge*)malloc(sizeof(Edge) * copy->E);
	for (int i = 0; i < copy->N; i++)
	{
		copy->vertexes[i] = rec->vertexes[i];
	}
	for (int i = 0; i < copy->E; i++)
	{
		copy->edges[i] = rec->edges[i];
	}
	return copy;
}
#endif

// Однородно масштабирует модель
void Scale(FrameModel *record, double scale)
{
	if (record == NULL)
		return;
	if (record->vertexes == NULL)
		return;
	for (int i = 0; i < record->N; i++)
	{
		int 
			x = getVertex3DX(record, i), 
			y = getVertex3DY(record, i),
			z = getVertex3DZ(record, i);
		//record->vertexes[i].x *= scale;
		//record->vertexes[i].y *= scale;
		//record->vertexes[i].z *= scale;
		setupVertex3D(&(record->vertexes[i]), x * scale, y * scale, z * scale);
	}
}


// Применяет трансформации и конструирует проекцию по результату
void Construct(FrameModel *record, Image2D* img, Vertex3D rot, double scale)
{
	if (record == NULL)
		return;
	if (record->vertexes == NULL)
		return;

	img->vertexCount = record->N;
	img->edgesCount = record->E;

	img->points = (Vertex2D*)malloc(sizeof(Vertex2D)*record->N);
	img->edges = (Edge*)malloc(sizeof(Edge)*record->E);

#ifdef RELATIVE_TRANSFORMATION

	// Трансформирование
	Rotate(record, DEG2RAD * rot.x, DEG2RAD * rot.y, DEG2RAD * rot.z);
	Scale(record, scale);

	// Проецирование
	for (int i = 0; i < record->N; i++)
	{
		int 
		x = getVertex3DX(record, i), 
		y = getVertex3DY(record, i);
		//img->points[i].x = (record->vertexes[i].x);
		//img->points[i].y = (record->vertexes[i].y);
		setupVertex2D(&(img->points[i]), x, y);
	}

	for (int i = 0; i < record->E; i++)
	{
		img->edges[i].start_index = record->edges[i].start_index;
		img->edges[i].end_index = record->edges[i].end_index;
	}

	

#else

	FrameModel *copy = CopyRecord(record);

	Rotate(copy, DEG2RAD * rot.x, DEG2RAD * rot.y, DEG2RAD * rot.z);

	for (int i = 0; i < record->N; i++)
	{
		img->points[i].x = (copy->vertexes[i].x);
		img->points[i].y = (copy->vertexes[i].y);
	}

	for (int i = 0; i < copy->E; i++)
	{
		img->edges[i].start_index = copy->edges[i].start_index;
		img->edges[i].end_index = copy->edges[i].end_index;
	}

	FreeRecord(copy);
#endif
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