#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>

#include "FrameMdlProjector.h"


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
	if (record == NULL)
	{
		return ERROR_BAD_ALLOC;
	}
	(*record)->vertexes = NULL;
	(*record)->edges = NULL;


	// Reading vertexes
	file >> (*record)->N;
	(*record)->vertexes = (Vertex3D*)malloc(sizeof(Vertex3D)* (*record)->N);
	for (int i = 0; i < (*record)->N; i++)
	{
		file >> (*record)->vertexes[i].x;
		file >> (*record)->vertexes[i].y;
		file >> (*record)->vertexes[i].z;
	}

	// Reading edges
	file >> (*record)->E;
	(*record)->edges = (Edge*)malloc(sizeof(Edge)* (*record)->E);
	for (int i = 0; i < (*record)->E; i++)
	{
		file >> (*record)->edges[i].start_index;
		file >> (*record)->edges[i].end_index;
	}

	file.close();
	return 0;
}

// Вращает модель
void Rotate(FrameModel *rec, float ax, float ay, float az)
{
	for (int i = 0; i < rec->N; i++)
	{		
		double x = rec->vertexes[i].x;
		double y = rec->vertexes[i].y;
		double z = rec->vertexes[i].z;

		y = rec->vertexes[i].y * cos(ax) - rec->vertexes[i].z * sin(ax);
		z = rec->vertexes[i].y * sin(ax) + rec->vertexes[i].z * cos(ax);

		rec->vertexes[i].y = y;
		rec->vertexes[i].z = z;

		x = rec->vertexes[i].x * cos(ay) + rec->vertexes[i].z * sin(ay);
		z = -rec->vertexes[i].x * sin(ay) + rec->vertexes[i].z * cos(ay);

		rec->vertexes[i].x = x;
		rec->vertexes[i].z = z;

		x = rec->vertexes[i].x * cos(az) - rec->vertexes[i].y * sin(az);
		y = rec->vertexes[i].x * sin(az) + rec->vertexes[i].y * cos(az);

		rec->vertexes[i].x = x;;
		rec->vertexes[i].y = y;
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
	for (int i = 0; i < record->N; i++)
	{
		record->vertexes[i].x *= scale;
		record->vertexes[i].y *= scale;
		record->vertexes[i].z *= scale;
	}
}


// Применяет трансформации и конструирует проекцию по результату
void Construct(FrameModel *record, Image2D* img, Vertex3D rot, double scale)
{
	img->vertexCount = record->N;
	img->edgesCount = record->E;

	img->points = (Vertex2D*)malloc(sizeof(Vertex2D)*record->N);
	img->edges = (Edge*)malloc(sizeof(Edge)*record->E);

#ifdef RELATIVE_TRANSFORMATION

	Rotate(record, DEG2RAD * rot.x, DEG2RAD * rot.y, DEG2RAD * rot.z);
	Scale(record, scale);

	for (int i = 0; i < record->N; i++)
	{
		img->points[i].x = (record->vertexes[i].x);
		img->points[i].y = (record->vertexes[i].y);
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