#include "Application.h"
#include "ModuleScene.h"
#include "ModuleAssets.h"
#include "ModuleGameObject.h"

#include "mmgr/mmgr.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled):Module(app, start_enabled)
{
}


ModuleScene::~ModuleScene()
{
}


bool ModuleScene::Init(nlohmann::json config) {

	//CreatePrimitive();
	scene = App->Gameobjects->CreateFatherGameObject();


	return true;
}

bool ModuleScene::Start() {

//primitves must Load AFTER FBX
	App->Assets->LoadFiles(App->AssetModel.data());
	//App->Assets->CreatePrimitive(Primitive_Type::BOTTLE);

	return true;
}
bool ModuleScene::CleanUp() {



	return true;
}

update_status ModuleScene::PreUpdate(float dt) {



	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt) {



	return UPDATE_CONTINUE;
}
update_status ModuleScene::PostUpdate(float dt) {



	return UPDATE_CONTINUE;
}

Gameobject * ModuleScene::GetSceneGameObjcet()
{
	return scene;
}
