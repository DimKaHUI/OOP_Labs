#pragma once

#include <stdio.h>
#include "Image2D.h"
#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>

#define ERROR_NO_SUCH_FILE -111
#define ERROR_FILE_PARSING -112
#define ERROR_BAD_ALLOC -113

#define DEG2RAD M_PI / 180

typedef struct Vertex3D
{
	float x, y, z;
};

typedef struct FrameMdlRecord
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
 *
 */

int MdlParseFile(char *filename);
void Construct(Image2D *img, Vector3 rot, Vector3 tran);