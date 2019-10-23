#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Globals.h"
#include "Component.h"
#include<vector>

enum CompType;
class Component;

class Gameobject
{
public:

	Gameobject(int id);
	virtual ~Gameobject();

public:

	void Update();
	void Enable();
	void Disable();
	void Cleanup();

	//create component
	void CreateComponent(Gameobject * object, CompType tocreate, bool active);

	
	//parent
	//chield

	bool active = false;
	char* nameGameObject = nullptr;
	int ID = 0;

	//list of components inside
	std::vector<Component*> ComponentList;

	//list of child
	/*std::vector<Gameobjects*> ChildGameobjects;

	Gameobjects* Father;*/

};



#endif //__GAMEOBJECT_H__