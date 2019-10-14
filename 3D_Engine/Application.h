#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include <list>
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleEngineUI.h"
#include "ModuleHardware.h"
#include "ModuleAssets.h"
#include "JSONLoader.h"
//#include "ModuleFileSystem.h"


struct Event;

class Application
{
public:
	ModuleWindow* window=nullptr;
	ModuleInput* input = nullptr;
	ModuleRenderer3D* renderer3D = nullptr;
	ModuleCamera3D* camera = nullptr;
	ModuleEngineUI* UI_Layer = nullptr;
	ModuleHardware* hardware = nullptr;
	//ModuleFileSystem* fs = nullptr;
	ModuleAssets* Assets = nullptr;

private:

	Timer	ms_timer;
	Timer	FPS_timer;
	float	dt=0;

	Uint32				Current_frames;
	int					FPS_counter;
	int					last_FPS;
	uint				capped_ms;
	int					last_frame_time;

	std::list<Module*> list_modules;


public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();


public:

	std::string AppName;



public:

//FPS
	uint GetMaxFrameRate()const;
	void SetMaxFrameRate(uint MaxFrameRate);

//Web
	void RequestBrowser(const char*URL);
//Event
	void BroadcastEvent(const Event& event);
//Info
	const char* GetAppName()const;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();


	void save();
	void load();
	JSONLoader JSONLoad;
	json settings;
};

// access everywhere
extern Application* App;

#endif // __APPLICATION_CPP__
