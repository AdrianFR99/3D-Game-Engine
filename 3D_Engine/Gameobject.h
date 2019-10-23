#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__


#include "Component.h"


class Gameobject
{
public:

	Gameobject(int id);
	virtual ~Gameobject();

private:

	void Update();
	void Enable();
	void Disable();
	void Cleanup();

	//create component

	
	//parent
	//chield

	bool active = false;
	char* nameGameObject = nullptr;
	int ID = 0;




};



#endif //__GAMEOBJECT_H__