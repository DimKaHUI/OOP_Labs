#include "stdafx.h"
#include "MainForm.h"
#include "FrameMdlProjector.h"
#include <iostream>
#include <fstream>

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

	void MainForm::DrawProjection()
	{
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

		Image2D *img = (Image2D*)malloc(sizeof(Image2D));
		Double angleX, angleY, angleZ;
		if (!Double::TryParse(X_TextBox->Text, angleX))
		{
			MessageBox::Show("I/O Error in X argument");
			return;
		}
		if (!Double::TryParse(Y_TextBox->Text, angleY))
		{
			MessageBox::Show("I/O Error in Y argument");
			return;
		}
		if (!Double::TryParse(Z_TextBox->Text, angleZ))
		{
			MessageBox::Show("I/O Error in Z argument");
			return;
		}

		Vector3 rot = { angleX, angleY, angleZ };
		Construct(img, rot);
		
		// Drawing edges
		for (int i = 0; i < img->edgesCount; i++)
		{
			gr->DrawLine(pen,
				img->points[img->edges[i].start_index].x,
				-img->points[img->edges[i].start_index].y,
				img->points[img->edges[i].end_index].x,
				-img->points[img->edges[i].end_index].y);
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

	void MainForm::LoadFile()
	{
		String ^path = PathBox->Text;
		char *path_c = str2char(path);
		int error = MdlParseFile(path_c);
		switch (error)
		{
		case 0:
			DrawProjection();
			break;
		case ERROR_BAD_ALLOC:
			MessageBox::Show("Bad memory allocation", "ERROR");
			break;
		case ERROR_FILE_PARSING:
			MessageBox::Show("Bad file", "ERROR");
			break;
		case ERROR_NO_SUCH_FILE:
			MessageBox::Show("No such file", "ERROR");
			break;
		}

		free(path_c);
	}

	System::Void MainForm::ProcessButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		DrawProjection();
	}

	System::Void MainForm::LoadButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		LoadFile();
	}
}