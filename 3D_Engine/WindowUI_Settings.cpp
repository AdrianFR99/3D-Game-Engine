#include "WindowUI_Settings.h"
#include "Application.h"

#include "mmgr/mmgr.h"

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
		//App Name	
		static char app_name[120];
		strcpy_s(app_name,120,App->GetAppName());
		if (ImGui::InputText("App Name","Engine", 120, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll));
		App->window->SetTitle(app_name);
	
		//FrameRate
		int Framerate = App->GetMaxFrameRate();
		if (ImGui::SliderInt("Max FPS", &Framerate, 0, App->window->GetDisplayRefRate()))
		App->SetMaxFrameRate(Framerate);

		ImGui::Spacing();

		ImGui::Text("Limit framerate:");
		ImGui::SameLine();
		ImGui::TextColored(YELLOW,"%i",App->GetMaxFrameRate());
		
		char title_Fplot[25];
		sprintf_s(title_Fplot,25,"Framerate %.1f",FPS_LOG[FPS_LOG.size()-1]);
		ImGui::PlotHistogram("##framerate",&FPS_LOG[0],FPS_LOG.size(),0, title_Fplot,0.0f,100.0f,ImVec2(310,100));

		ImGui::Spacing();

		char title_MSplot[25];
		sprintf_s(title_MSplot, 25, "Milliseconds %0.1f", MS_LOG[MS_LOG.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &MS_LOG[0], MS_LOG.size(), 0, title_MSplot, 0.0f, 100.0f, ImVec2(310, 100));

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Separator();


		//Memory

		ImGui::Text("Memory Stats");

		sMStats MemStats = m_getMemoryStatistics(); 
		static int ToUpdate = 0;	//var which it is used as an interval of time to 
		static std::vector<float>memory(LOG_MEM_SIZE_PLOT); //Creating a vector to allocate the memory data as we did with the FPS and ms
	

		
		if (ToUpdate > TO_MOVE_VEC_DATA) {

			if (memory.size() == LOG_MEM_SIZE_PLOT) {

				for (uint i = 0; i < LOG_MEM_SIZE_PLOT - 1; ++i)
					memory[i] = memory[i + 1];

				memory[LOG_MEM_SIZE_PLOT - 1] = (float)MemStats.totalReportedMemory;
			}
			else
				memory.push_back((float)MemStats.totalReportedMemory);
			
			ToUpdate = 0;

		}

		ImGui::PlotHistogram("##Memory", &memory[0], memory.size(), 0, "Memory Consumption", 0.0f, (float)MemStats.peakReportedMemory*1.75f, ImVec2(310, 100));
		
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::Text("Total Reported Memory: %u", MemStats.totalReportedMemory);
		ImGui::Text("Total Actual Memory: %u", MemStats.totalActualMemory);
		ImGui::Text("Peak Reported Memory: %u", MemStats.peakReportedMemory);
		ImGui::Text("Peak Actual Memory: %u", MemStats.peakActualMemory);
		ImGui::Text("Accumulated Reported Memory: %u", MemStats.accumulatedReportedMemory);
		ImGui::Text("Accumulated Actual Memory: %u", MemStats.accumulatedActualMemory);
		ImGui::Text("Accumulated Alloc Unit Count: %u", MemStats.accumulatedAllocUnitCount);
		ImGui::Text("Total Alloc Unit Count: %u", MemStats.totalAllocUnitCount);
		ImGui::Text("Peak Alloc Unit Count: %u", MemStats.peakAllocUnitCount);

		

		++ToUpdate;

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