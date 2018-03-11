#pragma once

#include <stdio.h>
#include "Image2D.h"
#include <iostream>
#include <fstream>
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

/* ��������� �����:
 * int N - ���������� ������
 * int x, int y, int z [Repeat N] - �������
 * int E - ���������� ����
 * int i, int j [Repeat E] - ����
 *
 */

int MdlParseFile(char *filename);
void Construct(Image2D *img, Vector3 rot);
void DisposeFrameModel();