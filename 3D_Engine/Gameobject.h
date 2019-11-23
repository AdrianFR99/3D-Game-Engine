#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Globals.h"
#include "Component.h"
#include "MathGeoLib/include/Geometry/AABB.h"
#include "MathGeoLib/include/Geometry/OBB.h"

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

	// Transform operations
	void UpdateGlobalTransform();

	//AABBs&OBB
	void SetBBOs();
	void UpdateBBOs();

	void DrawOBB_Box();


	const AABB GetAABB()const;

	//parent
	//children
public:
	
	//Components booleans
	bool hasTransform = false;
	bool hasCamera = false;
	bool hasMaterial = false;
	bool hasMesh=false;


	bool active = false;
	

	bool DrawGO=true;
	//AABBs&OBB booleans
	bool DrawBBOs = true;
	bool DrawAABB = true;
	bool DrawOBB = true;

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
	OBB obb;
	AABB def;
	AABB aabb;
	
	


	std::vector<Gameobject*> GameObject_Child_Vec;

	bool toDelete = false;
	bool UpdateTransform = false;
};



#endif //__GAMEOBJECT_H__
