#ifndef __COMPONENT_H__
#define  __COMPONENT_H__

#include "Gameobject.h"

class Gameobject;

enum class CompType
{
	TRANSFORM,
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
	virtual void Cleanup() {};

	void Enable();
	void Disable();



private:
	//vars
	bool active = false;
	Gameobject* belongsTo = nullptr;
	CompType type;
	char* nameComponent = nullptr;

};


#endif