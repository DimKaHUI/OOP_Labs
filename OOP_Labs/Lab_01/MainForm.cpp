#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "MainForm.h"
#include "FrameMdlProjector.h"
#include "strfuncs.h"

namespace WinFormsTemplate
{

	void ShowMessage(String^ msg)
	{
		MessageBox::Show(msg);
	}

	// Получает данные пользователя
	int MainForm::GetUserVals(Vertex3D *rot, Vertex3D *translate, double *scale)
	{
		Double angleX, angleY, angleZ, x, y, z;
		if (!Double::TryParse(X_TextBox->Text, angleX))
		{
			ShowMessage("I/O Error in X argument");
			return ERROR_USER_DATA;
		}
		if (!Double::TryParse(Y_TextBox->Text, angleY))
		{
			ShowMessage("I/O Error in Y argument");
			return ERROR_USER_DATA;
		}
		if (!Double::TryParse(Z_TextBox->Text, angleZ))
		{
			ShowMessage("I/O Error in Z argument");
			return ERROR_USER_DATA;
		}
		if (!Double::TryParse(scaleBox->Text, *scale))
		{
			ShowMessage("I/O Error in scale argument");
			return ERROR_USER_DATA;
		}
		if (!Double::TryParse(tranX_box->Text, x))
		{
			ShowMessage("I/O Error in translation X argument");
			return ERROR_USER_DATA;
		}
		if (!Double::TryParse(tranY_box->Text, y))
		{
			ShowMessage("I/O Error in translation Y argument");
			return ERROR_USER_DATA;
		}
		if (!Double::TryParse(tranZ_box->Text, z))
		{
			ShowMessage("I/O Error in translation Z argument");
			return ERROR_USER_DATA;
		}
		*rot = { angleX, angleY, angleZ };
		*translate = { x, y, z };
		return OK;
	}

	System::Drawing::Size MainForm::getScrSize()
	{
		return DrawingCanvas->Size;
	}

	int MainForm::getScrHeight()
	{
		return getScrSize().Height;
	}

	int MainForm::getScrWidth()
	{
		return getScrSize().Width;
	}

	

	void MainForm::DrawEdge(Image2D *img, Edge *edge)
	{
		Graphics ^gr = DrawingCanvas->CreateGraphics();
		gr->TranslateTransform(getScrWidth() / 2, getScrHeight() / 2);
		Brush ^vertexBrush = gcnew SolidBrush(VERTEX_COLOR);
		Brush ^brush = gcnew SolidBrush(EDGE_COLOR);
		Pen ^pen = gcnew Pen(brush);
		Vertex2D start, end;
		int start_ind = edge->start_index;
		int end_index = edge->end_index;
		int x1 = getVertex2DX(img, start_ind);
		int y1 = getVertex2DY(img, start_ind);
		int x2 = getVertex2DX(img, end_index);
		int y2 = getVertex2DY(img, end_index);
		gr->DrawLine(pen, x1, -y1, x2,	-y2);
	}

	void MainForm::DrawLabels()
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

	// Отображает проекцию модели
	void MainForm::DrawProjection(FrameModel *model)
	{
		if (model == NULL)
		{
			ShowMessage("Error: Model not loaded");
			return;
		}

		// Reading from MainForm
		Vertex3D rot;
		Vertex3D translate;
		double scale;		
		int err = GetUserVals(&rot, &translate, &scale);
		if (err)		
			return;

		TransformProps props = { rot, translate, scale };
		

		Image2D *img = (Image2D*)malloc(sizeof(Image2D));
		
		// Drawing variables
		Graphics ^gr = DrawingCanvas->CreateGraphics();
		Brush ^vertexBrush = gcnew SolidBrush(VERTEX_COLOR);

		DrawLabels();

		Construct(model, img, &props);
		
		// Drawing edges
		for (int i = 0; i < img->edgesCount; i++)		
			DrawEdge(img, &(model->edges[i]));		

		// Drawing verts
		gr->TranslateTransform(getScrWidth() / 2, getScrHeight() / 2);
		for (int i = 0; i < img->vertexCount; i++)		
			gr->FillEllipse(vertexBrush, img->points[i].x - POINT_SIZE / 2, -img->points[i].y - POINT_SIZE / 2, POINT_SIZE, POINT_SIZE);
		

		free(img->edges);
		free(img->points);
		free(img);
	}

	FrameModel *MainForm::LoadFile()
	{
		String ^path = PathBox->Text;
		char *path_c = str2char(path);
		FrameModel *record = NULL;
		int error = MdlParseFile(&record, path_c);
		switch (error)
		{
		case ERROR_BAD_ALLOC:
			ShowMessage("Bad memory allocation");
			record = NULL;
			break;
		case ERROR_FILE_PARSING:
			ShowMessage("Bad file");
			record = NULL;
			break;
		case ERROR_NO_SUCH_FILE:
			ShowMessage("No such file");
			record = NULL;
			break;
		}
		free(path_c);
		return record;
	}

	System::Void MainForm::ProcessButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		static FrameModel *model = NULL;
		if (sender == (Object^)LoadButton)
		{
			DisposeFrameModel(model);
			model = LoadFile();			
		}
		else if (sender == (Object^)ProcessButton)
		{
			DrawProjection(model);
		}
	}
}