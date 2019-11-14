
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

void ModuleGameobject::ChangeParenting(Gameobject * to_change, Gameobject * new_father)
{

	//Delete from list of parent and insert in newe parent
	bool ret = false;
	if (to_change->Father != nullptr)
	{
		Gameobject* tmp = to_change->Father;

		for (int i = 0; i < tmp->GameObject_Child_Vec.size(); ++i)
		{
			if (tmp->GameObject_Child_Vec[i] == to_change)
			{
				tmp->GameObject_Child_Vec.erase(tmp->GameObject_Child_Vec.begin() + i);
				ret = true;
				break;
			}
		}

	}
	if (ret == true && new_father != nullptr)
	{
		new_father->GameObject_Child_Vec.push_back(to_change);

	}
	
}

Gameobject * ModuleGameobject::CreateGameObject()
{
	//create the game object
	uint random = App->GetRandom().Int();
	Gameobject* creation = new Gameobject(random);


	//get it inside of the list
	GameobjectList.push_back(creation);


	return creation;
}

Gameobject * ModuleGameobject::CreateFatherGameObject()
{
	//create the game object
	uint random = App->GetRandom().Int();
	Gameobject* creation = new Gameobject(random);
	std::string name;
	name = "scene";
	creation->nameGameObject = name;



	//get it inside of the list
	GameobjectList.push_back(creation);


	return creation;
}

bool ModuleGameobject::LoadFiles(const char* path) {


	

	App->GearConsole.AddLog(" Loading File %s", path);

	return true;
}


