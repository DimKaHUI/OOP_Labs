#include "stdafx.h"
#include "WinFormModelViewer.h"
#include "Vertex3D.h"

#define DEG2RAD M_PI / 180

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
	DrawingCanvas = targetCanvas;
	free(fileName);
}

WinFormModelViewer::~WinFormModelViewer()
{
	delete model;
}

void WinFormModelViewer::Rotate(double x, double y, double z)
{
	model->Rotate(DEG2RAD * x, DEG2RAD * y, DEG2RAD * z);
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
	return model->Construct();
}

void WinFormModelViewer::DrawLabels()
{
	// Drawing variables
	Graphics ^gr = DrawingCanvas->CreateGraphics();
	Brush ^brush = gcnew SolidBrush(EDGE_COLOR);
	Pen ^pen = gcnew Pen(brush);

	Brush ^labelBrush = gcnew SolidBrush(LABEL_COLOR);
	Pen ^labelPen = gcnew Pen(labelBrush);
	System::Drawing::Font ^font = gcnew System::Drawing::Font(LABEL_FONT_NAME, LABEL_FONT_SIZE);
	gr->Clear(Color::White);
	gr->TranslateTransform(getScrWidth() / 2, getScrHeight() / 2);
	gr->DrawLine(labelPen,
		0, -getScrHeight() / 2,
		0, getScrHeight() / 2
		);
	gr->DrawLine(labelPen,
		-getScrWidth() / 2, 0,
		getScrWidth() / 2, 0
		);

	gr->DrawString("X", font, labelBrush, getScrWidth() / 2 + X_LABEL_OFFSET, 0);
	gr->DrawString("Y", font, labelBrush, 0, -getScrHeight() / 2 + Y_LABEL_OFFSET);

}

System::Drawing::Size WinFormModelViewer::getScrSize()
{
	return DrawingCanvas->Size;
}

int WinFormModelViewer::getScrHeight()
{
	return getScrSize().Height;
}

int WinFormModelViewer::getScrWidth()
{
	return getScrSize().Width;
}

void WinFormModelViewer::DrawEdge(const Image2D *img, const Edge *edge)
{
	Graphics ^gr = DrawingCanvas->CreateGraphics();
	gr->TranslateTransform(getScrWidth() / 2, getScrHeight() / 2);
	Brush ^vertexBrush = gcnew SolidBrush(VERTEX_COLOR);
	Brush ^brush = gcnew SolidBrush(EDGE_COLOR);
	Pen ^pen = gcnew Pen(brush);
	int start_ind = edge->getEdgeStart();
	int end_index = edge->getEdgeEnd();
	int x1 = img->getVertexX(start_ind);//getVertex2DX(img, start_ind);
	int y1 = img->getVertexY(start_ind);
	int x2 = img->getVertexX(end_index);
	int y2 = img->getVertexY(end_index);
	gr->DrawLine(pen, x1, -y1, x2, -y2);
}

void WinFormModelViewer::Render(const Image2D *img)
{
	DrawLabels();

	Graphics ^gr = DrawingCanvas->CreateGraphics();
	Brush ^vertexBrush = gcnew SolidBrush(VERTEX_COLOR);

	// Drawing edges
	for (int i = 0; i < img->getEdgesCount(); i++)
		DrawEdge(img, &(img->getEdge(i)));

	// Drawing verts
	gr->TranslateTransform(getScrWidth() / 2, getScrHeight() / 2);
	for (int i = 0; i < img->getVertexCount(); i++)
	{
		int x = img->getVertexX(i);
		int y = img->getVertexY(i);

		gr->FillEllipse(
			vertexBrush,
			x - POINT_SIZE_HALF,
			-y - POINT_SIZE_HALF,
			POINT_SIZE, POINT_SIZE
			);
	}
}

void WinFormModelViewer::Draw()
{
	if (model == nullptr)
	{
		throw gcnew NullReferenceException();
	}

	Image2D *img = getProjection();
	Render(img);
	img->~Image2D();
}

FrameModel* WinFormModelViewer::getModel()
{
	return model;
}