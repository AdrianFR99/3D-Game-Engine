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

public:

	void Init_test_UI();


};

