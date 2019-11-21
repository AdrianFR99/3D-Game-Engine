#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include <list>
#include "Globals.h"
#include "Timer.h"
#include "Module.h"

#include "JSONLoader.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleEngineUI.h"
#include "ModuleHardware.h"
#include "ModuleAssets.h"
#include "ModuleTexture.h"
#include "JSONLoader.h"
#include "WindowConsole.h"
#include "ModuleScene.h"

//#include "ModuleFileSystem.h"
#include "ModuleGameobject.h"

#include "MathGeoLib/include/Algorithm/Random/LCG.h"

struct Event;


//class ModuleWindow;
//class ModuleInput;
//class ModuleRenderer3D;
//class ModuleCamera3D;
//class ModuleEngineUI;
//class ModuleHardware;
// //ModuleFileSystem
//class ModuleAssets;
//class ModuleTexture;
//class ModuleGameobject;
//class ModuleScene;
//

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
	ModuleTexture* Textures = nullptr;
	ModuleGameobject* Gameobjects = nullptr;
	ModuleScene*SceneEngine = nullptr;

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
	bool Awake();
	update_status Update();
	bool CleanUp();


public:

	std::string AppName;
	std::string StudyCenter;

	std::string AssetModel;

	//Console
	AppConsole GearConsole;

public:

//FPS
	uint GetMaxFrameRate()const;
	void SetMaxFrameRate(uint MaxFrameRate);

//Web
	void RequestBrowser(const char*URL);
//Event
	void SendEvent(const Event& event);
//Info
	const char* GetAppName()const;

//Random Generator
	LCG& GetRandom();
	LCG* RandomNumbGenerator = nullptr;
private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	void save(nlohmann::json& file);
	void load(nlohmann::json& file);
	void RefreshConfig();

	JSONLoader JSONLoad;
	nlohmann::json settings;
};

// access everywhere
extern Application* App;

#endif // __APPLICATION_CPP__
