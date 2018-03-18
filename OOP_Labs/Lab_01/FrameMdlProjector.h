#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>

#define RELATIVE_TRANSFORMATION

#define ERROR_NO_SUCH_FILE -111
#define ERROR_FILE_PARSING -112
#define ERROR_BAD_ALLOC -113

#define DEG2RAD M_PI / 180


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

typedef struct Vertex3D
{
	float x, y, z;
};

typedef struct FrameModel
{
	int N;
	Vertex3D *vertexes;
	int E;
	Edge *edges;
};

/* Структура файла:
 * int N - количество вершин
 * int x, int y, int z [Repeat N] - вершины
 * int E - количество рёбер
 * int i, int j [Repeat E] - рёбра
 */

int MdlParseFile(FrameModel **record, char *filename);
void Construct(FrameModel *record, Image2D *img, Vertex3D rot, double scale);
void DisposeFrameModel(FrameModel *record);