#include "WindowUI_Settings.h"
#include "Application.h"
#include "ModuleHardware.h"
#include "imgui_defines.h"
#include "ModuleWindow.h"

#include "mmgr/mmgr.h"


WindowUI_Settings::WindowUI_Settings(char*title): WindowUI(title), FPS_LOG(LOG_FPS_SIZE), MS_LOG(LOG_FPS_SIZE)
{


}

WindowUI_Settings::~WindowUI_Settings()
{
}

bool WindowUI_Settings::Display() {

	if (active)
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
	Config_Window_Buttons();



	ImGui::End();


}
void WindowUI_Settings::Config_Window_App() {

	if (ImGui::CollapsingHeader("Application"))
	{
		ImGui::Spacing();
		ImGui::Spacing();

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
		ImGui::TextColored(IMGUI_YELLOW,"%i",App->GetMaxFrameRate());
		
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
		static int ToUpdate = 0;	//var which it is used as an interval of time to update the data in the vector and in the graph
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
		//Brightness

		float brightlevel = App->window->GetWinBrightness();

		if (ImGui::SliderFloat("Window Brightness", &brightlevel, 0.1f, 1.0f))
			App->window->SetBrightness(brightlevel);

		//size changer

		uint width, minW=600, maxW=1300, height, minH=600, maxH= 900;

		//App->window->getExtremeSizes(minW, minH, maxW, maxH);

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

		 fullscreen = App->window->isFullscreen();
		 resizable = App->window->isResize();
		 borderless = App->window->isBorderless();
		 fullscreen_desktop = App->window->isFullscreenDesktop();

		 if (ImGui::Checkbox("Fullscreen", &fullscreen))
			 App->window->changeFullscreen(fullscreen);

		 ImGui::SameLine();

		 if (ImGui::Checkbox("Resizable", &resizable))
			 App->window->changeResize(resizable);


		 if (ImGui::Checkbox("Borderless", &borderless))
			 App->window->changeBordeless(borderless);

		 ImGui::SameLine();

		 if (ImGui::Checkbox("FullScreen Desktop", &fullscreen_desktop))
			 App->window->changeFullscreenDestop(fullscreen_desktop);
	}



}
void WindowUI_Settings::Config_Window_FileSystem() {

	if (ImGui::CollapsingHeader("File system"))
	{

		char *base_path = SDL_GetBasePath();
		


		ImGui::Text("Base File Location:");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_YELLOW, "%s", base_path);

		ImGui::Separator();

		ImGui::Text("Read Location Location:");
		//ImGui::SameLine();

		ImGui::Separator();

		ImGui::Text("Wrigth location Location:");
		//ImGui::SameLine();
		ImGui::Separator();

	}



}

