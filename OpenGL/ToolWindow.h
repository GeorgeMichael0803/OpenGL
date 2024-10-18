#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		static float YValue;
		static float UValue;
		static float VValue;
		static bool InvertColors;

		ToolWindow(void)
		{
			InitializeComponent();
			YValue = trackBarY->Value / 100.0f; 
			UValue = trackBarU->Value / 100.0f;
			VValue = trackBarV->Value / 100.0f;
			InvertColors = checkBoxInvertColors->Checked;
		}

	protected:
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::TrackBar^ trackBarY;
	private: System::Windows::Forms::TrackBar^ trackBarU;
	private: System::Windows::Forms::TrackBar^ trackBarV;
	private: System::Windows::Forms::CheckBox^ checkBoxInvertColors;
	private: System::Windows::Forms::Label^ labelY;
	private: System::Windows::Forms::Label^ labelU;
	private: System::Windows::Forms::Label^ labelV;
	private: System::Windows::Forms::Label^ labelYValue;
	private: System::Windows::Forms::Label^ labelUValue;
	private: System::Windows::Forms::Label^ labelVValue;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->trackBarY = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarU = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarV = (gcnew System::Windows::Forms::TrackBar());
			this->checkBoxInvertColors = (gcnew System::Windows::Forms::CheckBox());
			this->labelY = (gcnew System::Windows::Forms::Label());
			this->labelU = (gcnew System::Windows::Forms::Label());
			this->labelV = (gcnew System::Windows::Forms::Label());
			this->labelYValue = (gcnew System::Windows::Forms::Label());
			this->labelUValue = (gcnew System::Windows::Forms::Label());
			this->labelVValue = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarU))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarV))->BeginInit();
			this->SuspendLayout();
			// 
			// trackBarY
			// 
			this->trackBarY->Location = System::Drawing::Point(67, 25);
			this->trackBarY->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->trackBarY->Maximum = 200;
			this->trackBarY->Name = L"trackBarY";
			this->trackBarY->Size = System::Drawing::Size(267, 45);
			this->trackBarY->TabIndex = 0;
			this->trackBarY->Value = 100;
			this->trackBarY->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarY_Scroll);
			// 
			// trackBarU
			// 
			this->trackBarU->Location = System::Drawing::Point(67, 86);
			this->trackBarU->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->trackBarU->Maximum = 200;
			this->trackBarU->Name = L"trackBarU";
			this->trackBarU->Size = System::Drawing::Size(267, 45);
			this->trackBarU->TabIndex = 1;
			this->trackBarU->Value = 100;
			this->trackBarU->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarU_Scroll);
			// 
			// trackBarV
			// 
			this->trackBarV->Location = System::Drawing::Point(67, 148);
			this->trackBarV->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->trackBarV->Maximum = 200;
			this->trackBarV->Name = L"trackBarV";
			this->trackBarV->Size = System::Drawing::Size(267, 45);
			this->trackBarV->TabIndex = 2;
			this->trackBarV->Value = 100;
			this->trackBarV->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarV_Scroll);
			// 
			// checkBoxInvertColors
			// 
			this->checkBoxInvertColors->AutoSize = true;
			this->checkBoxInvertColors->Location = System::Drawing::Point(17, 209);
			this->checkBoxInvertColors->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBoxInvertColors->Name = L"checkBoxInvertColors";
			this->checkBoxInvertColors->Size = System::Drawing::Size(100, 20);
			this->checkBoxInvertColors->TabIndex = 3;
			this->checkBoxInvertColors->Text = L"Invert Colors";
			this->checkBoxInvertColors->UseVisualStyleBackColor = true;
			this->checkBoxInvertColors->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxInvertColors_CheckedChanged);
			// 
			// labelY
			// 
			this->labelY->Location = System::Drawing::Point(17, 25);
			this->labelY->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelY->Name = L"labelY";
			this->labelY->Size = System::Drawing::Size(133, 28);
			this->labelY->TabIndex = 4;
			this->labelY->Text = L"Y";
			// 
			// labelU
			// 
			this->labelU->Location = System::Drawing::Point(17, 86);
			this->labelU->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelU->Name = L"labelU";
			this->labelU->Size = System::Drawing::Size(133, 28);
			this->labelU->TabIndex = 5;
			this->labelU->Text = L"U";
			// 
			// labelV
			// 
			this->labelV->Location = System::Drawing::Point(17, 148);
			this->labelV->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelV->Name = L"labelV";
			this->labelV->Size = System::Drawing::Size(133, 28);
			this->labelV->TabIndex = 6;
			this->labelV->Text = L"V";
			// 
			// labelYValue
			// 
			this->labelYValue->Location = System::Drawing::Point(347, 25);
			this->labelYValue->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelYValue->Name = L"labelYValue";
			this->labelYValue->Size = System::Drawing::Size(133, 28);
			this->labelYValue->TabIndex = 7;
			this->labelYValue->Text = L"100%";
			// 
			// labelUValue
			// 
			this->labelUValue->Location = System::Drawing::Point(347, 86);
			this->labelUValue->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelUValue->Name = L"labelUValue";
			this->labelUValue->Size = System::Drawing::Size(133, 28);
			this->labelUValue->TabIndex = 8;
			this->labelUValue->Text = L"100%";
			// 
			// labelVValue
			// 
			this->labelVValue->Location = System::Drawing::Point(347, 148);
			this->labelVValue->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelVValue->Name = L"labelVValue";
			this->labelVValue->Size = System::Drawing::Size(133, 28);
			this->labelVValue->TabIndex = 9;
			this->labelVValue->Text = L"100%";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(427, 271);
			this->Controls->Add(this->checkBoxInvertColors);
			this->Controls->Add(this->trackBarY);
			this->Controls->Add(this->trackBarU);
			this->Controls->Add(this->trackBarV);
			this->Controls->Add(this->labelY);
			this->Controls->Add(this->labelU);
			this->Controls->Add(this->labelV);
			this->Controls->Add(this->labelYValue);
			this->Controls->Add(this->labelUValue);
			this->Controls->Add(this->labelVValue);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarU))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarV))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void trackBarY_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		YValue = trackBarY->Value / 100.0f;
		labelYValue->Text = trackBarY->Value.ToString() + "%"; // Update percentage label
	}
	private: System::Void trackBarU_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		UValue = trackBarU->Value / 100.0f;
		labelUValue->Text = trackBarU->Value.ToString() + "%"; 
	}
	private: System::Void trackBarV_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		VValue = trackBarV->Value / 100.0f;
		labelVValue->Text = trackBarV->Value.ToString() + "%"; 
	}
	private: System::Void checkBoxInvertColors_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		InvertColors = checkBoxInvertColors->Checked;
	}
	};
}
