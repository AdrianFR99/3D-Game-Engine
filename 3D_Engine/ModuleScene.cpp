#include "Application.h"
#include "ModuleScene.h"
#include "ModuleAssets.h"


ModuleScene::ModuleScene(Application* app, bool start_enabled):Module(app, start_enabled)
{
}


ModuleScene::~ModuleScene()
{
}


bool ModuleScene::Init() {

	//CreatePrimitive();



	return true;
}
bool ModuleScene::Start() {

	App->Assets->CreatePrimitive(Primitive_Type::CUBE);
	//App->Assets->LoadFiles(App->AssetModel.data());
	
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

