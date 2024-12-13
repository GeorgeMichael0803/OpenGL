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
	public: System::Windows::Forms::CheckBox^ Translate;
	public:

	public:
	public: System::Windows::Forms::CheckBox^ Rotate;
	public: System::Windows::Forms::CheckBox^ Scale;
	public: System::Windows::Forms::RadioButton^ WaterScene;
	public: System::Windows::Forms::TrackBar^ trackBar1;
	public: System::Windows::Forms::TrackBar^ trackBar2;
	public: System::Windows::Forms::Label^ label1;
	public:
	public: System::Windows::Forms::Label^ label2;
	public: System::Windows::Forms::Label^ label3;
	public: System::Windows::Forms::Label^ label4;
	public: System::Windows::Forms::CheckBox^ checkBox1;
	public: System::Windows::Forms::CheckBox^ checkBox2;
	public:

		   //property bool ResetButtonClicked;
		bool ResetLightButtonClicked = false;
		bool ResetButtonClicked = false;
		ToolWindow(void)
		{
			InitializeComponent();
			SpecularStrengthValue = trackBarSpecularStrength->Value / 32.0f;
			SpecularColorRValue = trackBarSpecularColorR->Value / 100.0f;
			SpecularColorGValue = trackBarSpecularColorG->Value / 100.0f;
			SpecularColorBValue = trackBarSpecularColorB->Value / 100.0f;

			// Update the label texts with the initialized values
			valueSpecularStrength->Text = trackBarSpecularStrength->Value.ToString("0");
			valueSpecularColorR->Text = (trackBarSpecularColorR->Value / 100.0f).ToString("0.00");
			valueSpecularColorG->Text = (trackBarSpecularColorG->Value / 100.0f).ToString("0.00");
			valueSpecularColorB->Text = (trackBarSpecularColorB->Value / 100.0f).ToString("0.00");
			label1->Text = (trackBar1->Value ).ToString("0.00"); // Frequency
			label2->Text = (trackBar2->Value / 128).ToString("0.00"); // Amplitude
		}


		System::Windows::Forms::RadioButton^ radioButtonMoveLight;
	public: System::Windows::Forms::RadioButton^ radioButtonTransform;

	public: System::Windows::Forms::RadioButton^ SpaceScene;

		System::Windows::Forms::Button^ buttonResetLightPosition;
	public: System::Windows::Forms::Button^ ResetTransform;

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
			this->radioButtonTransform = (gcnew System::Windows::Forms::RadioButton());
			this->SpaceScene = (gcnew System::Windows::Forms::RadioButton());
			this->buttonResetLightPosition = (gcnew System::Windows::Forms::Button());
			this->ResetTransform = (gcnew System::Windows::Forms::Button());
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
			this->Translate = (gcnew System::Windows::Forms::CheckBox());
			this->Rotate = (gcnew System::Windows::Forms::CheckBox());
			this->Scale = (gcnew System::Windows::Forms::CheckBox());
			this->WaterScene = (gcnew System::Windows::Forms::RadioButton());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorG))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			this->SuspendLayout();
			// 
			// radioButtonMoveLight
			// 
			this->radioButtonMoveLight->AutoSize = true;
			this->radioButtonMoveLight->Checked = true;
			this->radioButtonMoveLight->Location = System::Drawing::Point(10, 10);
			this->radioButtonMoveLight->Name = L"radioButtonMoveLight";
			this->radioButtonMoveLight->Size = System::Drawing::Size(78, 17);
			this->radioButtonMoveLight->TabIndex = 0;
			this->radioButtonMoveLight->TabStop = true;
			this->radioButtonMoveLight->Text = L"Move Light";
			// 
			// radioButtonTransform
			// 
			this->radioButtonTransform->AutoSize = true;
			this->radioButtonTransform->Location = System::Drawing::Point(15, 359);
			this->radioButtonTransform->Name = L"radioButtonTransform";
			this->radioButtonTransform->Size = System::Drawing::Size(72, 17);
			this->radioButtonTransform->TabIndex = 14;
			this->radioButtonTransform->Text = L"Transform";
			// 
			// SpaceScene
			// 
			this->SpaceScene->AutoSize = true;
			this->SpaceScene->Location = System::Drawing::Point(15, 680);
			this->SpaceScene->Name = L"SpaceScene";
			this->SpaceScene->Size = System::Drawing::Size(90, 17);
			this->SpaceScene->TabIndex = 16;
			this->SpaceScene->Text = L"Space Scene";
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
			// ResetTransform
			// 
			this->ResetTransform->Location = System::Drawing::Point(41, 382);
			this->ResetTransform->Name = L"ResetTransform";
			this->ResetTransform->Size = System::Drawing::Size(112, 23);
			this->ResetTransform->TabIndex = 15;
			this->ResetTransform->Text = L"Reset Transfrom";
			this->ResetTransform->Click += gcnew System::EventHandler(this, &ToolWindow::OnResetButtonClick);
			// 
			// trackBarSpecularStrength
			// 
			this->trackBarSpecularStrength->Location = System::Drawing::Point(150, 84);
			this->trackBarSpecularStrength->Maximum = 128;
			this->trackBarSpecularStrength->Minimum = 0;
			this->trackBarSpecularStrength->Name = L"trackBarSpecularStrength";
			this->trackBarSpecularStrength->Size = System::Drawing::Size(300, 45);
			this->trackBarSpecularStrength->TabIndex = 3;
			this->trackBarSpecularStrength->Value = 1;
			this->trackBarSpecularStrength->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::OnSpecularStrengthChanged);
			// 
			// trackBarSpecularColorR
			// 
			this->trackBarSpecularColorR->Location = System::Drawing::Point(150, 150);
			this->trackBarSpecularColorR->Maximum = 300;
			this->trackBarSpecularColorR->Name = L"trackBarSpecularColorR";
			this->trackBarSpecularColorR->Size = System::Drawing::Size(300, 45);
			this->trackBarSpecularColorR->TabIndex = 6;
			this->trackBarSpecularColorR->Value = 100;
			this->trackBarSpecularColorR->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::OnSpecularColorRChanged);
			// 
			// trackBarSpecularColorG
			// 
			this->trackBarSpecularColorG->Location = System::Drawing::Point(150, 220);
			this->trackBarSpecularColorG->Maximum = 300;
			this->trackBarSpecularColorG->Name = L"trackBarSpecularColorG";
			this->trackBarSpecularColorG->Size = System::Drawing::Size(300, 45);
			this->trackBarSpecularColorG->TabIndex = 9;
			this->trackBarSpecularColorG->Value = 100;
			this->trackBarSpecularColorG->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::OnSpecularColorGChanged);
			// 
			// trackBarSpecularColorB
			// 
			this->trackBarSpecularColorB->Location = System::Drawing::Point(150, 290);
			this->trackBarSpecularColorB->Maximum = 300;
			this->trackBarSpecularColorB->Name = L"trackBarSpecularColorB";
			this->trackBarSpecularColorB->Size = System::Drawing::Size(300, 45);
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
			// Translate
			// 
			this->Translate->AutoSize = true;
			this->Translate->Location = System::Drawing::Point(41, 412);
			this->Translate->Name = L"Translate";
			this->Translate->Size = System::Drawing::Size(70, 17);
			this->Translate->TabIndex = 17;
			this->Translate->Text = L"Translate";
			this->Translate->UseVisualStyleBackColor = true;
			// 
			// Rotate
			// 
			this->Rotate->AutoSize = true;
			this->Rotate->Location = System::Drawing::Point(201, 412);
			this->Rotate->Name = L"Rotate";
			this->Rotate->Size = System::Drawing::Size(58, 17);
			this->Rotate->TabIndex = 18;
			this->Rotate->Text = L"Rotate";
			this->Rotate->UseVisualStyleBackColor = true;
			// 
			// Scale
			// 
			this->Scale->AutoSize = true;
			this->Scale->Location = System::Drawing::Point(368, 412);
			this->Scale->Name = L"Scale";
			this->Scale->Size = System::Drawing::Size(53, 17);
			this->Scale->TabIndex = 19;
			this->Scale->Text = L"Scale";
			this->Scale->UseVisualStyleBackColor = true;
			// 
			// WaterScene
			// 
			this->WaterScene->AutoSize = true;
			this->WaterScene->Location = System::Drawing::Point(15, 459);
			this->WaterScene->Name = L"WaterScene";
			this->WaterScene->Size = System::Drawing::Size(88, 17);
			this->WaterScene->TabIndex = 20;
			this->WaterScene->TabStop = true;
			this->WaterScene->Text = L"Water Scene";
			this->WaterScene->UseVisualStyleBackColor = true;
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(55, 520);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(395, 45);
			this->trackBar1->TabIndex = 21;
			this->trackBar1->Minimum = 0;   // Minimum frequency
			this->trackBar1->Maximum = 4; // Maximum frequency
			this->trackBar1->Value = 0;     // Default frequency value
			this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::OnFrequencySliderChanged);


			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(55, 589);
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(404, 45);
			this->trackBar2->TabIndex = 22;
			this->trackBar2->Minimum = 0;
			this->trackBar2->Maximum = 128; // Full range 0.00–1.00
			this->trackBar2->Value = 0;     // Default to 0.00
			this->trackBar2->ValueChanged += gcnew System::EventHandler(this, &ToolWindow::OnAmplitudeSliderChanged);
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(471, 520);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(100, 23);
			this->label1->TabIndex = 23;
			this->label1->Text = L"1.00";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(471, 589);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(100, 23);
			this->label2->TabIndex = 24;
			this->label2->Text = L"1.00";
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(52, 494);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(128, 23);
			this->label3->TabIndex = 25;
			this->label3->Text = L"Frequency";
			// 
			// label4
			// 
			this->label4->Location = System::Drawing::Point(52, 563);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(128, 23);
			this->label4->TabIndex = 26;
			this->label4->Text = L"Amplitude";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(60, 640);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(112, 17);
			this->checkBox1->TabIndex = 27;
			this->checkBox1->Text = L"Wireframe Render";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(310, 640);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(68, 17);
			this->checkBox2->TabIndex = 28;
			this->checkBox2->Text = L"Tint Blue";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// ToolWindow
			// 
			this->ClientSize = System::Drawing::Size(554, 729);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->WaterScene);
			this->Controls->Add(this->Scale);
			this->Controls->Add(this->Rotate);
			this->Controls->Add(this->Translate);
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
			this->Controls->Add(this->radioButtonTransform);
			this->Controls->Add(this->ResetTransform);
			this->Controls->Add(this->SpaceScene);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularStrength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorG))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularColorB))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		// Specular Strength Slider Changed
		void OnSpecularStrengthChanged(System::Object^ sender, System::EventArgs^ e)
		{
			// Scale Specular Strength to range [0.00, 4.00]
			SpecularStrengthValue = static_cast<float>(trackBarSpecularStrength->Value) / 32.0f; // 128 -> 4.00 scaling
			valueSpecularStrength->Text = SpecularStrengthValue.ToString("0.00"); // Update label
		}


		// Specular Color R Slider Changed
		void OnSpecularColorRChanged(System::Object^ sender, System::EventArgs^ e)
		{
			SpecularColorRValue = static_cast<float>(trackBarSpecularColorR->Value) / 100.0f;
			valueSpecularColorR->Text = SpecularColorRValue.ToString("0.00"); // Update label
		}

		// Specular Color G Slider Changed
		void OnSpecularColorGChanged(System::Object^ sender, System::EventArgs^ e)
		{
			SpecularColorGValue = static_cast<float>(trackBarSpecularColorG->Value) / 100.0f;
			valueSpecularColorG->Text = SpecularColorGValue.ToString("0.00"); // Update label
		}

		// Specular Color B Slider Changed
		void OnSpecularColorBChanged(System::Object^ sender, System::EventArgs^ e)
		{
			SpecularColorBValue = static_cast<float>(trackBarSpecularColorB->Value) / 100.0f;
			valueSpecularColorB->Text = SpecularColorBValue.ToString("0.00"); // Update label
		}

		// Update the label value to map the slider's current value to 0.00 - 4.00
		void OnFrequencySliderChanged(System::Object^ sender, System::EventArgs^ e)
		{
			float scaledValue = trackBar1->Value; // Map 0-128 to 0.00-4.00
			label1->Text = scaledValue.ToString("0.00"); // Update the displayed value
			float frequencyValue = scaledValue;
		}

		void OnAmplitudeSliderChanged(System::Object^ sender, System::EventArgs^ e)
		{
			// Scale Amplitude to range [0.00, 1.00]
			float scaledValue = trackBar2->Value / 128.0f; // Map 0-128 to 0.00-1.00
			label2->Text = scaledValue.ToString("0.00"); // Update label
			float amplitudeValue = scaledValue; // Now ranges from 0.00 to 2.00
		
		}




		void OnResetButtonClick(System::Object^ sender, System::EventArgs^ e)
		{
			ResetButtonClicked = true; // Set the flag when the button is clicked
		}

		void buttonResetLightPosition_Click(System::Object^ sender, System::EventArgs^ e)
		{
			ResetLightButtonClicked = true; // Set the flag to true
		}

		


	};
}
