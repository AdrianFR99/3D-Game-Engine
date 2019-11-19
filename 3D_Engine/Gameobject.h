#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Globals.h"
#include "Component.h"
#include "MathGeoLib/include/Geometry/AABB.h"

#include <string>
//#include "ComponentTransform.h"
//#include "ComponentMesh.h"
//#include "ComponentMaterial.h"

class Component;
class ComponentTransform;
class ComponentMesh;
class ComponentMaterial;
class ComponentCamera;

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


public:
	//create component
	void CreateComponent(Gameobject * object, CompType tocreate, bool active);


	void SetOBBToNegativeInf();
	void SetOBBtoGlobalTrans();

	void DrawOBB_Box();

	// Transform operations
	void UpdateGlobalTransform();

	//parent
	//children

	bool active = false;
	std::string nameGameObject ;
	uint ID = 0;
	//camera
	float CameraDistance = 0.0f;
	float xPos = 1.0f;
	float yPos = 1.0f;
	float zPos = 1.0f;
	//list of components inside
	std::vector<Component*> ComponentList;

	//list of child
	/*std::vector<Gameobjects*> ChildGameobjects;*/

	Gameobject* Father = nullptr;

	ComponentTransform* transformPointer = nullptr;
	ComponentMesh* meshPointer = nullptr;
	ComponentMaterial* materialPointer = nullptr;
	ComponentCamera*CameraPointer = nullptr;


	//BoundingBox GameObjext
	AABB*obbGameObject;




	std::vector<Gameobject*> GameObject_Child_Vec;

	bool toDelete = false;
	bool UpdateTransform = false;
};



#endif //__GAMEOBJECT_H__
