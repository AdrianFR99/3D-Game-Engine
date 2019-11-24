#include "Application.h"
#include "ModuleScene.h"
#include "ModuleAssets.h"
#include "ModuleCamera3D.h"
#include "ModuleGameObject.h"
#include "ModuleLoaderControl.h"
#include "ResourceSceneLoader.h"

#include "mmgr/mmgr.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled):Module(app, start_enabled)
{
}


ModuleScene::~ModuleScene()
{
}


bool ModuleScene::Init(nlohmann::json config) {



	scene = App->Gameobject->CreateFatherGameObject();


	Test = App->Gameobject->CreateGameObject();
	Test->CreateComponent(Test,CompType::CAMERA,true);
	Test->nameGameObject = "camera";
	Test->aabb.SetFrom(AABB(Test->transformPointer->GetPosition() - float3::one, Test->transformPointer->GetPosition() + float3::one));
	Test->Father = scene;
	scene->GameObject_Child_Vec.push_back(Test);

	return true;
}

bool ModuleScene::Start() {

//primitves must Load AFTER FBX
	App->Assets->LoadFiles(App->AssetModel.data());


	SceneTree = new Tree(AABB({ -50, -30.f, -50.f }, { 50.f, 30.f, 50.f }),TreeType::QUAT_TREE,3);



	for (int i = 0; i < App->Gameobject->GameobjectList.size(); ++i) {
		if (App->Gameobject->GameobjectList[i]->Static == true)
			SceneTree->Insert(App->Gameobject->GameobjectList[i]);

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

void ModuleScene::SaveScene()
{
	if (scene->GameObject_Child_Vec.size() != 0)
	{
		std::string Scene_name = "Scene";
		App->importer->GetImporterScene()->SaveSceneToFile(scene->GameObject_Child_Vec, Scene_name, SCENE);

	}
}
