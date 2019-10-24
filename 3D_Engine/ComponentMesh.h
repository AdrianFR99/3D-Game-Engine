#ifndef __COMPONENTMESH_H__
#define __COMPONENTMESH_H__

#include "Component.h"
#include "AssetMesh.h"

class Gameobject;
class AssetMesh;

class ComponentMesh : public Component
{
public:
	ComponentMesh(Gameobject* owner,CompType newtype);
	virtual ~ComponentMesh();

	void Init();
	void Update();
	void CleanUp();
	void Draw();
	void Enable();
	void Disable();

	
	//list of Meshes
	std::vector<AssetMesh*> Meshes_Vec;
private:
	

};

#endif // COMPONENTMESH