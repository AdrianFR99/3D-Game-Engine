#include "Application.h"
#include "ModuleScene.h"
#include "ModuleAssets.h"
#include "ModuleCamera3D.h"
#include "ModuleGameObject.h"

#include "mmgr/mmgr.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled):Module(app, start_enabled)
{
}


ModuleScene::~ModuleScene()
{
}


bool ModuleScene::Init() {

	

	scene = App->Gameobjects->CreateFatherGameObject();


	Test = App->Gameobjects->CreateGameObject();
	Test->CreateComponent(Test,CompType::CAMERA,true);
	Test->nameGameObject = "camera";
	Test->Father = scene;
	scene->GameObject_Child_Vec.push_back(Test);

	return true;
}

bool ModuleScene::Start() {

//primitves must Load AFTER FBX
	App->Assets->LoadFiles(App->AssetModel.data());
	

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
