#pragma once
#include "Module.h"




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


public:
	
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	void Init_test_UI();


};

