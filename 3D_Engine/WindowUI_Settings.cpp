#include "WindowUI_Settings.h"
#include "Application.h"



WindowUI_Settings::WindowUI_Settings(char*title): WindowUI(title), FPS_LOG(LOG_FPS_SIZE), MS_LOG(LOG_FPS_SIZE)
{


}

WindowUI_Settings::~WindowUI_Settings()
{
}

bool WindowUI_Settings::Display() {


	Config_Window();



	return true;
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
		strcpy_s(app_name,120,App->GetAppName());
		if (ImGui::InputText("App Name","Engine", 120, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll));
		App->window->SetTitle(app_name);
	

		int Framerate = App->GetMaxFrameRate();
		if (ImGui::SliderInt("Max FPS", &Framerate, 0, App->window->GetDisplayRefRate()))
		App->SetMaxFrameRate(Framerate);


		ImGui::Text("Limit framerate:");
		ImGui::SameLine();
		ImGui::TextColored(YELLOW,"%i",App->GetMaxFrameRate());
		
		char title_Fplot[25];
		sprintf_s(title_Fplot,25,"Framerate %.1f",FPS_LOG[FPS_LOG.size()-1]);
		ImGui::PlotHistogram("##framerate",&FPS_LOG[0],FPS_LOG.size(),0, title_Fplot,0.0f,100.0f,ImVec2(310,100));

		char title_MSplot[25];
		sprintf_s(title_MSplot, 25, "Milliseconds %0.1f", MS_LOG[MS_LOG.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &MS_LOG[0], MS_LOG.size(), 0, title_MSplot, 0.0f, 100.0f, ImVec2(310, 100));

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

	static uint counter=0;

	if (counter == LOG_FPS_SIZE) {

		for (uint i = 0; i < LOG_FPS_SIZE - 1; ++i) {

			FPS_LOG[i] = FPS_LOG[i + 1];
			MS_LOG[i] = MS_LOG[i + 1];

		}

	}
	else
		++counter;

	FPS_LOG[counter - 1] = FPS;
	MS_LOG[counter - 1] = ms;
}