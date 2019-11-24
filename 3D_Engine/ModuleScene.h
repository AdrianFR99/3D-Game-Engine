#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"

class Camera3D;
class Tree;

class ModuleScene :
	public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Init();
	bool Start();
	bool CleanUp();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	
	Gameobject* GetSceneGameObjcet();

public:

	Tree*SceneTree = nullptr;

	Gameobject* scene=nullptr;
	Gameobject* Test=nullptr;

};




#endif//__MODULESCENE_H__
