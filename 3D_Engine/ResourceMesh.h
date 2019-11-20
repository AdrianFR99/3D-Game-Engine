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

	void LoadToMemory();
	void UnloadFromMemory();

	uint GetIdVertices();
	uint GetIdIndices();

	uint GetNumVertices();
	uint GetNumIndices();

	uint* GetIndices();
	float3* GetVertices();
	
	
private:
	
	std::string nameMesh;
	AssetMesh* Meshes_Vec = nullptr;;
	Primitives* Primitives_Vec = nullptr;
	ResourceTexture* Default_texture = nullptr;
	
private:

	uint DiffuseID;
	uint currentID;
	uint CheckeredID;

};

#endif