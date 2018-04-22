#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "MainForm.h"
#include "FrameMdlProjector.h"
#include "strfuncs.h"
#include "UserMessage.h"
#include "Exceptions.h"

namespace WinFormsTemplate
{	

	// Получает данные пользователя
	int MainForm::GetUserVals(Vertex3D *rot, Vertex3D *translate, double *scale)
	{
		double angleX, angleY, angleZ, x, y, z;
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
		*rot = { (float)angleX, (float)angleY, (float)angleZ };
		*translate = { (float)x, (float)y, (float)z };
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

	

	void MainForm::DrawEdge(const Image2D *img, const Edge *edge)
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

	void MainForm::Render(const Image2D *img)
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

	// Отображает проекцию модели
	int MainForm::DrawProjection(FrameModel *model)
	{
		if (model == NULL)
		{
			return ERROR_NO_DATA;
		}

		// Reading from MainForm
		Vertex3D rot;
		Vertex3D translate;
		double scale;		
		int err = GetUserVals(&rot, &translate, &scale);
		if (err != OK)		
			return err;
		TransformProps props = { rot, translate, scale };		

		Image2D *img = model->Construct(&props);		
		Render(img);
		img->~Image2D();
	}

	FrameModel *MainForm::LoadFile()
	{
		String ^path = PathBox->Text;
		char *path_c = str2char(path);
		if (path_c == NULL)
		{
			ShowMessage("String data allocated badly");
			return NULL;
		}

		FrameModel *record;
		try
		{
			record = record->MdlParseFile(path_c);
		}
		finally
		{
			free(path_c);
		}
		return record;
	}

	System::Void MainForm::ProcessButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		static FrameModel *model = nullptr;
		if (sender == (Object^)LoadButton)
		{
			if (model != nullptr)
				model->~FrameModel();// DisposeFrameModel(model);
			try
			{
				model = LoadFile();
			}			
			catch (bad_memory& ex)
			{
				ShowMessage("Bad memory allocation");
				model = nullptr;
			}
			catch (no_such_file& ex)
			{
				ShowMessage("Bad file");
				model = nullptr;
			}
		}
		else if (sender == (Object^)ProcessButton)
		{
			int err = DrawProjection(model);
			switch (err)
			{
			case ERROR_BAD_ALLOC:
				ShowMessage("Error: Bad memory allocation");
				break;
			case ERROR_NO_DATA:
				ShowMessage("Error: Model not loaded");
				break;
			}
		}
	}
}