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
	void CleanUp();
	void Draw();
	void Enable();
	void Disable();
	void NormalDisplay(bool faces, bool vertex);
	
	//list of Meshes
	std::vector<AssetMesh*> Meshes_Vec;
	//list of Primitives
	std::vector<Primitives*> Primitives_Vec;

	bool normalsDrawFaces = false;
	bool normalsDrawVertex = false;

private:
	

};

#endif // COMPONENTMESH