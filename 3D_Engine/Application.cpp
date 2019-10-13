#include "Application.h"
#include "Brofiler/Brofiler.h"




Application::Application()
{

	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	//fs = new ModuleFileSystem(ASSETS_FOLDER));
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	UI_Layer = new ModuleEngineUI(this);
	hardware = new ModuleHardware(this);
	Assets = new ModuleAssets(this);

	Current_frames = 0; //current frame the program is
	FPS_counter = 0;   //Frame per cicle
	last_FPS = -1;		
	last_frame_time = -1;
	

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(hardware);
	AddModule(Assets);
	AddModule(UI_Layer);
	// Renderer last!
	AddModule(renderer3D);

	
	
}

Application::~Application()
{
	std::list<Module*>::reverse_iterator item = list_modules.rbegin();

	while(item != list_modules.rend())
	{
		delete *item;
		item++;
	}
}

bool Application::Init()
{
	bool ret = true;

	AppName = "Engine";

	// Call Init() in all modules
	std::list<Module*>::const_iterator item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		ret = (*item)->Init();
		item++;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		ret = (*item)->Start();
		item++;
	}
	
	ms_timer.Start();
	SetMaxFrameRate(0);

	load();
	settings = JSONLoad.getFile();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	++Current_frames;
	++FPS_counter;
	
	if (FPS_timer.Read()>=1000) {

		last_FPS = FPS_counter;
		FPS_counter = 0;
		FPS_timer.Start();
	
	}
	last_frame_time = ms_timer.Read();

	
	//capping FPS
	if (capped_ms > 0 && last_frame_time < capped_ms)
		SDL_Delay(capped_ms-last_frame_time);


	UI_Layer->Assign_FPS_Data((float)last_FPS,(float)last_frame_time);

}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{

	BROFILER_CATEGORY("App_Update", Profiler::Color::Yellow);

	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	std::list<Module*>::const_iterator item = list_modules.begin();
	
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PreUpdate(dt);
		item++;
	}

	item = list_modules.begin();

	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->Update(dt);
		item++;
	}

	item = list_modules.begin();

	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PostUpdate(dt);
		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	save();
	bool ret = true;
	std::list<Module*>::reverse_iterator item = list_modules.rbegin();

	while(item != list_modules.rend() && ret == true)
	{
		ret = (*item)->CleanUp();
		item++;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{

  list_modules.push_back(mod);
}
void  Application::RequestBrowser(const char*URL) {
	
	ShellExecuteA(NULL, "open", URL, NULL, NULL, SW_SHOWNORMAL);


}

uint Application::GetMaxFrameRate()const {


	if (capped_ms > 0)
		return (uint)((1.0f /(float)capped_ms) * 1000.0f);
	else
		return 0;
}
void Application::SetMaxFrameRate(uint MaxFrameRate) {

	if (MaxFrameRate > 0)
		capped_ms = 1000/MaxFrameRate; // ms/Frame  MaxFrameRate/1000.0f->Frame/ms
	else
		capped_ms = 0;
}

const char* Application::GetAppName() const {

	return AppName.c_str();

}

void Application::save()
{
	json test;
	test = {
		{ "Test",{
			{ "mic", "1,2,3" }
		} }
	};

	

	JSONLoad.Save("test.json", test);
	
}


void Application::load()
{
	JSONLoad.Load("test.json");

}