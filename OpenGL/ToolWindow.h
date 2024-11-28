#include "StandardIncludes.h";

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
		static float SpecularStrengthValue;
		static float SpecularColorRValue;
		static float SpecularColorGValue;
		static float SpecularColorBValue;
		property bool ResetButtonClicked; 
		bool ResetLightButtonClicked = false;
		ToolWindow(void)
		{
			InitializeComponent();
			SpecularStrengthValue = trackBarSpecularStrength->Value;
			SpecularColorRValue = trackBarSpecularColorR->Value / 100.0f;
			SpecularColorGValue = trackBarSpecularColorG->Value / 100.0f;
			SpecularColorBValue = trackBarSpecularColorB->Value / 100.0f;
		}


		System::Windows::Forms::RadioButton^ radioButtonMoveLight;
		System::Windows::Forms::RadioButton^ radioButtonColorByPosition;
		System::Windows::Forms::RadioButton^ radioButtonMoveCubes;
		System::Windows::Forms::Button^ buttonResetLightPosition;
		System::Windows::Forms::Button^ buttonResetSuzannePosition;
		System::Windows::Forms::TrackBar^ trackBarSpecularStrength;
		System::Windows::Forms::TrackBar^ trackBarSpecularColorR;
		System::Windows::Forms::TrackBar^ trackBarSpecularColorG;
		System::Windows::Forms::TrackBar^ trackBarSpecularColorB;
		System::Windows::Forms::Label^ labelSpecularStrength;
		System::Windows::Forms::Label^ labelSpecularColorR;
		System::Windows::Forms::Label^ labelSpecularColorG;
		System::Windows::Forms::Label^ labelSpecularColorB;
		System::Windows::Forms::Label^ valueSpecularStrength;
		System::Windows::Forms::Label^ valueSpecularColorR;
		System::Windows::Forms::Label^ valueSpecularColorG;
		System::Windows::Forms::Label^ valueSpecularColorB;

	protected:
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		


		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->radioButtonMoveLight = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonColorByPosition = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonMoveCubes = (gcnew System::Windows::Forms::RadioButton());
			this->buttonResetLightPosition = (gcnew System::Windows::Forms::Button());
			this->buttonResetSuzannePosition = (gcnew System::Windows::Forms::Button());
			this->trackBarSpecularStrength = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSpecularColorR = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSpecularColorG = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSpecularColorB = (gcnew System::Windows::Forms::TrackBar());
			this->labelSpecularStrength = (gcnew System::Windows::Forms::Label());
			this->labelSpecularColorR = (gcnew System::Windows::Forms::Label());
			this->labelSpecularColorG = (gcnew System::Windows::Forms::Label());
			this->labelSpecularColorB = (gcnew System::Windows::Forms::Label());
			this->valueSpecularStrength = (gcnew System::Windows::Forms::Label());
			this->valueSpecularColorR = (gcnew System::Windows::Forms::Label());
			this->valueSpecularColorG = (gcnew System::Windows::Forms::Label());
			this->valueSpecularColorB = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorG))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorB))->BeginInit();
			this->SuspendLayout();
			// 
			// radioButtonMoveLight
			// 
			this->radioButtonMoveLight->AutoSize = true;
			this->radioButtonMoveLight->Checked = true;
			this->radioButtonMoveLight->Location = System::Drawing::Point(10, 10);
			this->radioButtonMoveLight->Name = L"radioButtonMoveLight";
			this->radioButtonMoveLight->Size = System::Drawing::Size(93, 20);
			this->radioButtonMoveLight->TabIndex = 0;
			this->radioButtonMoveLight->TabStop = true;
			this->radioButtonMoveLight->Text = L"Move Light";
			// 
			// radioButtonColorByPosition
			// 
			this->radioButtonColorByPosition->AutoSize = true;
			this->radioButtonColorByPosition->Location = System::Drawing::Point(10, 414);
			this->radioButtonColorByPosition->Name = L"radioButtonColorByPosition";
			this->radioButtonColorByPosition->Size = System::Drawing::Size(130, 20);
			this->radioButtonColorByPosition->TabIndex = 14;
			this->radioButtonColorByPosition->Text = L"Color By Position";
			// 
			// radioButtonMoveCubes
			// 
			this->radioButtonMoveCubes->AutoSize = true;
			this->radioButtonMoveCubes->Location = System::Drawing::Point(15, 487);
			this->radioButtonMoveCubes->Name = L"radioButtonMoveCubes";
			this->radioButtonMoveCubes->Size = System::Drawing::Size(171, 20);
			this->radioButtonMoveCubes->TabIndex = 16;
			this->radioButtonMoveCubes->Text = L"Move Cubes To Sphere";
			// 
			// buttonResetLightPosition
			// 
			this->buttonResetLightPosition->Location = System::Drawing::Point(28, 36);
			this->buttonResetLightPosition->Name = L"buttonResetLightPosition";
			this->buttonResetLightPosition->Size = System::Drawing::Size(184, 23);
			this->buttonResetLightPosition->TabIndex = 1;
			this->buttonResetLightPosition->Text = L"Reset Light Position";
			this->buttonResetLightPosition->Click += gcnew System::EventHandler(this, &ToolWindow::buttonResetLightPosition_Click);
			// 
			// buttonResetSuzannePosition
			// 
			this->buttonResetSuzannePosition->Location = System::Drawing::Point(41, 440);
			this->buttonResetSuzannePosition->Name = L"buttonResetSuzannePosition";
			this->buttonResetSuzannePosition->Size = System::Drawing::Size(184, 23);
			this->buttonResetSuzannePosition->TabIndex = 15;
			this->buttonResetSuzannePosition->Text = L"Reset Suzanne Position";
			this->ResetButtonClicked = false;
			this->buttonResetSuzannePosition->Click += gcnew System::EventHandler(this, &ToolWindow::OnResetButtonClick);

			// 
			// trackBarSpecularStrength
			// 
			this->trackBarSpecularStrength->Location = System::Drawing::Point(150, 84);
			this->trackBarSpecularStrength->Maximum = 128;
			this->trackBarSpecularStrength->Minimum = 1;
			this->trackBarSpecularStrength->Name = L"trackBarSpecularStrength";
			this->trackBarSpecularStrength->Size = System::Drawing::Size(300, 56);
			this->trackBarSpecularStrength->TabIndex = 3;
			this->trackBarSpecularStrength->Value = 4;
			this->trackBarSpecularStrength->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::OnSpecularStrengthChanged);
			// 
			// trackBarSpecularColorR
			// 
			this->trackBarSpecularColorR->Location = System::Drawing::Point(150, 150);
			this->trackBarSpecularColorR->Maximum = 300;
			this->trackBarSpecularColorR->Name = L"trackBarSpecularColorR";
			this->trackBarSpecularColorR->Size = System::Drawing::Size(300, 56);
			this->trackBarSpecularColorR->TabIndex = 6;
			this->trackBarSpecularColorR->Value = 100;
			this->trackBarSpecularColorR->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::OnSpecularColorRChanged);
			// 
			// trackBarSpecularColorG
			// 
			this->trackBarSpecularColorG->Location = System::Drawing::Point(150, 220);
			this->trackBarSpecularColorG->Maximum = 300;
			this->trackBarSpecularColorG->Name = L"trackBarSpecularColorG";
			this->trackBarSpecularColorG->Size = System::Drawing::Size(300, 56);
			this->trackBarSpecularColorG->TabIndex = 9;
			this->trackBarSpecularColorG->Value = 100;
			this->trackBarSpecularColorG->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::OnSpecularColorGChanged);
			// 
			// trackBarSpecularColorB
			// 
			this->trackBarSpecularColorB->Location = System::Drawing::Point(150, 290);
			this->trackBarSpecularColorB->Maximum = 300;
			this->trackBarSpecularColorB->Name = L"trackBarSpecularColorB";
			this->trackBarSpecularColorB->Size = System::Drawing::Size(300, 56);
			this->trackBarSpecularColorB->TabIndex = 12;
			this->trackBarSpecularColorB->Value = 100;
			this->trackBarSpecularColorB->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::OnSpecularColorBChanged);
			// 
			// labelSpecularStrength
			// 
			this->labelSpecularStrength->Location = System::Drawing::Point(12, 84);
			this->labelSpecularStrength->Name = L"labelSpecularStrength";
			this->labelSpecularStrength->Size = System::Drawing::Size(128, 23);
			this->labelSpecularStrength->TabIndex = 2;
			this->labelSpecularStrength->Text = L"Specular Strength";
			// 
			// labelSpecularColorR
			// 
			this->labelSpecularColorR->Location = System::Drawing::Point(12, 150);
			this->labelSpecularColorR->Name = L"labelSpecularColorR";
			this->labelSpecularColorR->Size = System::Drawing::Size(128, 23);
			this->labelSpecularColorR->TabIndex = 5;
			this->labelSpecularColorR->Text = L"Specular Color R";
			// 
			// labelSpecularColorG
			// 
			this->labelSpecularColorG->Location = System::Drawing::Point(12, 220);
			this->labelSpecularColorG->Name = L"labelSpecularColorG";
			this->labelSpecularColorG->Size = System::Drawing::Size(128, 23);
			this->labelSpecularColorG->TabIndex = 8;
			this->labelSpecularColorG->Text = L"Specular Color G";
			// 
			// labelSpecularColorB
			// 
			this->labelSpecularColorB->Location = System::Drawing::Point(12, 290);
			this->labelSpecularColorB->Name = L"labelSpecularColorB";
			this->labelSpecularColorB->Size = System::Drawing::Size(128, 23);
			this->labelSpecularColorB->TabIndex = 11;
			this->labelSpecularColorB->Text = L"Specular Color B";
			// 
			// valueSpecularStrength
			// 
			this->valueSpecularStrength->Location = System::Drawing::Point(471, 86);
			this->valueSpecularStrength->Name = L"valueSpecularStrength";
			this->valueSpecularStrength->Size = System::Drawing::Size(100, 23);
			this->valueSpecularStrength->TabIndex = 4;
			this->valueSpecularStrength->Text = L"4";
			// 
			// valueSpecularColorR
			// 
			this->valueSpecularColorR->Location = System::Drawing::Point(471, 150);
			this->valueSpecularColorR->Name = L"valueSpecularColorR";
			this->valueSpecularColorR->Size = System::Drawing::Size(100, 23);
			this->valueSpecularColorR->TabIndex = 7;
			this->valueSpecularColorR->Text = L"1.00";
			// 
			// valueSpecularColorG
			// 
			this->valueSpecularColorG->Location = System::Drawing::Point(471, 220);
			this->valueSpecularColorG->Name = L"valueSpecularColorG";
			this->valueSpecularColorG->Size = System::Drawing::Size(100, 23);
			this->valueSpecularColorG->TabIndex = 10;
			this->valueSpecularColorG->Text = L"1.00";
			// 
			// valueSpecularColorB
			// 
			this->valueSpecularColorB->Location = System::Drawing::Point(471, 290);
			this->valueSpecularColorB->Name = L"valueSpecularColorB";
			this->valueSpecularColorB->Size = System::Drawing::Size(100, 23);
			this->valueSpecularColorB->TabIndex = 13;
			this->valueSpecularColorB->Text = L"1.00";
			// 
			// ToolWindow
			// 
			this->ClientSize = System::Drawing::Size(600, 600);
			this->Controls->Add(this->radioButtonMoveLight);
			this->Controls->Add(this->buttonResetLightPosition);
			this->Controls->Add(this->labelSpecularStrength);
			this->Controls->Add(this->trackBarSpecularStrength);
			this->Controls->Add(this->valueSpecularStrength);
			this->Controls->Add(this->labelSpecularColorR);
			this->Controls->Add(this->trackBarSpecularColorR);
			this->Controls->Add(this->valueSpecularColorR);
			this->Controls->Add(this->labelSpecularColorG);
			this->Controls->Add(this->trackBarSpecularColorG);
			this->Controls->Add(this->valueSpecularColorG);
			this->Controls->Add(this->labelSpecularColorB);
			this->Controls->Add(this->trackBarSpecularColorB);
			this->Controls->Add(this->valueSpecularColorB);
			this->Controls->Add(this->radioButtonColorByPosition);
			this->Controls->Add(this->buttonResetSuzannePosition);
			this->Controls->Add(this->radioButtonMoveCubes);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularStrength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorG))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorB))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
		private:
			void OnSpecularStrengthChanged(System::Object^ sender, System::EventArgs^ e)
			{
				SpecularStrengthValue = static_cast<float>(trackBarSpecularStrength->Value);
				valueSpecularStrength->Text = trackBarSpecularStrength->Value.ToString();
				std::cout << "Specular Strength Changed: " << SpecularStrengthValue << std::endl;
			}

			void OnSpecularColorRChanged(System::Object^ sender, System::EventArgs^ e)
			{
				SpecularColorRValue = static_cast<float>(trackBarSpecularColorR->Value) / 100.0f;
				valueSpecularColorR->Text = (trackBarSpecularColorR->Value / 100.0f).ToString("F2");
				std::cout << "Specular Color R Changed: " << SpecularColorRValue << std::endl;
			}


			void OnSpecularColorGChanged(System::Object^ sender, System::EventArgs^ e)
			{
				SpecularColorGValue = static_cast<float>(trackBarSpecularColorG->Value) / 100.0f;
				valueSpecularColorG->Text = (trackBarSpecularColorG->Value / 100.0f).ToString("F2");
			}

			void OnSpecularColorBChanged(System::Object^ sender, System::EventArgs^ e)
			{
				SpecularColorBValue = static_cast<float>(trackBarSpecularColorB->Value) / 100.0f;
				valueSpecularColorB->Text = (trackBarSpecularColorB->Value / 100.0f).ToString("F2");
			}


			void OnResetButtonClick(System::Object^ sender, System::EventArgs^ e)
			{
				this->ResetButtonClicked = true; // Set the flag when the button is clicked
			}

			void buttonResetLightPosition_Click(System::Object^ sender, System::EventArgs^ e)
			{
				ResetLightButtonClicked = true; // Set the flag to true
			}



};
}
