
#include "ModuleGameobject.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleEngineUI.h"
#include"WindowHierarchy.h"
#include "mmgr/mmgr.h"


ModuleGameobject::ModuleGameobject(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleGameobject::~ModuleGameobject()
{
}

bool ModuleGameobject::Init(nlohmann::json config) {


	return true;
}

bool ModuleGameobject::Start() {


	return true;
}

update_status ModuleGameobject::PreUpdate(float dt) {

	//App->SceneEngine->scene->UpdateGlobalTransform();


	return UPDATE_CONTINUE;
}

update_status ModuleGameobject::Update(float dt) {

	for (int i = 0; i < GameobjectList.size(); ++i) {
		if (GameobjectList[i]->toDelete)
			App->Gameobject->SetToDestroy(GameobjectList[i]);
		
		
		
		if (GameobjectList[i]->UpdateTransform)
		{
			App->SceneEngine->scene->UpdateGlobalTransform();
			GameobjectList[i]->UpdateTransform = false;
		}

		GameobjectList[i]->Update();


	}


	return UPDATE_CONTINUE;
}


void ModuleGameobject::Draw() {


	if (App->camera->EditorCam->Culling) {//FIX
		Frustum aux = App->camera->EditorCam->GetFrustum();
		App->camera->DrawIfInside(aux);
	}
	else {
	
		for (int i = 0; i < GameobjectList.size(); ++i) {

			GameobjectList[i]->Draw();

		}
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

	//Delete from list of parent and insert in new parent
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
		to_change->Father = new_father;
	}

}

void ModuleGameobject::SetToDestroy(Gameobject * object)
{
	//unparent

	bool ret = false;
	if (object->Father != nullptr)
	{
		Gameobject* tmp = object->Father;

		for (int i = 0; i < tmp->GameObject_Child_Vec.size(); ++i)
		{
			if (tmp->GameObject_Child_Vec[i] == object)
			{
				tmp->GameObject_Child_Vec.erase(tmp->GameObject_Child_Vec.begin() + i);
				ret = true;
				break;
			}
		}

	}


	//delete childs and information
	RecursiveDestruction(object);


}

void ModuleGameobject::RecursiveDestruction(Gameobject * object)
{
	//recursivele call each child to delete all members
	if (object != nullptr)
	{
		Gameobject* tmp = object;

		if (tmp->GameObject_Child_Vec.size() > 0)
		{

			for (std::vector<Gameobject*>::iterator it = object->GameObject_Child_Vec.begin(); it != object->GameObject_Child_Vec.end(); ++it)
			{
				RecursiveDestruction(*it);
			}


		}
		object->GameObject_Child_Vec.clear();
	}

	

	object->CleanUp();
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
	creation->aabb.SetFrom(AABB(float3::zero - float3::one, float3::zero + float3::one));


	App->SceneEngine->scene = creation;

	//get it inside of the list
	GameobjectList.push_back(creation);


	return creation;
}

Gameobject * ModuleGameobject::CreateEmpty()
{
	//create the game object
	Gameobject* gm = CreateGameObject();
	gm->Father = App->SceneEngine->GetSceneGameObjcet();
	Gameobject* scene = App->SceneEngine->GetSceneGameObjcet();
	scene->GameObject_Child_Vec.push_back(gm);

	return gm;
}

bool ModuleGameobject::LoadFiles(const char* path) {




	App->GearConsole.AddLog(" Loading File %s", path);

	return true;
}


Gameobject * ModuleGameobject::CreateEmptyFatherLess()
{
	//create the game object
	Gameobject* gm = CreateGameObject();

	return gm;
}

void ModuleGameobject::SetTextureToActiveGameobject(uint id)
{
	// --- Assign Texture to Object's Material ---
	ComponentMaterial* Material = App->UI_Layer->HierarchyPanel->getActiveGameobject()->materialPointer;

	if (Material)
	{
		//Material->FreeTexture();
		Material->SetDiffuseID( id);
		Material->SetTextureID ( id);
	}
}
