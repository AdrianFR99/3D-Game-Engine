#ifndef __COMPONENTMESH_H__
#define __COMPONENTMESH_H__

#include "Component.h"

class Gameobject;

class ComponentMesh : public Component
{
public:
	ComponentMesh(Gameobject* owner,CompType newtype);
	virtual ~ComponentMesh();

	void Init();
	void Update();
	void CleanUp();

	void Enable();
	void Disable();


private:
	

};

#endif // COMPONENTMESH