void WindowUI_Settings::Config_Window_Input() {

	if (ImGui::CollapsingHeader("Input"))
	{
		ImGui::Spacing();
		ImGui::Spacing();
		// --- Get Mouse position & Mouse Motin¡on
		int mouse_x, mouse_y;
		mouse_x = App->input->GetMouseX();
		mouse_y = App->input->GetMouseY();
		
		mouse_x = App->input->GetMouseXMotion();
		mouse_y = App->input->GetMouseYMotion();


		// ---print  Mouse position

		ImGui::Text("Mouse Position:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "(%i,%i)", mouse_x, mouse_y);


		// --- print Mouse Motion ---
		
		ImGui::Text("Mouse Motion:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "(%i,%i)", mouse_x, mouse_y);

		



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

void WindowUI_Settings::Config_Window_Buttons() {

	
	
	if (ImGui::CollapsingHeader("Buttons"))
	{
		if (ImGui::TreeNode("Poly configuration"))
		{

			if (ImGui::Checkbox("Depth Test", &depth_test))
			{
				if (depth_test)
				{
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glEnable(GL_DEPTH_TEST);
				}
				else
				{
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glDisable(GL_DEPTH_TEST);
				}

			}

			ImGui::SameLine();

			if (ImGui::Checkbox("Cull Face ", &face_cull))
			{
				if (face_cull)
				{
					glEnable(GL_CULL_FACE);
					//glCullFace(GL_FRONT);
				}
				else
				{
					//glCullFace(GL_BACK);
					glDisable(GL_CULL_FACE);
				}

			}



			if (ImGui::Checkbox("Ligth", &lighting))
			{
				if (lighting)
				{

					glEnable(GL_LIGHTING);
				}
				else
				{

					glDisable(GL_LIGHTING);

				}

			}

			ImGui::SameLine();

			if (ImGui::Checkbox("Wireframe", &wireframe))
			{
				if (wireframe)
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			}


			ImGui::TreePop();
		}

	
		if (ImGui::TreeNode("Materials")){

			if (ImGui::Checkbox("Color Material", &color_material))
			{
				if (color_material)
					glEnable(GL_COLOR_MATERIAL);
				else
					glDisable(GL_COLOR_MATERIAL);

			}
			
			if (ImGui::Checkbox("Texture 2D", &texture_2d))
			{
				if (texture_2d)
					glEnable(GL_TEXTURE_2D);
				else
					glDisable(GL_TEXTURE_2D);

			}

			//if (ImGui::Checkbox("Specular", &specular))
			//{
			//	if (specular)
			//	{
			//		glEnable(GL_COLOR_MATERIAL);
			//		glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);

			//		glEnable(GL_LIGHT0);

			//		float fAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
			//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fAmbient);

			//		float fDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
			//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fDiffuse);

			//		diffuse = ambient = ambient_and_diffuse = emission = false;
			//	}
			//	else
			//	{
			//		glDisable(GL_COLOR_MATERIAL);
			//		//ambient_and_diffuse = true;
			//		//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
			//	}

			//}

			//ImGui::SameLine();

			//if (ImGui::Checkbox("Diffuse", &diffuse))
			//{
			//	if (diffuse)
			//	{
			//		glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
			//		glEnable(GL_COLOR_MATERIAL);
			//		glEnable(GL_LIGHTING);
			//		specular = ambient = ambient_and_diffuse = emission = false;
			//	}
			//	else
			//	{
			//		glDisable(GL_COLOR_MATERIAL);
			//		//ambient_and_diffuse = true;
			//		//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
			//	}

			//}

			//if (ImGui::Checkbox("Ambient", &ambient))
			//{
			//	if (ambient)
			//	{
			//		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
			//		glEnable(GL_COLOR_MATERIAL);
			//		glEnable(GL_LIGHTING);
			//		diffuse = specular = ambient_and_diffuse = emission = false;
			//	}
			//	else
			//	{
			//		glDisable(GL_COLOR_MATERIAL);
			//		//ambient_and_diffuse = true;
			//		//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
			//	}

			//}

			//ImGui::SameLine();

			//if (ImGui::Checkbox("Emission", &emission))
			//{
			//	if (emission)
			//	{
			//		glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
			//		glEnable(GL_COLOR_MATERIAL);
			//		glEnable(GL_LIGHTING);
			//		diffuse = ambient = ambient_and_diffuse = specular = false;
			//	}
			//	else
			//	{
			//		glDisable(GL_COLOR_MATERIAL);
			//		//ambient_and_diffuse = true;
			//		//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
			//	}

			//}

			//if (ImGui::Checkbox("Ambient and Diffuse", &ambient_and_diffuse))
			//{
			//	if (ambient_and_diffuse)
			//	{
			//		glEnable(GL_COLOR_MATERIAL);
			//		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
			//		glEnable(GL_LIGHT0);

			//		float fAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
			//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fAmbient);

			//		float fDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
			//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fDiffuse);

			//		diffuse = ambient = specular = emission = false;
			//	}
			//	else
			//	{
			//		glDisable(GL_COLOR_MATERIAL);
			//		//ambient = true;
			//		//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
			//	}

			//}

			//if (!diffuse && !ambient && !specular && !emission && !ambient_and_diffuse)
			//{
			//	ambient_and_diffuse = true;

			//}

			ImGui::TreePop();
		}
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