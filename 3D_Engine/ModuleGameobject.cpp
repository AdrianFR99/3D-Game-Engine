
#include "ModuleGameobject.h"
#include "Application.h"

#include "mmgr/mmgr.h"


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

	

	return true;
}


void ModuleGameobject::Draw() {

	for (int i = 0; i < GameobjectList.size(); ++i) {

		GameobjectList[i]->Draw();

		
	}

	

}

bool ModuleGameobject::CleanUp() {
	

	for (int i = 0; i < GameobjectList.size(); ++i) {

		GameobjectList[i]->CleanUp();

		//delete(Meshes_Vec[i]);
		

		if (GameobjectList[i] != nullptr) {
			delete GameobjectList[i]; \
				GameobjectList[i] = nullptr;
		}
	}

	GameobjectList.clear();
	return true;
}

Gameobject * ModuleGameobject::CreateGameObject()
{
	//create the game object
	Gameobject* creation = new Gameobject(id);
	
	id = id++;

	//get it inside of the list
	GameobjectList.push_back(creation);


	return creation;
}

Gameobject * ModuleGameobject::CreateFatherGameObject()
{
	//create the game object
	Gameobject* creation = new Gameobject(id);
	std::string name;
	name = "scene";
	creation->nameGameObject = name;

	id = id++;

	//get it inside of the list
	GameobjectList.push_back(creation);


	return creation;
}

bool ModuleGameobject::LoadFiles(const char* path) {


	

	App->GearConsole.AddLog(" Loading File %s", path);

	return true;
}


