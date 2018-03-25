#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Image2D.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define RELATIVE_TRANSFORMATION

#define ERROR_NO_SUCH_FILE -111
#define ERROR_FILE_PARSING -112
#define ERROR_BAD_ALLOC -113

#define DEG2RAD M_PI / 180

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

// Считывание модели из файла
int MdlParseFile(FrameModel **record, char *filename);

// Конструирование изображения 
void Construct(FrameModel *record, Image2D *img, Vertex3D rot, double scale);

// Освобождение памяти из-под модели
void DisposeFrameModel(FrameModel *record);

void setupVertex3D(Vertex3D *v, int x, int y, int z);

int getVertex3DX(FrameModel *mdl, int ind);
int getVertex3DY(FrameModel *mdl, int ind);
int getVertex3DZ(FrameModel *mdl, int ind);