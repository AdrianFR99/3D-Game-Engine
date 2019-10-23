
#include "ModuleGameobject.h"
#include "Application.h"
//#include "mmgr/mmgr.h"


ModuleGameobject::ModuleGameobject(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleGameobject::~ModuleGameobject()
{
}

bool ModuleGameobject::Init() {

	
	return true;
}

bool ModuleGameobject::Start() {

	CreateGameObject();

	return true;
}


void ModuleGameobject::Draw() {



	

}

bool ModuleGameobject::CleanUp() {
	
	return true;
}

Gameobject * ModuleGameobject::CreateGameObject()
{
	//create the game object
	Gameobject* creation = new Gameobject(id);
	
	id = id++;

	//get it inside of the list
	GameobjectList.push_back(creation);


	return nullptr;
}

bool ModuleGameobject::LoadFiles(const char* path) {


	

	App->GearConsole.AddLog(" Loading File %s", path);

	return true;
}


