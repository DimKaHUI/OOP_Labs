#pragma once

#include "WinFormVisualizer.h"
#include "BoilerCharacteristics.h"
#include "Boiler.h"

namespace BoilerImitator
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  SwitchButton;
	protected:
	private: System::Windows::Forms::Button^  CoverButton;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  TempLabel;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Panel^  LedPanel;
	private: System::Windows::Forms::Label^  CoverLabel;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  CoverLockLabel;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Timer^  timer1;

	protected:
	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->SwitchButton = (gcnew System::Windows::Forms::Button());
			this->CoverButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->TempLabel = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->LedPanel = (gcnew System::Windows::Forms::Panel());
			this->CoverLabel = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->CoverLockLabel = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// SwitchButton
			// 
			this->SwitchButton->Location = System::Drawing::Point(12, 228);
			this->SwitchButton->Name = L"SwitchButton";
			this->SwitchButton->Size = System::Drawing::Size(250, 23);
			this->SwitchButton->TabIndex = 0;
			this->SwitchButton->Text = L"Switch";
			this->SwitchButton->UseVisualStyleBackColor = true;
			// 
			// CoverButton
			// 
			this->CoverButton->Location = System::Drawing::Point(12, 257);
			this->CoverButton->Name = L"CoverButton";
			this->CoverButton->Size = System::Drawing::Size(250, 23);
			this->CoverButton->TabIndex = 1;
			this->CoverButton->Text = L"Cover open/close";
			this->CoverButton->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(101, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Water temperature: ";
			// 
			// TempLabel
			// 
			this->TempLabel->AutoSize = true;
			this->TempLabel->Location = System::Drawing::Point(119, 9);
			this->TempLabel->Name = L"TempLabel";
			this->TempLabel->Size = System::Drawing::Size(0, 13);
			this->TempLabel->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(77, 46);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(34, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"LED: ";
			// 
			// LedPanel
			// 
			this->LedPanel->BackColor = System::Drawing::Color::Black;
			this->LedPanel->Location = System::Drawing::Point(109, 34);
			this->LedPanel->Name = L"LedPanel";
			this->LedPanel->Size = System::Drawing::Size(43, 35);
			this->LedPanel->TabIndex = 5;
			// 
			// CoverLabel
			// 
			this->CoverLabel->AutoSize = true;
			this->CoverLabel->Location = System::Drawing::Point(119, 83);
			this->CoverLabel->Name = L"CoverLabel";
			this->CoverLabel->Size = System::Drawing::Size(0, 13);
			this->CoverLabel->TabIndex = 7;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(72, 83);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(41, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Cover: ";
			// 
			// CoverLockLabel
			// 
			this->CoverLockLabel->AutoSize = true;
			this->CoverLockLabel->Location = System::Drawing::Point(119, 106);
			this->CoverLockLabel->Name = L"CoverLockLabel";
			this->CoverLockLabel->Size = System::Drawing::Size(0, 13);
			this->CoverLockLabel->TabIndex = 9;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(37, 106);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(76, 13);
			this->label5->TabIndex = 8;
			this->label5->Text = L"Cover locked: ";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(274, 290);
			this->Controls->Add(this->CoverLockLabel);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->CoverLabel);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->LedPanel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->TempLabel);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->CoverButton);
			this->Controls->Add(this->SwitchButton);
			this->Name = L"Form1";
			this->Text = L"Boiler";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e)
	{
		WinFormVisualizer^ vis = gcnew WinFormVisualizer(TempLabel, CoverLabel, CoverLockLabel, LedPanel);
		BoilerCharacteristics^ chars = gcnew BoilerCharacteristics(2.5, 0.01, 25.0);
		Boiler^ boiler = gcnew Boiler(vis, timer1, chars);
		SwitchButton->Click += gcnew System::EventHandler(boiler, &Boiler::SwitchClick);
		CoverButton->Click += gcnew System::EventHandler(boiler, &Boiler::CoverButtonClick);
		timer1->Start();
	}
};
}
