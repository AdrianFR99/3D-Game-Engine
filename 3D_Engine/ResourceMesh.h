#ifndef __RESOURCE_MESH_H__
#define __RESOURCE_MESH_H__

#include "Resource.h"
#include "ModuleAssets.h"
#include "Globals.h"
#include "Maths.h"
#include "Gameobject.h"
//#include "Primitives.h"
#include "AssetMesh.h"

class AssetMesh;

struct Material {

	std::string path;
	Texture_Type type;
};

class ResourceMesh : public Resource
{
public:
	ResourceMesh(std::string unique_id);
	virtual ~ResourceMesh();

	void CleanUp();

	void Render();

	AssetMesh* Meshes_Vec;
	
	//Primitives Primitives_Vec;

	Material Comp_Material;
private:
	
	std::string nameMesh;

	void LoadToMemory();
	void UnloadFromMemory();

	

private:
	uint DiffuseID;
	uint currentID;
	uint CheckeredID;



};

#endif