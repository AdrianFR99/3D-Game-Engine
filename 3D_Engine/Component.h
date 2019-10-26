#ifndef __COMPONENT_H__
#define  __COMPONENT_H__

#include "Gameobject.h"

class Gameobject;

enum CompType
{
	TRANSFORM=0,
	MESH,
	MATERIAL,
	LIGHT
};


class Component 
{
public:
	Component(CompType intype, Gameobject* owner);
	virtual ~Component();

	virtual void Init() {};
	virtual void Update() {};
	virtual void CleanUp() {};
	virtual void Draw() {};
	void Enable();
	void Disable();


	//vars
	bool active = false;
	Gameobject* belongsTo = nullptr;
	CompType type;
	char* nameComponent = nullptr;

private:

};


#endif