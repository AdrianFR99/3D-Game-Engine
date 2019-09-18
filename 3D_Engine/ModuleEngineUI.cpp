#include "Application.h"
#include "ModuleEngineUI.h"



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

	Init_test_UI();


	return true;
}



void ModuleEngineUI::Init_test_UI() {


	

}