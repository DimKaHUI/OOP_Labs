#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "MainForm.h"
#include "FrameMdlProjector.h"

namespace WinFormsTemplate
{

	char *str2char(String^ str)
	{
		char *res = (char*)malloc(sizeof(char)* (str->Length + 1));
		int i = 0;
		for (; i < str->Length; i++)
		{
			res[i] = str[i];
		}
		res[i] = '\0';
		return res;
	}

	// Получает данные пользователя
	int MainForm::GetUserVals(Vertex3D *rot, double *scale)
	{
		Double angleX, angleY, angleZ;
		if (!Double::TryParse(X_TextBox->Text, angleX))
		{
			MessageBox::Show("I/O Error in X argument");
			return ERROR_USER_DATA;
		}
		if (!Double::TryParse(Y_TextBox->Text, angleY))
		{
			MessageBox::Show("I/O Error in Y argument");
			return ERROR_USER_DATA;
		}
		if (!Double::TryParse(Z_TextBox->Text, angleZ))
		{
			MessageBox::Show("I/O Error in Z argument");
			return ERROR_USER_DATA;
		}
		if (!Double::TryParse(scaleBox->Text, *scale))
		{
			MessageBox::Show("I/O Error in scale argument");
			return ERROR_USER_DATA;
		}
		*rot = { angleX, angleY, angleZ };
		return OK;
	}

	void MainForm::DrawEdge(Image2D *img, Edge *edge)
	{
		Graphics ^gr = DrawingCanvas->CreateGraphics();
		gr->TranslateTransform(DrawingCanvas->Size.Width / 2, DrawingCanvas->Size.Height / 2);
		Brush ^vertexBrush = gcnew SolidBrush(VERTEX_COLOR);
		Brush ^brush = gcnew SolidBrush(EDGE_COLOR);
		Pen ^pen = gcnew Pen(brush);
		Vertex2D start, end;
		int start_ind = edge->start_index;
		int end_index = edge->end_index;
		gr->DrawLine(pen,
			img->points[start_ind].x,
			-img->points[start_ind].y,
			img->points[end_index].x,
			-img->points[end_index].y);
	}

	// Отображает проекцию модели
	void MainForm::DrawProjection(FrameModel *model)
	{
		if (model == NULL)
		{
			MessageBox::Show("Error: Model not loaded");
			return;
		}

		// Reading from MainForm
		Vertex3D rot;
		double scale;
		int err = GetUserVals(&rot, &scale);
		if (err)
		{
			return;
		}

		Image2D *img = (Image2D*)malloc(sizeof(Image2D));
		
		// Drawing variables
		Graphics ^gr = DrawingCanvas->CreateGraphics();
		Brush ^vertexBrush = gcnew SolidBrush(VERTEX_COLOR);
		Brush ^brush = gcnew SolidBrush(EDGE_COLOR);		
		Pen ^pen = gcnew Pen(brush);

#ifdef DRAW_LABELS
		Brush ^labelBrush = gcnew SolidBrush(LABEL_COLOR);
		Pen ^labelPen = gcnew Pen(labelBrush);
		System::Drawing::Font ^font = gcnew System::Drawing::Font(LABEL_FONT_NAME, LABEL_FONT_SIZE);
		gr->Clear(Color::White);
		gr->TranslateTransform(DrawingCanvas->Size.Width / 2, DrawingCanvas->Size.Height / 2);
		gr->DrawLine(labelPen,
			0, -DrawingCanvas->Size.Height / 2,
			0, DrawingCanvas->Size.Height / 2
			);
		gr->DrawLine(labelPen,
			-DrawingCanvas->Size.Width / 2, 0,
			DrawingCanvas->Size.Width / 2, 0
			);

		gr->DrawString("X", font, labelBrush, DrawingCanvas->Size.Width / 2 + X_LABEL_OFFSET, 0);
		gr->DrawString("Y", font, labelBrush, 0, -DrawingCanvas->Size.Height / 2 + Y_LABEL_OFFSET);
#endif		

		Construct(model, img, rot, scale);
		
		// Drawing edges
		for (int i = 0; i < img->edgesCount; i++)
		{
			DrawEdge(img, &(model->edges[i]));
		}

		// Drawing verts
		for (int i = 0; i < img->vertexCount; i++)
		{
			gr->FillEllipse(vertexBrush, img->points[i].x - POINT_SIZE / 2, -img->points[i].y - POINT_SIZE / 2, POINT_SIZE, POINT_SIZE);
		}

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
			MessageBox::Show("Bad memory allocation", "ERROR");
			record = NULL;
			break;
		case ERROR_FILE_PARSING:
			MessageBox::Show("Bad file", "ERROR");
			record = NULL;
			break;
		case ERROR_NO_SUCH_FILE:
			MessageBox::Show("No such file", "ERROR");
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