#ifndef __MODULEENGINEUI_H__
#define __MODULEENGINEUI_H__


#include "Module.h"



#include <vector>

typedef int ImGuiWindowFlags;

class WindowUI;
class WindowUI_Settings;



struct ImVec3 { 

	float x, y, z; 
	ImVec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) 
	{
		x = _x; y = _y; z = _z;
	} 
};

class ModuleEngineUI:public Module 
{
public:
	ModuleEngineUI(Application* app, bool start_enabled=true);
	~ModuleEngineUI();

public:

	bool Init();
	bool Start();
	bool Awake();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	void Draw() const;


	

	//Flags
	ImGuiWindowFlags window_flags;



	WindowUI_Settings* settingsPanel=nullptr;
	std::vector<WindowUI*> Panels;

	


public:
	

	//load data
	void Load(nlohmann::json& file);

	//load data
	void Save(nlohmann::json& file);

	//setting up bools flags for the window
	ImGuiWindowFlags Setting_Flag_bools(bool no_titlebar =false, bool no_scrollbar = false,
		bool no_menu = false, bool no_move = false, bool no_resize = false, bool no_collapse = false, bool no_close = false,
		bool no_nav = false, bool no_background = false, bool no_bring_to_front = false);

	//MenuBar 

	void Menu_Bar();
	void Menu_Bar_File();
	void Menu_Bar_Edit();
	void Menu_Bar_Asset();
	void Menu_Bar_GameObject();
	void Menu_Bar_Component();
	void Menu_Bar_Window();
	void Menu_Bar_Help();
	void Menu_Bar_About();

	
	//FPS
	void Assign_FPS_Data(float fps,float ms);


	

	//dock
	void ModuleEngineUI::UpdatedockingWindos(int style=1) const;

	//appereance
	void Selecet_Style(const int style=3);

	bool toSave = false;

	//variables for loading
	bool show_demo_window = true;
	bool show_another_window = false;
	int current_tab = 1;
	bool openWindowAbout = false;
	bool showConsole = false;
	bool Show_ImGui_Demo = false;
	bool Exit_Pressed=false; //Exit engine pressed
	

};

#endif //__MODULEENGINEUI_H__