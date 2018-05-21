#pragma once

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
	FrameModel *model;
	Image2D *img;
	static char* WinFormModelViewer::str2char(String^ str);

public:
	WinFormModelViewer(PictureBox^ targetCanvas, String^ modelSrc);
	~WinFormModelViewer();

	void Rotate(double x, double y, double z);
	void Scale(double k);
	void Translate(double dx, double dy, double dz);

	Image2D* getProjection();
	void Draw();
};

