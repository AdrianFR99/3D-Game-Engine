#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"

class Camera3D;


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

	Camera3D*test=nullptr;


};




#endif//__MODULESCENE_H__