#include "Application.h"
#include "ModuleEngineUI.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

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

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
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



	return UPDATE_CONTINUE;
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

	


}

void ModuleEngineUI::Init_test_UI() {


	

}