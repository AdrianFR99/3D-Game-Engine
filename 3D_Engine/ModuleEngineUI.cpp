#include "Application.h"
#include "ModuleEngineUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"


#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"


bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


ModuleEngineUI::ModuleEngineUI(Application* app, bool start_enabled):Module(app, start_enabled)
{
}


ModuleEngineUI::~ModuleEngineUI()
{
}

bool ModuleEngineUI::Init() {

	return true;
}

bool ModuleEngineUI::Start() {
	
	

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window,App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();

	


	return true;
}

update_status  ModuleEngineUI::PreUpdate(float dt) {

	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}
update_status ModuleEngineUI::Update(float dt) {

	static float f = 0.0f;
	static int counter = 0;

	//ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	//ImGui::Checkbox("Another Window", &show_another_window);

	//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//	counter++;
	//ImGui::SameLine();
	//ImGui::Text("counter = %d", counter);

	//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//ImGui::End();


	




	
	
	//ImGui::ShowDemoWindow();

	Menu_Bar();

	if(!Exit_Pressed)
	return UPDATE_CONTINUE;
	else
		return UPDATE_STOP;


	//return UPDATE_CONTINUE;

}
update_status  ModuleEngineUI::PostUpdate(float dt) {

	
	return UPDATE_CONTINUE;
}
bool  ModuleEngineUI::CleanUp() {
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
	
}

void  ModuleEngineUI::Draw() const {
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	

}

void ModuleEngineUI::Init_test_UI() {


	

}


void ModuleEngineUI::Menu_Bar() {


	if (ImGui::BeginMainMenuBar())
	{

		Menu_Bar_File();
		Menu_Bar_Edit();
		Menu_Bar_Asset();
		Menu_Bar_GameObject();
		Menu_Bar_Component();
		Menu_Bar_Window();
		Menu_Bar_Help();

		ImGui::EndMainMenuBar();
	}
}

	void ModuleEngineUI::Menu_Bar_File(){
	
		if (ImGui::BeginMenu("File"))
		{
			//ImGui::MenuItem("(menu)", NULL, false, false);
			if (ImGui::MenuItem("New Scene","Ctrl+N")) {}
			if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {}
			
			ImGui::Separator(); 
			
			if (ImGui::MenuItem("Save", "Ctrl+S")) {}
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {}
			
			ImGui::Separator();

			if (ImGui::MenuItem("New Project")) {}
			if (ImGui::MenuItem("Open Project")) {}
			if (ImGui::MenuItem("Save Project")) {}

			ImGui::Separator();

			if (ImGui::MenuItem("Build Settings...","Ctrl+Shift+B")) {}
			if (ImGui::MenuItem("Build And Run", "Ctrl+B")) {}
			
			ImGui::Separator();

			if (ImGui::MenuItem("Exit")) {
	
				Exit_Pressed = true;
			}

			ImGui::EndMenu();
		}
	}

	void ModuleEngineUI::Menu_Bar_Edit(){
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "Ctrl+Z",false,false)) {}
			if (ImGui::MenuItem("Redo Scene", "Ctrl+Y",false, false)) {}

			ImGui::Separator();

			if (ImGui::MenuItem("Select All","Ctrl+A")) {}
			if (ImGui::MenuItem("Deselect All","Shift+D")) {}
			if (ImGui::MenuItem("Select Children","Shift+C")) {}
			if (ImGui::MenuItem("Select Prefab Root","Ctrl+Shift+R")) {}
			if (ImGui::MenuItem("Invert Selection","Ctrl+I")) {}
			
			ImGui::Separator();

			if (ImGui::MenuItem("Cut","Ctrl+X")) {}
			if (ImGui::MenuItem("Copy","Ctrl+C")) {}
			if (ImGui::MenuItem("Paste","Ctrl+V")) {}

			ImGui::Separator();

			if (ImGui::MenuItem("Duplicate", "Ctrl+D")) {}
			if (ImGui::MenuItem("Delete")) {}
			
			ImGui::Separator();

			if (ImGui::MenuItem("Frame Selected", "F")) {}
			if (ImGui::MenuItem("Lock View to Selected", "Shift+F")) {}
			if (ImGui::MenuItem("Find", "Ctrl+F")) {}

			ImGui::Separator();

			if (ImGui::MenuItem("Play", "Ctrl+P")) {}
			if (ImGui::MenuItem("Pause", "Ctrl+Shift+P")) {}
			if (ImGui::MenuItem("Step", "Ctrl+ALt+P")) {}

			ImGui::Separator();

			if (ImGui::MenuItem("Sign in",NULL,false,false)) {}
			if (ImGui::MenuItem("Sign out", NULL, false, false)) {}

			ImGui::Separator();

			if (ImGui::BeginMenu("Selection")) {
				
				if (ImGui::MenuItem("Load Selection 1")){}
				if (ImGui::MenuItem("Load Selection 2")){}
				if (ImGui::MenuItem("Save Selection 1")){}
				if (ImGui::MenuItem("Save Selection 2")){}
		
				ImGui::EndMenu();
			}

			
			ImGui::Separator();

			if (ImGui::MenuItem("Project Settings...")) {}
			if (ImGui::MenuItem("Preferences...")) {}
			if (ImGui::MenuItem("Shortcuts...")) {}
			if (ImGui::MenuItem("Modules...")) {}
			if (ImGui::MenuItem("Clear All PlayersPrefs")) {}

			ImGui::Separator();

			if (ImGui::BeginMenu("Graphic Tier")) {

				if (ImGui::MenuItem("Shader1")){}
				if (ImGui::MenuItem("Shader2")) {}
				if (ImGui::MenuItem("Shader3")) {}

				ImGui::EndMenu();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Snap Settings...")) {}


			ImGui::EndMenu();
		}
	}
	void ModuleEngineUI::Menu_Bar_Asset(){
		if (ImGui::BeginMenu("Asset"))
		{


			ImGui::EndMenu();
		}
	}
	void ModuleEngineUI::Menu_Bar_GameObject(){

		if (ImGui::BeginMenu("GameObject"))
		{


			ImGui::EndMenu();
		}
	}
	void ModuleEngineUI::Menu_Bar_Component(){
		if (ImGui::BeginMenu("Component"))
		{


			ImGui::EndMenu();
		}
	}
	void ModuleEngineUI::Menu_Bar_Window(){
		if (ImGui::BeginMenu("Window"))
		{


			ImGui::EndMenu();
		}
	}
	void ModuleEngineUI::Menu_Bar_Help(){

		if (ImGui::BeginMenu("Help"))
		{


			ImGui::EndMenu();
		}
	}


	