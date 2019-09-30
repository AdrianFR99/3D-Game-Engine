#include "Application.h"



Application::Application()
{

	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	UI_Layer = new ModuleEngineUI(this);
	

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
	AddModule(UI_Layer);
	
	// Renderer last!
	AddModule(renderer3D);

	AppName = "Engine";
	   	  
}

Application::~Application()
{
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL)
	{
		delete item->data;
		item = item->prev;
	}
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}
	
	ms_timer.Start();
	MaxFrameRate(0);

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





}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	p2List_item<Module*>* item = list_modules.getFirst();
	
	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->PreUpdate(dt);
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->Update(dt);
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->PostUpdate(dt);
		item = item->next;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}
void  Application::RequestBrowser(const char*URL) {
	
	ShellExecuteA(NULL, "open", URL, NULL, NULL, SW_SHOWNORMAL);


}

void Application::MaxFrameRate(uint framerate) {


	if (framerate > 0)
		capped_ms = 1000 / framerate;
	else
		capped_ms = 0;

}


uint Application::GetMaxFrameRate()const {

	if (capped_ms > 0)
		return (uint)((1.0f / capped_ms) * 1000.0f);
	else
		return 0;
}

const char* Application::Get_App_Name() const {

	return AppName.c_str();
}