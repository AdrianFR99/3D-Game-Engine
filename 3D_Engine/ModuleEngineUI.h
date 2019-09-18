#pragma once
#include "Module.h"

#include "imgui/imgui.h"


class ModuleEngineUI:public Module 
{
public:
	ModuleEngineUI(Application* app, bool start_enabled=true);
	~ModuleEngineUI();

public:

	void Init_test_UI();


};

