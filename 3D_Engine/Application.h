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


class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleEngineUI* UI_Layer;

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

//Info
	const char* GetAppName()const;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

// access everywhere
extern Application* App;

#endif // __APPLICATION_CPP__
