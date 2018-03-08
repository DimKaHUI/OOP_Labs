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
		Brush ^vertexBrush = gcnew SolidBrush(Color::LightGreen);
		Brush ^brush = gcnew SolidBrush(Color::Blue);
		Brush ^blackBrush = gcnew SolidBrush(Color::Black);
		Pen ^pen = gcnew Pen(brush);
		Pen ^blackPen = gcnew Pen(blackBrush);
		System::Drawing::Font ^font = gcnew System::Drawing::Font("Arial", 14);
		

		gr->Clear(Color::White);
		gr->TranslateTransform(DrawingCanvas->Size.Width / 2, DrawingCanvas->Size.Height / 2);
		gr->DrawLine(blackPen,
			0, -DrawingCanvas->Size.Height / 2,
			0, DrawingCanvas->Size.Height / 2
			);
		gr->DrawLine(blackPen,
			-DrawingCanvas->Size.Width / 2, 0,
			DrawingCanvas->Size.Width / 2, 0
			);

		gr->DrawString("X", font, blackBrush, DrawingCanvas->Size.Width / 2 - 20, 0);
		gr->DrawString("Y", font, blackBrush, 0, -DrawingCanvas->Size.Height / 2 + 10);

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

		Vector3 rot = { DEG2RAD * angleX, DEG2RAD * angleY, DEG2RAD * angleZ };
		Construct(img, rot, {0, 0, 0});
		
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
			gr->FillEllipse(vertexBrush, img->points[i].x - 2.5, -img->points[i].y - 2.5, 5, 5);
		}

		free(img->edges);
		free(img->points);
		free(img);
	}

	System::Void MainForm::ProcessButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		DrawProjection();
	}

	System::Void MainForm::LoadButton_Click(System::Object^  sender, System::EventArgs^  e)
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
}