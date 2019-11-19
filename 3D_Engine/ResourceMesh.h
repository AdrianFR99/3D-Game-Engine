#ifndef __RESOURCE_MESH_H__
#define __RESOURCE_MESH_H__

#include "Resource.h"
//#include "ResourceTexture.h"
#include "Globals.h"
#include "Primitives.h"
#include "AssetMesh.h"

class AssetMesh;
class ResourceTexture;

class ResourceMesh : public Resource
{
public:
	ResourceMesh(std::string unique_id);
	virtual ~ResourceMesh();

	void CleanUp();

	void Render();

	AssetMesh* Meshes_Vec = nullptr;;
	
	Primitives* Primitives_Vec = nullptr;

	
	ResourceTexture* Default_texture = nullptr;
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