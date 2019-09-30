#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include "p2List.h"
#include "Globals.h"
#include "Timer.h"



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


	p2List<Module*> list_modules;

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
	void MaxFrameRate(uint framerate);
	uint GetMaxFrameRate()const;


//Web
	void RequestBrowser(const char*URL);

//Info

	const char* Get_App_Name()const;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

// access everywhere
extern Application* App;

#endif // __APPLICATION_CPP__
