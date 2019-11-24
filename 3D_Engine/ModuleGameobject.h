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
	
	
	bool Init(nlohmann::json config);
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	void Draw();
	bool CleanUp();
	
	void ChangeParenting(Gameobject* to_change, Gameobject* new_father);
	void SetToDestroy(Gameobject* object);
	void RecursiveDestruction(Gameobject* object);
	Gameobject* CreateGameObject();
	Gameobject* CreateFatherGameObject();
	Gameobject* CreateEmpty();

	bool LoadFiles(const char* path);

	Gameobject * CreateEmptyFatherLess();

	int id = 0;

	std::vector<Gameobject*> GameobjectList;


	
};




#endif //__MODULEGAMEOBJECT_H__