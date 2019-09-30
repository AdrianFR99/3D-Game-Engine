#include "WindowUI_Settings.h"
#include "Application.h"


WindowUI_Settings::WindowUI_Settings(char*title):WindowUI(title)
{


}

WindowUI_Settings::~WindowUI_Settings()
{
}


void WindowUI_Settings::Config_Window() {
	
	if (ImGui::Begin("Config Menu",&active)) {

		if (ImGui::BeginMenu("Options")) {

			if (ImGui::MenuItem("Set Default")) {


			}

			if (ImGui::MenuItem("Save")) {

			}

			if (ImGui::MenuItem("Load")) {

			}

			ImGui::EndMenu();


			

		}

	}


	Config_Window_App();
	Config_Window_Window();
	Config_Window_FileSystem();
	Config_Window_Input();
	Config_Window_Hardware();


	ImGui::End();


}
void WindowUI_Settings::Config_Window_App() {

	if (ImGui::CollapsingHeader("Application"))
	{
	
		
		static char app_name[120];
		strcpy_s(app_name, 120, App->Get_App_Name());
		if (ImGui::InputText("App Name", app_name, 120, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll));
		App->window->SetTitle(app_name);

		
	}


}

void WindowUI_Settings::Config_Window_Window() {

	if (ImGui::CollapsingHeader("Window"))
	{



	}



}
void WindowUI_Settings::Config_Window_FileSystem() {

	if (ImGui::CollapsingHeader("File system"))
	{



	}



}

void WindowUI_Settings::Config_Window_Input() {

	if (ImGui::CollapsingHeader("Input"))
	{



	}



}
void WindowUI_Settings::Config_Window_Hardware() {

	if (ImGui::CollapsingHeader("Hardware"))
	{



	}



}
void WindowUI_Settings::FPS_vec_Alloc(float FPS, float ms) {

	int counter;
	int MaxVecSize = 100;
	++counter;

	if (counter == MaxVecSize) {

		for (uint i = 0; i < MaxVecSize - 1; ++i) {

			FPS_Tracker[i] = FPS_Tracker[i + 1];
			MS_Tracker[i] = MS_Tracker[i + 1];

		}

	}
	else
		++counter;

	FPS_Tracker[counter - 1] = FPS;
	MS_Tracker[counter - 1] = ms;
}