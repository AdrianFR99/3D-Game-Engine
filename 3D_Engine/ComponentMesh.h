#ifndef __COMPONENTMESH_H__
#define __COMPONENTMESH_H__

#include "Component.h"
#include "AssetMesh.h"

class Gameobject;
class AssetMesh;
class Primitives;

class ComponentMesh : public Component
{
public:
	ComponentMesh(Gameobject* owner,CompType newtype);
	virtual ~ComponentMesh();

	void Init();
	void Update();
	void Cleanup();
	void Draw();
	void Enable();
	void Disable();

	
	//list of Meshes
	std::vector<AssetMesh*> Meshes_Vec;

	//list of Primitives
	std::vector<Primitives*> Primitives_Vec;
private:
	

};

#endif // COMPONENTMESH