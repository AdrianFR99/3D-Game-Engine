#include "Application.h"
#include "ModuleEngineUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"
#include "ModuleAssets.h"

#include "WindowUI.h"
#include "WindowUI_Settings.h"
#include "WindowInspector.h"
#include "WindowHierarchy.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
//#include "imgui/imgui_impl_sdl.h"


#include "Maths.h"



ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


ModuleEngineUI::ModuleEngineUI(Application* app, bool start_enabled):Module(app, start_enabled)
{

	



}


ModuleEngineUI::~ModuleEngineUI()
{
}

bool ModuleEngineUI::Init() {


	settingsPanel = new WindowUI_Settings("Configurations");
	Panels.push_back(settingsPanel);

	HierarchyPanel = new WindowHierarchy("Hierarchy");
	InspectorPanel = new WindowInspector("Inspector");

	App->GearConsole.AddLog(" Init UI subsystem ");
	return true;
}

bool ModuleEngineUI::Awake()
{
	bool ret = true;

	LOG("Loading ImGui");
	App->GearConsole.AddLog(" Loading ImGui ");
	
	
	return ret;
}

//Called to init variables
void ModuleEngineUI::Load(nlohmann::json& file)
{
	LOG("Load variables from Json to module UI");
	App->GearConsole.AddLog(" Load Config Variables for UI ");

	show_demo_window = file["Modules"]["IMGUI"]["show_demo_window"];
	show_another_window = file["Modules"]["IMGUI"]["show_another_window"];
	current_tab = file["Modules"]["IMGUI"]["current_tab"];
	openWindowAbout = file["Modules"]["IMGUI"]["openWindowAbout"];
	showConsole = file["Modules"]["IMGUI"]["showConsole"];
	Show_ImGui_Demo = file["Modules"]["IMGUI"]["Show_ImGui_Demo"];
	Exit_Pressed = file["Modules"]["IMGUI"]["Exit_Pressed"];


}

// Called to init variables
void ModuleEngineUI::Save(nlohmann::json& file)
{
	LOG("Save variables from Module UI to Config");
	App->GearConsole.AddLog(" Save variables from Module UI to Config ");

	file["Modules"]["IMGUI"]["show_demo_window"] = show_demo_window;
	file["Modules"]["IMGUI"]["show_another_window"] = show_another_window;
	file["Modules"]["IMGUI"]["current_tab"] = current_tab;
	file["Modules"]["IMGUI"]["openWindowAbout"] = openWindowAbout;
	file["Modules"]["IMGUI"]["showConsole"] = showConsole;
	file["Modules"]["IMGUI"]["Show_ImGui_Demo"] = Show_ImGui_Demo;
	file["Modules"]["IMGUI"]["Exit_Pressed"] = Exit_Pressed;




}

// Called to load variables
void ModuleEngineUI::ReloadFromConfig()
{
	LOG("Load variables from Config");
	App->GearConsole.AddLog(" Load variables from Config to UI");



}

bool ModuleEngineUI::Start() {


	settingsPanel->SetState(true);
	HierarchyPanel->SetState(true);
	InspectorPanel->SetState(true);
	showConsole = !showConsole;

	App->GearConsole.AddLog(" glew version:");
	App->GearConsole.AddLog(" %s", glewGetString(GLEW_VERSION));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	App->GearConsole.AddLog(" create IMGUI Context ");
	

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window,App->renderer3D->context);
	App->GearConsole.AddLog(" Init SDL2 for OpenGl ");
	ImGui_ImplOpenGL3_Init();
	App->GearConsole.AddLog(" Init OpenGL3 ");
	

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;     // Enable Keyboard Controls

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// We specify a default position/size in case there's no data in the .ini file. Typically this isn't required! We only do it to make the Demo applications a little more welcoming.

	/*ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);*/

	Selecet_Style(1); // default style 
					  //1: Corporate Grey
					  //2: Light Green
					  //3: blue ayes
					  //4: cherry
					  //5: another dark theme

	App->GearConsole.AddLog(" Load IMGUI theme ");
	return true;
}

