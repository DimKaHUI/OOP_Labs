#pragma once

#include <stdlib.h>
#include "FrameMdlProjector.h"

namespace WinFormsTemplate {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
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

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DrawingCanvas))->BeginInit();
			this->SuspendLayout();
			// 
			// DrawingCanvas
			// 
			this->DrawingCanvas->BackColor = System::Drawing::Color::White;
			this->DrawingCanvas->Location = System::Drawing::Point(266, 12);
			this->DrawingCanvas->Name = L"DrawingCanvas";
			this->DrawingCanvas->Size = System::Drawing::Size(704, 548);
			this->DrawingCanvas->TabIndex = 0;
			this->DrawingCanvas->TabStop = false;
			// 
			// X_TextBox
			// 
			this->X_TextBox->Location = System::Drawing::Point(78, 40);
			this->X_TextBox->Name = L"X_TextBox";
			this->X_TextBox->Size = System::Drawing::Size(182, 26);
			this->X_TextBox->TabIndex = 1;
			this->X_TextBox->Text = L"0";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 43);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(65, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Euler X:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 75);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(65, 20);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Euler Y:";
			// 
			// Y_TextBox
			// 
			this->Y_TextBox->Location = System::Drawing::Point(78, 72);
			this->Y_TextBox->Name = L"Y_TextBox";
			this->Y_TextBox->Size = System::Drawing::Size(182, 26);
			this->Y_TextBox->TabIndex = 3;
			this->Y_TextBox->Text = L"0";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 107);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(64, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Euler Z:";
			// 
			// Z_TextBox
			// 
			this->Z_TextBox->Location = System::Drawing::Point(78, 104);
			this->Z_TextBox->Name = L"Z_TextBox";
			this->Z_TextBox->Size = System::Drawing::Size(182, 26);
			this->Z_TextBox->TabIndex = 5;
			this->Z_TextBox->Text = L"0";
			// 
			// ProcessButton
			// 
			this->ProcessButton->Location = System::Drawing::Point(12, 144);
			this->ProcessButton->Name = L"ProcessButton";
			this->ProcessButton->Size = System::Drawing::Size(248, 41);
			this->ProcessButton->TabIndex = 7;
			this->ProcessButton->Text = L"Apply";
			this->ProcessButton->UseVisualStyleBackColor = true;
			this->ProcessButton->Click += gcnew System::EventHandler(this, &MainForm::ProcessButton_Click);
			// 
			// LoadButton
			// 
			this->LoadButton->Location = System::Drawing::Point(11, 519);
			this->LoadButton->Name = L"LoadButton";
			this->LoadButton->Size = System::Drawing::Size(248, 41);
			this->LoadButton->TabIndex = 8;
			this->LoadButton->Text = L"Load frame";
			this->LoadButton->UseVisualStyleBackColor = true;
			this->LoadButton->Click += gcnew System::EventHandler(this, &MainForm::LoadButton_Click);
			// 
			// PathBox
			// 
			this->PathBox->Location = System::Drawing::Point(13, 487);
			this->PathBox->Name = L"PathBox";
			this->PathBox->Size = System::Drawing::Size(246, 26);
			this->PathBox->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 464);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(124, 20);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Model file name:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(136, 17);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(70, 20);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Degrees";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(982, 572);
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
			this->Name = L"MainForm";
			this->Text = L"FrameViewer";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DrawingCanvas))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private:
		System::Void ProcessButton_Click(System::Object^  sender, System::EventArgs^  e);
	private:
		System::Void LoadButton_Click(System::Object^  sender, System::EventArgs^  e);
		void DrawProjection();
	};

}

