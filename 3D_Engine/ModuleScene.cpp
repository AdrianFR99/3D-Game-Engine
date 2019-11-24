#include "Application.h"
#include "ModuleScene.h"
#include "ModuleAssets.h"
#include "ModuleCamera3D.h"
#include "ModuleGameObject.h"
#include "Tree.h"

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


	SceneTree = new Tree(AABB({ -50, -30.f, -50.f }, { 50.f, 30.f, 50.f }),TreeType::QUAT_TREE,3);



	for (int i = 0; i < App->Gameobjects->GameobjectList.size(); ++i) {
		if (App->Gameobjects->GameobjectList[i]->Static == true)
			SceneTree->Insert(App->Gameobjects->GameobjectList[i]);

	}


	return true;
}
bool ModuleScene::CleanUp() {

	RELEASE(SceneTree);

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
