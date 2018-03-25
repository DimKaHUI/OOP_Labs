#pragma once

#include <stdlib.h>
#include "FrameMdlProjector.h"

#define POINT_SIZE 5
#define X_LABEL_OFFSET -20
#define Y_LABEL_OFFSET 10
#define LABEL_FONT_SIZE 14
#define LABEL_FONT_NAME "Arial"
#define LABEL_COLOR Color::LightGray
#define DRAW_LABELS
#define VERTEX_COLOR Color::Red
#define EDGE_COLOR Color::Black
#define ERROR_USER_DATA -111
#define OK 0


namespace WinFormsTemplate {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(String ^filename)
		{
			InitializeComponent();			
			PathBox->Text = filename;
		}

		MainForm()
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  DrawingCanvas;
	private: System::Windows::Forms::TextBox^  X_TextBox;
	protected:

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  Y_TextBox;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  Z_TextBox;

	private: System::Windows::Forms::Button^  ProcessButton;
	private: System::Windows::Forms::Button^  LoadButton;
	private: System::Windows::Forms::TextBox^  PathBox;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;


	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  scaleBox;


	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->DrawingCanvas = (gcnew System::Windows::Forms::PictureBox());
			this->X_TextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Y_TextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->Z_TextBox = (gcnew System::Windows::Forms::TextBox());
			this->ProcessButton = (gcnew System::Windows::Forms::Button());
			this->LoadButton = (gcnew System::Windows::Forms::Button());
			this->PathBox = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->scaleBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DrawingCanvas))->BeginInit();
			this->SuspendLayout();
			// 
			// DrawingCanvas
			// 
			this->DrawingCanvas->BackColor = System::Drawing::Color::White;
			this->DrawingCanvas->Location = System::Drawing::Point(177, 8);
			this->DrawingCanvas->Margin = System::Windows::Forms::Padding(2);
			this->DrawingCanvas->Name = L"DrawingCanvas";
			this->DrawingCanvas->Size = System::Drawing::Size(469, 356);
			this->DrawingCanvas->TabIndex = 0;
			this->DrawingCanvas->TabStop = false;
			// 
			// X_TextBox
			// 
			this->X_TextBox->Location = System::Drawing::Point(52, 26);
			this->X_TextBox->Margin = System::Windows::Forms::Padding(2);
			this->X_TextBox->Name = L"X_TextBox";
			this->X_TextBox->Size = System::Drawing::Size(123, 20);
			this->X_TextBox->TabIndex = 1;
			this->X_TextBox->Text = L"0";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(5, 28);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Euler X:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(5, 49);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(44, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Euler Y:";
			// 
			// Y_TextBox
			// 
			this->Y_TextBox->Location = System::Drawing::Point(52, 47);
			this->Y_TextBox->Margin = System::Windows::Forms::Padding(2);
			this->Y_TextBox->Name = L"Y_TextBox";
			this->Y_TextBox->Size = System::Drawing::Size(123, 20);
			this->Y_TextBox->TabIndex = 3;
			this->Y_TextBox->Text = L"0";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(5, 70);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(44, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Euler Z:";
			// 
			// Z_TextBox
			// 
			this->Z_TextBox->Location = System::Drawing::Point(52, 68);
			this->Z_TextBox->Margin = System::Windows::Forms::Padding(2);
			this->Z_TextBox->Name = L"Z_TextBox";
			this->Z_TextBox->Size = System::Drawing::Size(123, 20);
			this->Z_TextBox->TabIndex = 5;
			this->Z_TextBox->Text = L"0";
			// 
			// ProcessButton
			// 
			this->ProcessButton->Location = System::Drawing::Point(9, 133);
			this->ProcessButton->Margin = System::Windows::Forms::Padding(2);
			this->ProcessButton->Name = L"ProcessButton";
			this->ProcessButton->Size = System::Drawing::Size(165, 27);
			this->ProcessButton->TabIndex = 7;
			this->ProcessButton->Text = L"Apply";
			this->ProcessButton->UseVisualStyleBackColor = true;
			this->ProcessButton->Click += gcnew System::EventHandler(this, &MainForm::ProcessButton_Click);
			// 
			// LoadButton
			// 
			this->LoadButton->Location = System::Drawing::Point(7, 337);
			this->LoadButton->Margin = System::Windows::Forms::Padding(2);
			this->LoadButton->Name = L"LoadButton";
			this->LoadButton->Size = System::Drawing::Size(165, 27);
			this->LoadButton->TabIndex = 8;
			this->LoadButton->Text = L"Load frame";
			this->LoadButton->UseVisualStyleBackColor = true;
			this->LoadButton->Click += gcnew System::EventHandler(this, &MainForm::ProcessButton_Click);
			// 
			// PathBox
			// 
			this->PathBox->Location = System::Drawing::Point(9, 317);
			this->PathBox->Margin = System::Windows::Forms::Padding(2);
			this->PathBox->Name = L"PathBox";
			this->PathBox->Size = System::Drawing::Size(165, 20);
			this->PathBox->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(8, 302);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(84, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Model file name:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(91, 11);
			this->label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(47, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Degrees";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(8, 112);
			this->label9->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(37, 13);
			this->label9->TabIndex = 13;
			this->label9->Text = L"Scale:";
			// 
			// scaleBox
			// 
			this->scaleBox->Location = System::Drawing::Point(52, 109);
			this->scaleBox->Margin = System::Windows::Forms::Padding(2);
			this->scaleBox->Name = L"scaleBox";
			this->scaleBox->Size = System::Drawing::Size(123, 20);
			this->scaleBox->TabIndex = 12;
			this->scaleBox->Text = L"1";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(655, 372);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->scaleBox);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->PathBox);
			this->Controls->Add(this->LoadButton);
			this->Controls->Add(this->ProcessButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->Z_TextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->Y_TextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->X_TextBox);
			this->Controls->Add(this->DrawingCanvas);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MainForm";
			this->Text = L"FrameViewer";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DrawingCanvas))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private:
		// Точка входа - обработ
		System::Void ProcessButton_Click(System::Object^  sender, System::EventArgs^  e);

		// Отображение проекции
		void DrawProjection(FrameModel *model);

		// Загрузка модели из файла
		FrameModel* LoadFile();

		// Считывание текстовых полей трансформации
		int GetUserVals(Vertex3D *rot, double *scale);

		void DrawEdge(Image2D *img, Edge *edge);
};

}