update_status  ModuleEngineUI::PreUpdate(float dt) {

	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	if (ImGuiConfigFlags_DockingEnable)
		UpdatedockingWindos();

	return UPDATE_CONTINUE;
}
update_status ModuleEngineUI::Update(float dt) {


	if(!Exit_Pressed)
	return UPDATE_CONTINUE;
	else
		return UPDATE_STOP;

	
}
update_status  ModuleEngineUI::PostUpdate(float dt) {


	settingsPanel->Display();
	
	HierarchyPanel->Display();

	InspectorPanel->Display();

	Menu_Bar();
		
	if(Show_ImGui_Demo)
	ImGui::ShowDemoWindow();

	if (showConsole)
	{
		App->GearConsole.Draw("Gear Console",&showConsole);
	}
	if (openWindowAbout)
	{
		settingsPanel->DrawAbout(&openWindowAbout, &current_tab);
	}

	if (ImGuiConfigFlags_DockingEnable)
		ImGui::End();
	
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
		Menu_Bar_About();

		ImGui::EndMainMenuBar();
	}
}

	void ModuleEngineUI::Menu_Bar_File(){
	
		if (ImGui::BeginMenu("File"))
		{
			//ImGui::MenuItem("(menu)", NULL, false, false);
			if (ImGui::MenuItem("New Scene","Ctrl+N")) 
			{
				App->Gameobjects->CleanUp();
			
			}
			if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {}
			
			ImGui::Separator(); 
			
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
				toSave = true;
			}
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {}
			
			ImGui::Separator();


			if (ImGui::MenuItem("Load")) {
				toLoad = true;
			}
			

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
			if (ImGui::MenuItem("Console", "Ctrl+C")) {
				showConsole = !showConsole;
			}
			if ( ImGui::MenuItem("Settings")) {
				if (settingsPanel->isActive()==false)
				{
					settingsPanel->SetState(true);

				}
				else
					settingsPanel->SetState(false);
				
			}
			if (ImGui::MenuItem("Hierarchy")) {
				if (HierarchyPanel->isActive() == false)
				{
					HierarchyPanel->SetState(true);

				}
				else
					HierarchyPanel->SetState(false);

			}
			if (ImGui::MenuItem("Inspector")) {
				if (InspectorPanel->isActive() == false)
				{
					InspectorPanel->SetState(true);

				}
				else
					InspectorPanel->SetState(false);

			}

			ImGui::EndMenu();
		}
	}
	void ModuleEngineUI::Menu_Bar_Help(){

		if (ImGui::BeginMenu("Help"))
		{

			if (ImGui::MenuItem("Gui Demo","", Show_ImGui_Demo,true))
				Show_ImGui_Demo = !Show_ImGui_Demo;
			if (ImGui::MenuItem("GitHub Repository"))
				App->RequestBrowser("https://github.com/AdrianFR99/3D-Game-Engine");
			if (ImGui::MenuItem("Documentation"))
				App->RequestBrowser("https://github.com/AdrianFR99/3D-Game-Engine/wiki");
			if (ImGui::MenuItem("Download latest"))
				App->RequestBrowser("https://github.com/AdrianFR99/3D-Game-Engine/releases");
			if (ImGui::MenuItem("Report a bug"))
				App->RequestBrowser("https://github.com/AdrianFR99/3D-Game-Engine/issues");

			ImGui::EndMenu();
		}
	}

	void ModuleEngineUI::Menu_Bar_About() {


		if (ImGui::BeginMenu("About"))
		{

			if (ImGui::MenuItem("About")) {
				openWindowAbout = !openWindowAbout;
			}
			
			ImGui::EndMenu();
		}
		
	}

	ImGuiWindowFlags ModuleEngineUI::Setting_Flag_bools(bool no_titlebar, bool no_scrollbar,
		bool no_menu , bool no_move, bool no_resize , bool no_collapse , bool no_close,
		bool no_nav, bool no_background , bool no_bring_to_front){

		ImGuiWindowFlags window_flags = 0;
		if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
		if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
		if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
		if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
		if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
		if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
		if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		

		return window_flags;
	}

	void ModuleEngineUI::Assign_FPS_Data(float fps, float ms) {

		if (settingsPanel != nullptr) 
			settingsPanel->FPS_vec_Alloc(fps, ms);


	}

	void ModuleEngineUI::UpdatedockingWindos(int style) const
	{
		
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGuiWindowFlags window_flags= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
		window_flags |= ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;

		if (style == 0)
		{
			
			// prepared to set varios styles of docking flags. main idea is o pass a bool and decide what premade styles you want. 
			//For now the default is a movable window with lateral resize capability
			window_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
			window_flags |= ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;

		}
		else
		{
			

		}

			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 1.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1.0f, 1.0f));

			//cant pass a bool directily, must be a static bool
		static bool static_true = true;

		ImGui::Begin("DockSpace Demo", &static_true, window_flags);
		ImGui::PopStyleVar(3);

		ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
		ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

	

		

	}

	void ModuleEngineUI::Selecet_Style(const int looks)
	{
		ImGuiStyle * style = &ImGui::GetStyle();

		if (looks == 1) // Corporate Grey
		{
			ImGuiStyle & style = ImGui::GetStyle();
			ImVec4 * colors = style.Colors;

			/// 0 = FLAT APPEARENCE
			/// 1 = MORE "3D" LOOK
			int is3D = 0;

			#define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
			#define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
			#define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
			// backgrounds (@todo: complete with BG_MED, BG_LOW)
			#define BG(v)   ImVec4(0.200f, 0.220f, 0.270f, v)
			// text
			#define TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

			style.Colors[ImGuiCol_Text] = TEXT(0.78f);
			style.Colors[ImGuiCol_TextDisabled] = TEXT(0.28f);
			style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
			style.Colors[ImGuiCol_ChildWindowBg] = BG(0.58f);
			style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
			style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
			style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_FrameBg] = BG(0.70f);
			style.Colors[ImGuiCol_FrameBgHovered] = MED(0.48f);
			style.Colors[ImGuiCol_FrameBgActive] = MED(0.80f);
			style.Colors[ImGuiCol_TitleBg] = LOW(1.00f);
			style.Colors[ImGuiCol_TitleBgActive] = HI(1.00f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
			style.Colors[ImGuiCol_MenuBarBg] = BG(0.47f);
			style.Colors[ImGuiCol_ScrollbarBg] = BG(1.00f);
			style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
			style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
			style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
			style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
			style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
			style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
			style.Colors[ImGuiCol_ButtonActive] = MED(1.00f);
			style.Colors[ImGuiCol_Header] = MED(0.36f);
			style.Colors[ImGuiCol_HeaderHovered] = MED(0.46f);
			style.Colors[ImGuiCol_HeaderActive] = HI(1.00f);
			//style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
			//style.Colors[ImGuiCol_ColumnHovered] = MED(0.78f);
			//style.Colors[ImGuiCol_ColumnActive] = MED(1.00f);
			style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
			style.Colors[ImGuiCol_ResizeGripHovered] = MED(0.78f);
			style.Colors[ImGuiCol_ResizeGripActive] = MED(1.00f);
			style.Colors[ImGuiCol_PlotLines] = TEXT(0.63f);
			style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
			style.Colors[ImGuiCol_PlotHistogram] = TEXT(0.63f);
			style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
			style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);
			//style.Colors[ImGuiCol_Tab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
			/*style.Colors[ImGuiCol_TabHovered] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
			style.Colors[ImGuiCol_TabActive] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
			style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
			style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);*/
			
				
			// [...]
			style.Colors[ImGuiCol_ModalWindowDarkening] = BG(0.73f);

			style.PopupRounding = 3;

			style.WindowPadding = ImVec2(4, 4);
			style.FramePadding = ImVec2(6, 4);
			style.ItemSpacing = ImVec2(6, 2);

			style.ScrollbarSize = 18;

			style.WindowBorderSize = 1;
			style.ChildBorderSize = 1;
			style.PopupBorderSize = 1;
			style.FrameBorderSize = is3D;

			style.WindowRounding = 3;
			style.ChildRounding = 3;
			style.FrameRounding = 3;
			style.ScrollbarRounding = 2;
			style.GrabRounding = 3;

			#ifdef IMGUI_HAS_DOCK 
			style.TabBorderSize = is3D;
			style.TabRounding = 3;

			colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.78f, 0.10f, 0.38f, 1.00f);
			colors[ImGuiCol_Tab] = ImVec4(0.75f, 0.10f, 0.25f, 1.00f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.70f, 0.10f, 0.40f, 1.00f);
			colors[ImGuiCol_TabActive] = ImVec4(0.73f, 0.10f, 0.33f, 1.00f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.75f, 0.10f, 0.25f, 1.00f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.73f, 0.10f, 0.33f, 1.00f);
			colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.10f, 0.28f);

			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}
			#endif
		
		}
		else if (looks == 2) //LightGreen
		{
			ImGuiStyle* style = &ImGui::GetStyle();
			ImVec4* colors = style->Colors;

			style->WindowRounding = 2.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
			style->ScrollbarRounding = 3.0f;             // Radius of grab corners rounding for scrollbar
			style->GrabRounding = 2.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
			style->AntiAliasedLines = true;
			style->AntiAliasedFill = true;
			style->WindowRounding = 2;
			style->ChildRounding = 2;
			style->ScrollbarSize = 16;
			style->ScrollbarRounding = 3;
			style->GrabRounding = 2;
			style->ItemSpacing.x = 10;
			style->ItemSpacing.y = 4;
			style->IndentSpacing = 22;
			style->FramePadding.x = 6;
			style->FramePadding.y = 4;
			style->Alpha = 1.0f;
			style->FrameRounding = 3.0f;

			colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
			//colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.93f, 0.93f, 0.93f, 0.98f);
			colors[ImGuiCol_Border] = ImVec4(0.71f, 0.71f, 0.71f, 0.08f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.71f, 0.71f, 0.71f, 0.55f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.94f, 0.94f, 0.94f, 0.55f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.71f, 0.78f, 0.69f, 0.98f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.82f, 0.78f, 0.78f, 0.51f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.61f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.90f, 0.90f, 0.90f, 0.30f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.92f, 0.92f, 0.78f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.184f, 0.407f, 0.193f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4(0.71f, 0.78f, 0.69f, 0.40f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.725f, 0.805f, 0.702f, 1.00f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.793f, 0.900f, 0.836f, 1.00f);
			colors[ImGuiCol_Header] = ImVec4(0.71f, 0.78f, 0.69f, 0.31f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.71f, 0.78f, 0.69f, 0.80f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.71f, 0.78f, 0.69f, 1.00f);
			/*colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
			colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
			colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);*/
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.45f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
			colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
			colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
			colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
		

		}
		else if (looks == 3) //blue eyes
		{
			static ImVec3 color_for_text = ImVec3(236.f / 255.f, 240.f / 255.f, 241.f / 255.f);
			static ImVec3 color_for_head = ImVec3(41.f / 255.f, 128.f / 255.f, 185.f / 255.f);
			static ImVec3 color_for_area = ImVec3(57.f / 255.f, 79.f / 255.f, 105.f / 255.f);
			static ImVec3 color_for_body = ImVec3(44.f / 255.f, 62.f / 255.f, 80.f / 255.f);
			static ImVec3 color_for_pops = ImVec3(33.f / 255.f, 46.f / 255.f, 60.f / 255.f);


			ImGuiStyle& style = ImGui::GetStyle();

			style.Colors[ImGuiCol_Text] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 1.00f);
			style.Colors[ImGuiCol_TextDisabled] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.58f);
			style.Colors[ImGuiCol_WindowBg] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.95f);
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.58f);
			style.Colors[ImGuiCol_Border] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.00f);
			style.Colors[ImGuiCol_BorderShadow] = ImVec4(color_for_body.x, color_for_body.y, color_for_body.z, 0.00f);
			style.Colors[ImGuiCol_FrameBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
			style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
			style.Colors[ImGuiCol_FrameBgActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
			style.Colors[ImGuiCol_TitleBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.75f);
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
			style.Colors[ImGuiCol_MenuBarBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.47f);
			style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.21f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
			//style.Colors[ImGuiCol_ComboBg] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 1.00f);
			style.Colors[ImGuiCol_CheckMark] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.80f);
			style.Colors[ImGuiCol_SliderGrab] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.50f);
			style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
			style.Colors[ImGuiCol_Button] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.50f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.86f);
			style.Colors[ImGuiCol_ButtonActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
			style.Colors[ImGuiCol_Header] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.76f);
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.86f);
			style.Colors[ImGuiCol_HeaderActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
			//style.Colors[ImGuiCol_Column] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.32f);
			//style.Colors[ImGuiCol_ColumnHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
			//style.Colors[ImGuiCol_ColumnActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
			style.Colors[ImGuiCol_ResizeGrip] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.15f);
			style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.78f);
			style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
			//style.Colors[ImGuiCol_CloseButton] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.16f);
			//style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.39f);
			//style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 1.00f);
			style.Colors[ImGuiCol_PlotLines] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.63f);
			style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
			style.Colors[ImGuiCol_PlotHistogram] = ImVec4(color_for_text.x, color_for_text.y, color_for_text.z, 0.63f);
			style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 1.00f);
			style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(color_for_head.x, color_for_head.y, color_for_head.z, 0.43f);
			style.Colors[ImGuiCol_PopupBg] = ImVec4(color_for_pops.x, color_for_pops.y, color_for_pops.z, 0.92f);
			style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(color_for_area.x, color_for_area.y, color_for_area.z, 0.73f);

		
		}

		else if (looks == 4) //cherry theme
		{
#define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
#define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
#define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
			// backgrounds (@todo: complete with BG_MED, BG_LOW)
#define BG(v)   ImVec4(0.200f, 0.220f, 0.270f, v)
			// text
#define TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

			auto &style = ImGui::GetStyle();
			style.Colors[ImGuiCol_Text] = TEXT(0.78f);
			style.Colors[ImGuiCol_TextDisabled] = TEXT(0.28f);
			style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
			style.Colors[ImGuiCol_ChildWindowBg] = BG(0.58f);
			style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
			style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
			style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_FrameBg] = BG(1.00f);
			style.Colors[ImGuiCol_FrameBgHovered] = MED(0.78f);
			style.Colors[ImGuiCol_FrameBgActive] = MED(1.00f);
			style.Colors[ImGuiCol_TitleBg] = LOW(1.00f);
			style.Colors[ImGuiCol_TitleBgActive] = HI(1.00f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
			style.Colors[ImGuiCol_MenuBarBg] = BG(0.47f);
			style.Colors[ImGuiCol_ScrollbarBg] = BG(1.00f);
			style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
			style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
			style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
			style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
			style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
			style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
			style.Colors[ImGuiCol_ButtonActive] = MED(1.00f);
			style.Colors[ImGuiCol_Header] = MED(0.76f);
			style.Colors[ImGuiCol_HeaderHovered] = MED(0.86f);
			style.Colors[ImGuiCol_HeaderActive] = HI(1.00f);
			//style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
			//style.Colors[ImGuiCol_ColumnHovered] = MED(0.78f);
			//style.Colors[ImGuiCol_ColumnActive] = MED(1.00f);
			style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
			style.Colors[ImGuiCol_ResizeGripHovered] = MED(0.78f);
			style.Colors[ImGuiCol_ResizeGripActive] = MED(1.00f);
			style.Colors[ImGuiCol_PlotLines] = TEXT(0.63f);
			style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
			style.Colors[ImGuiCol_PlotHistogram] = TEXT(0.63f);
			style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
			style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);
			// [...]
			style.Colors[ImGuiCol_ModalWindowDarkening] = BG(0.73f);

			style.WindowPadding = ImVec2(6, 4);
			style.WindowRounding = 0.0f;
			style.FramePadding = ImVec2(5, 2);
			style.FrameRounding = 3.0f;
			style.ItemSpacing = ImVec2(7, 1);
			style.ItemInnerSpacing = ImVec2(1, 1);
			style.TouchExtraPadding = ImVec2(0, 0);
			style.IndentSpacing = 6.0f;
			style.ScrollbarSize = 12.0f;
			style.ScrollbarRounding = 16.0f;
			style.GrabMinSize = 20.0f;
			style.GrabRounding = 2.0f;

			style.WindowTitleAlign.x = 0.50f;

			style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
			style.FrameBorderSize = 0.0f;
			style.WindowBorderSize = 1.0f;
		}
		else if (looks == 5)
		{
		
			ImGui::GetStyle().FrameRounding = 4.0f;
			ImGui::GetStyle().GrabRounding = 4.0f;

			ImVec4* colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
			colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
			colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
			colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
			colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
			colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
			colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		}

	}

	