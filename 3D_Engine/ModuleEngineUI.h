#pragma once
#include "Module.h"


typedef int ImGuiWindowFlags;

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


	bool Exit_Pressed=false;



public:
	
	void Init_test_UI();
	void Menu_Bar();
	void Menu_Bar_File();
	void Menu_Bar_Edit();
	void Menu_Bar_Asset();
	void Menu_Bar_GameObject();
	void Menu_Bar_Component();
	void Menu_Bar_Window();
	void Menu_Bar_Help();

};

