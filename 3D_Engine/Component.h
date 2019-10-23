#ifndef __COMPONENT_H__
#define  __COMPONENT_H__

#include "Gameobject.h"

enum class CompType
{
	TRANSFORM,
	MESH,
	MATERIAL,
	LIGHT 
}


class Component
{
public:
	Component{}
	virtual ~Component{};

	virtual void Init() {};
	virtual void Update() {};
	virtual void Cleanup() {};

	void Enable();
	void Disable();



private:
	//vars
	boo active = false;
	Gameobject* belongsTo = nullptr;
	CompType type;
	sttd::string name;

}


#endif