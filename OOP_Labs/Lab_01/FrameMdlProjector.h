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
#define ERROR_NO_DATA -114

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

typedef struct TransformProps
{
	Vertex3D Rotation;
	Vertex3D Translation;
	double scale;
};

/* ��������� �����:
 * int N - ���������� ������
 * int x, int y, int z [Repeat N] - �������
 * int E - ���������� ����
 * int i, int j [Repeat E] - ����
 */

// ���������� ������ �� �����
int MdlParseFile(FrameModel **record, char *filename);

// ��������������� ����������� 
int Construct(FrameModel *record, Image2D *img, const TransformProps *props);

// ������������ ������ ��-��� ������
void DisposeFrameModel(FrameModel *record);

void setupVertex3D(Vertex3D *v, float x, float y, float z);

float getVertex3DX(FrameModel *mdl, int ind);
float getVertex3DY(FrameModel *mdl, int ind);
float getVertex3DZ(FrameModel *mdl, int ind);