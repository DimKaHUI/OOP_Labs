#pragma once
#include <stdlib.h>
#include <cmath>

typedef struct Matrix
{
	int rows;
	int cols;
	double **data;
};

void MatrixX(Matrix *m, float angle)
{
	int size = 3;
	m->rows = 3;
	m->cols = 3;
	m->data = (double**)malloc(sizeof(double*)* size);
	for (int i = 0; i < size; i++)
	{
		m->data[i] = (double*)calloc(sizeof(double), size);
	}

	m->data[0][0] = 1;
	m->data[1][1] = cos(angle);
	m->data[2][2] = cos(angle);
	m->data[1][2] = sin(angle);
	m->data[2][1] = -sin(angle);
}

void MatrixY(Matrix *m, float angle)
{
	int size = 3;
	m->rows = 3;
	m->cols = 3;
	m->data = (double**)malloc(sizeof(double*)* size);
	for (int i = 0; i < size; i++)
	{
		m->data[i] = (double*)calloc(sizeof(double),  size);
	}

	m->data[1][1] = 1;
	m->data[0][0] = cos(angle);
	m->data[2][2] = cos(angle);
	m->data[0][2] = -sin(angle);
	m->data[2][0] = sin(angle);
}

void MatrixZ(Matrix *m, float angle)
{
	int size = 3;
	m->rows = 3;
	m->cols = 3;
	m->data = (double**)malloc(sizeof(double*)* size);
	for (int i = 0; i < size; i++)
	{
		m->data[i] = (double*)calloc(sizeof(double), size);
	}

	m->data[0][0] = cos(angle);
	m->data[1][1] = cos(angle);
	m->data[2][2] = 1;
	m->data[0][1] = sin(angle);
	m->data[1][0] = -sin(angle);
}

void VecToCol(Matrix *m, double x, double y, double z)
{
	m->cols = 1;
	m->rows = 3;
	m->data = (double**)malloc(sizeof(double*)* m->rows);
	for (int i = 0; i < 3; i++)
	{
		m->data[i] = (double*)calloc(sizeof(double), m->cols);
	}
	m->data[0][0] = x;
	m->data[0][1] = y;
	m->data[0][2] = z;
}

void MProd(Matrix *m, Matrix *a, Matrix *b)
{
	m->cols = b->rows;
	m->rows = a->cols;
	m->data = (double**)malloc(sizeof(double*)* m->rows);
	for (int i = 0; i < 3; i++)
	{
		m->data[i] = (double*)calloc(sizeof(double), m->cols);
	}
	for (int i = 0; i < m->rows; i++)
	for (int j = 0; j < m->cols; j++)
	{
		for (int r = 0; r < a->cols; r++)
			m->data[i][j] = a->data[i][r] * b->data[r][i];
	}
}

