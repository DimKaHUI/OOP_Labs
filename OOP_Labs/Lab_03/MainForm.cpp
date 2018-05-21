#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "MainForm.h"
#include "FrameMdlProjector.h"
#include "strfuncs.h"
#include "UserMessage.h"
#include "Exceptions.h"
#include "PerimetrCounter.h"
#include "WinFormModelViewer.h"

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
	

	System::Void MainForm::ProcessButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//static FrameModel *model = nullptr;
		if (sender == (Object^)LoadButton)
		{			
			try
			{
				String^ path = PathBox->Text;
				Viewer = gcnew WinFormModelViewer(DrawingCanvas, path);
			}			
			catch (bad_memory& ex)
			{
				ShowMessage("Bad memory allocation");
				Viewer = nullptr;
			}
			catch (no_such_file& ex)
			{
				ShowMessage("Bad file");
				Viewer = nullptr;
			}			
		}
		else if (sender == (Object^)ProcessButton)
		{
			try
			{
				Vertex3D rotation, translation;
				double scale;
				if (GetUserVals(&rotation, &translation, &scale) != OK)
					throw gcnew ArgumentException();
				Viewer->Rotate(rotation.getX(), rotation.getY(), rotation.getZ());
				Viewer->Translate(translation.getX(), translation.getY(), translation.getZ());
				Viewer->Scale(scale);
				Viewer->Draw();
			}
			catch (NullReferenceException^ ex)
			{
				ShowMessage("Model not loaded");
			}
			catch (ArgumentException^ ex)
			{
				ShowMessage("Invalid transformation preferences");
			}
		}
		else if(sender == (Object^)PerimButt)
		{
			if(Viewer != nullptr)
			{
				PerimetrCounter* counter = new PerimetrCounter();
				counter->SetComponent(Viewer->getModel());
				counter->operation();
			}
		}
	}
}