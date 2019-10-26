#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Globals.h"
#include "Component.h"

//#include "ComponentTransform.h"
//#include "ComponentMesh.h"
//#include "ComponentMaterial.h"

class Component;
class ComponentTransform;
class ComponentMesh;
class ComponentMaterial;

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
	void CleanUp();
	void Draw();

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

	ComponentTransform* transformPointer = nullptr;
	ComponentMesh* meshPointer = nullptr;
	ComponentMaterial* materialPointer = nullptr;

};



#endif //__GAMEOBJECT_H__