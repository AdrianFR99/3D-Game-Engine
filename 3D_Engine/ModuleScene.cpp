#include "Application.h"
#include "ModuleScene.h"



ModuleScene::ModuleScene(Application* app, bool start_enabled):Module(app, start_enabled)
{
}


ModuleScene::~ModuleScene()
{
}


bool ModuleScene::Init() {





	return true;
}
bool ModuleScene::Start() {



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

