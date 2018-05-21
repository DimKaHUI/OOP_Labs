#pragma once

#define POINT_SIZE 5
#define POINT_SIZE_HALF 2
#define X_LABEL_OFFSET -20
#define Y_LABEL_OFFSET 10
#define LABEL_FONT_SIZE 14
#define LABEL_FONT_NAME "Arial"
#define LABEL_COLOR Color::LightGray
#define VERTEX_COLOR Color::Red
#define EDGE_COLOR Color::Black

#include <stdlib.h>
#include "FrameMdlProjector.h"
#include "Exceptions.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class WinFormModelViewer
{
private:
	PictureBox^ DrawingCanvas;
	FrameModel *model;
	Image2D *img;
	static char* WinFormModelViewer::str2char(String^ str);

	void Render(const Image2D *img);
	void DrawLabels();

	void WinFormModelViewer::DrawEdge(const Image2D *img, const Edge *edge);
	int WinFormModelViewer::getScrWidth();
	int WinFormModelViewer::getScrHeight();
	System::Drawing::Size WinFormModelViewer::getScrSize();

public:
	WinFormModelViewer(PictureBox^ targetCanvas, String^ modelSrc);
	~WinFormModelViewer();

	void Rotate(double x, double y, double z);
	void Scale(double k);
	void Translate(double dx, double dy, double dz);

	Image2D* getProjection();
	FrameModel* getModel();
	void Draw();
};

