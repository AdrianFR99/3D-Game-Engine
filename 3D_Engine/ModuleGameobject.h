#ifndef __MODULEGAMEOBJECT_H__
#define __MODULEGAMEOBJECT_H__

#include "Module.h"
#include "Gameobject.h"
#include "Component.h"
#include<vector>


class Gameobject;
class Components;

class ModuleGameobject : public Module
{
public:

	ModuleGameobject(Application* app, bool start_enabled = true);

	virtual ~ModuleGameobject();
	
	
	bool Init();
	bool Start();
	void Draw();
	bool CleanUp();
	
	Gameobject* CreateGameObject();

	bool LoadFiles(const char* path);

	int id = 0;

	std::vector<Gameobject*> GameobjectList;

	
};




#endif //__MODULEGAMEOBJECT_H__