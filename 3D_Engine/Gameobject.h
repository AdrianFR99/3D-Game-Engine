#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__


//#include "Component.h"


class Gameobject
{
puclic:

	Gameobject{};
	virtual ~Gameobject{};

private:

	void Update();
	void Enable();
	void Disable();
	void Cleanup();

	//create component

	
	//parent
	//chield

	bool active = false;
	std::string name;
	int ID = 0;




}



#endif //__GAMEOBJECT_H__