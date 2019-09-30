#ifndef __MODULEENGINEUI_H__
#define __MODULEENGINEUI_H__



#include "Module.h"
#include "JSONLoader.h"



#include <vector>

typedef int ImGuiWindowFlags;

class JSONLoader;

class ModuleEngineUI:public Module 
{
public:
	ModuleEngineUI(Application* app, bool start_enabled=true);
	~ModuleEngineUI();

public:

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	void Draw() const;


	//bools
	bool Show_ImGui_Demo = false;
	bool Exit_Pressed=false; //Exit engine pressed
	bool Config_Window_Open=true;
	
	// int 
	unsigned int App_name;


	//Flags
	ImGuiWindowFlags window_flags;

	//json
	JSONLoader testingmic;


public:
	
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


	




};

#endif //__MODULEENGINEUI_H__