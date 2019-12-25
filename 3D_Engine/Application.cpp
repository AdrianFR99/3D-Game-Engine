#include "Application.h"
#include "Brofiler/Brofiler.h"



#include "mmgr/mmgr.h"




Application::Application()
{
	AppName = "Gear Engine";
	StudyCenter = "CITM";
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	FileSystem = new ModuleFileSystem(this, ASSETS_FOLDER);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	UI_Layer = new ModuleEngineUI(this);
	hardware = new ModuleHardware(this);
	Assets = new ModuleAssets(this);
	Textures = new ModuleTexture(this);
	Gameobject = new ModuleGameobject(this);
	SceneEngine = new ModuleScene(this);
	RS = new ResourceManager(this,true);
	importer = new ModuleImporter(this, true);
	particles = new ModuleParticles(this, true);

	Current_frames = 0; //current frame the program is
	FPS_counter = 0;   //Frame per cicle
	last_FPS = -1;		
	last_frame_time = -1;
	
	RandomNumbGenerator = new math::LCG();
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(RS);
	AddModule(importer);
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(hardware);
	AddModule(FileSystem);
	AddModule(Assets);
	AddModule(Textures);
	AddModule(Gameobject);
	AddModule(SceneEngine);
	AddModule(particles);
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

	if (RandomNumbGenerator)
	{
		delete RandomNumbGenerator;
		RandomNumbGenerator = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;


	
	App->GearConsole.AddLog(" Welcome to Gear Engine");
	
//	 Call Init() in all modules
	std::list<Module*>::const_iterator item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		ret = (*item)->Init(settings);
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
	SetMaxFrameRate(60);



	return ret;
}

// Called to load config
bool Application::Awake()
{
	//load config
	//not loading variables from, just parcing doc
	App->GearConsole.AddLog(" Loading Config File and Configuration");
	JSONLoad.Load("SettingConfig/GearConfig.json");
	settings = JSONLoad.getFile();

	load(settings);

	return true;
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

	if (UI_Layer->toSave == true)
	{
		UI_Layer->toSave = false;
		save(settings);
	}

	if (UI_Layer->toLoad == true)
	{
		UI_Layer->toLoad = false;
		load(settings);

		RefreshConfig();

	}
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
	
	bool ret = true;
	std::list<Module*>::reverse_iterator item = list_modules.rbegin();

	while(item != list_modules.rend() && ret == true)
	{
		ret = (*item)->CleanUp();
		item++;
	}

	GearConsole.ClearLog();

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

	return AppName.data();

}

void Application::save(nlohmann::json& file)
{

	App->GearConsole.AddLog(" Save variables ");
	file["Modules"]["App"]["Name"] = AppName.data();
	
	file["Modules"]["App"]["Uni"] = StudyCenter.data();


	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end())
	{
		(*item)->Save(file);
		item++;
	}
	
	JSONLoad.Save("SettingConfig/GearConfig.json", settings); 
}

void Application::load(nlohmann::json& file)
{

	std::string name = file["Modules"]["App"]["Name"];
	AppName = name;

	std::string Uniname = file["Modules"]["App"]["Uni"];
	StudyCenter = Uniname;

	std::string toload = file["Modules"]["App"]["Assets"];
	AssetModel = toload;

	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end())
	{
		(*item)->Load(file);
		item++;
	}


}

void Application::SendEvent(const Event& event)
{
	for (std::list<Module*>::iterator it = list_modules.begin(); it != list_modules.end(); ++it)
		(*it)->CallbackEvent(event);
}



void Application::RefreshConfig()
{
	for (std::list<Module*>::iterator it = list_modules.begin(); it != list_modules.end(); ++it)
		(*it)->ReloadFromConfig();
}


LCG & Application::GetRandom()
{
	return *RandomNumbGenerator;
}

const char* Application::GetOrganizationName() const
{
	return StudyCenter.data();
}

JSONLoader * Application::GetJsonLoader()
{
	return &JSONLoad;
}
