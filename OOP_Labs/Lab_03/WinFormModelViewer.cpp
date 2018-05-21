#include "stdafx.h"
#include "WinFormModelViewer.h"
#include "Vertex3D.h"

char* WinFormModelViewer::str2char(String^ str)
{
	char *res = (char*)malloc(sizeof(char)* (str->Length + 1));
	if (res == NULL)
	{
		return NULL;
	}
	int i = 0;
	for (; i < str->Length; i++)
	{
		res[i] = str[i];
	}
	res[i] = '\0';
	return res;
}

WinFormModelViewer::WinFormModelViewer(PictureBox^ targetCanvas, String^ modelSrc)
{
	char *fileName = str2char(modelSrc);
	model = FrameModel::MdlParseFile(fileName);
	free(fileName);
}

WinFormModelViewer::~WinFormModelViewer()
{
	delete model;
}

void WinFormModelViewer::Rotate(double x, double y, double z)
{
	model->Rotate(x, y, z);
}

void WinFormModelViewer::Scale(double k)
{
	model->Scale(k);
}
void WinFormModelViewer::Translate(double dx, double dy, double dz)
{
	Vertex3D *vec = new Vertex3D(dx, dy, dz);
	model->Translate(*vec);
	delete vec;
}

Image2D* WinFormModelViewer::getProjection()
{
	return model->Construct(new TransformProps());
}
void WinFormModelViewer::Draw()
{

}