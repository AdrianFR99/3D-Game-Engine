#include "WindowUI_Settings.h"
#include "Application.h"
#include "ModuleHardware.h"
#include "imgui_defines.h"
#include "ModuleWindow.h"


WindowUI_Settings::WindowUI_Settings(char*title): WindowUI(title)
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
	

		//int Framerate = App->GetMaxFrameRate();
		//if (ImGui::SliderInt("Max FPS", &Framerate, 0, App->window->GetDisplayRefRate())) 
		//	App->SetMaxFrameRate(Framerate);
		





	}


}

void WindowUI_Settings::Config_Window_Window() {

	if (ImGui::CollapsingHeader("Window"))
	{
		//Brightness

		float brightlevel = App->window->GetWinBrightness();

		if (ImGui::SliderFloat("Window Brightness", &brightlevel, 0.1f, 1.0f))
			App->window->SetBrightness(brightlevel);

		//size changer

		uint width, minW, maxW, height, minH, maxH;

		App->window->getExtremeSizes(minW, minH, maxW, maxH);
		width = App->window->getWinWidth();
		height = App->window->getWinHeight();


		if (ImGui::SliderInt("Width", (int*)&width, minW, maxW))
			App->window->changeWinWidth(width);

		if (ImGui::SliderInt("Height", (int*)&height, minH, maxH))
			App->window->changeWinHeight(height);

		ImGui::Separator();

		//refresh
		ImGui::Text("Refresh Rate:");
		ImGui::SameLine();

		if (App->window->getRefreshrate() < 31)
		{
			ImGui::TextColored(IMGUI_RED, "%u", App->window->getRefreshrate());
		}
		else if ((App->window->getRefreshrate() < 61))
		{
			ImGui::TextColored(IMGUI_YELLOW, "%u", App->window->getRefreshrate());
		}
		else if (App->window->getRefreshrate() > 61)
		{
			ImGui::TextColored(IMGUI_GREEN, "%u", App->window->getRefreshrate());
		}
		else
			ImGui::TextColored(IMGUI_YELLOW, "%u", App->window->getRefreshrate());
		
		//window options

	

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

	hw_info hardware_specs = App->hardware->GetInfo();

	if (ImGui::CollapsingHeader("Hardware"))
	{

		//SDL
		ImGui::Text("SDL Version:");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_YELLOW, "%i", hardware_specs.sdl_version);
		ImGui::Separator();

		// CPUS
		ImGui::Text("CPUs:");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_GREEN, "%i%s%i", hardware_specs.cpu_count," Cache: ", hardware_specs.l1_cachekb);

		ImGui::Text("Caps: ");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_GREEN, "%s%s%s%s", 
			hardware_specs.rdtsc ? "RDTSC," : "",
			hardware_specs.altivec ? "AltiVec," : "",
			hardware_specs.mmx ? "MMX," : "",
			hardware_specs.now3d ? "3DNow," : "");

		ImGui::TextColored(IMGUI_GREEN, "%s%s%s%s%s%s%s", 
			hardware_specs.sse ? "SSE," : "",
			hardware_specs.sse2 ? "SSE2," : "",
			hardware_specs.sse3 ? "SSE3," : "",
			hardware_specs.sse41 ? "SSE41," : "",
			hardware_specs.sse42 ? "SSE42," : "",
			hardware_specs.avx ? "AVX," : "",
			hardware_specs.avx2 ? "AVX2" : "");

		ImGui::Separator();

		//RAM
		ImGui::Text("RAM in GBs:");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_TEAL_GREEN, "%F", hardware_specs.ram_gb);

		ImGui::Separator();

		//GPU
		ImGui::Text("GPUs Vendor:");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_BLUE, "%s", hardware_specs.gpu_vendor.data());

		ImGui::Text("GPUs Brand:");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_BLUE, "%s", hardware_specs.gpu_brand.data());

		ImGui::Text("GPUs Driver:");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_BLUE, "%s", hardware_specs.gpu_driver.data());

		ImGui::Separator();

		// VRAM 

		ImGui::Text("VRAM Usage:");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_GREY, "%f", hardware_specs.vram_mb_budget);

		ImGui::Text("VRAM Usage:");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_GREY, "%f", hardware_specs.vram_mb_usage);

		ImGui::Text("VRAM Available:");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_GREY, "%f", hardware_specs.vram_mb_available);

		ImGui::Text("VRAM Reserved:");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_GREY, "%f", hardware_specs.vram_mb_reserved);

		ImGui::Separator();

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