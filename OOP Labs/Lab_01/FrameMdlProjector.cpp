#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "FrameMdlProjector.h"
#include <cmath>
#include "RotationMatrix.h"

// Global record
FrameMdlRecord *record = NULL;

void FreeRecord(FrameMdlRecord *rec)
{
	free(rec->vertexes);
	free(rec->edges);
	free(rec);
}

// Загружает информацию о каркасной модели из указанного файла
int MdlParseFile(char *filename)
{
	std::ifstream file = std::ifstream(filename);
	if (file.is_open() == false)
	{
		return ERROR_NO_SUCH_FILE;
	}
	record = (FrameMdlRecord*)malloc(sizeof(FrameMdlRecord));
	if (record == NULL)
	{
		return ERROR_BAD_ALLOC;
	}
	record->vertexes = NULL;
	record->edges = NULL;


	// Reading vertexes
	file >> record->N;
	record->vertexes = (Vertex3D*)malloc(sizeof(Vertex3D)* record->N);
	for (int i = 0; i < record->N; i++)
	{
		file >> record->vertexes[i].x;
		file >> record->vertexes[i].y;
		file >> record->vertexes[i].z;
	}

	// Reading edges
	file >> record->E;
	record->edges = (Edge*)malloc(sizeof(Edge)* record->E);
	for (int i = 0; i < record->E; i++)
	{
		file >> record->edges[i].start_index;
		file >> record->edges[i].end_index;
	}

	file.close();
	return 0;
}

// Вращает модель
void Rotate(FrameMdlRecord *rec, float ax, float ay, float az)
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

// Смещает модель
void Translate(FrameMdlRecord *rec, int x, int y, int z)
{
	for (int i = 0; i < record->N; i++)
	{
		rec->vertexes[i].x += x;
		rec->vertexes[i].y += y;
		rec->vertexes[i].z += z;
	}
}

// Дублирует данные модели
FrameMdlRecord *CopyRecord(FrameMdlRecord *rec)
{
	FrameMdlRecord *copy = (FrameMdlRecord*)malloc(sizeof(FrameMdlRecord));
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


// Применяет трансформации и конструирует проекцию по результату
void Construct(Image2D* img, Vector3 rot, Vector3 tran)
{
	img->vertexCount = record->N;
	img->edgesCount = record->E;

	img->points = (Vertex2D*)malloc(sizeof(Vertex2D)*record->N);
	img->edges = (Edge*)malloc(sizeof(Edge)*record->E);

	FrameMdlRecord *copy = record;// = CopyRecord(record);	

	//Translate(copy, tran.x, tran.y, tran.z);
	Rotate(record, rot.x, rot.y, rot.z);

	for (int i = 0; i < copy->N; i++)
	{
		img->points[i].x = (copy->vertexes[i].x);
		img->points[i].y = (copy->vertexes[i].y);
	}

	for (int i = 0; i < copy->E; i++)
	{
		img->edges[i].start_index = copy->edges[i].start_index;
		img->edges[i].end_index = copy->edges[i].end_index;
	}
	//FreeRecord(copy);
}