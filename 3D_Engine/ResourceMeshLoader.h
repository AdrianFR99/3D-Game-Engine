 #ifndef __RESOURCE_MESH_LOADER_H__
#define __RESOURCE_MESH_LOADER_H__

#include "Assimp\include\DefaultLogger.hpp"
#include "Assimp\include\scene.h"
#include "Maths.h"
#include <string>
#include "Globals.h"
#include "Resource.h"

class ResourceMesh;
class Gameobject;

//used
class ResourceMeshLoader
{
public:
	ResourceMeshLoader();
	virtual ~ResourceMeshLoader();

	//void Unload(const char* filepath);
	//bool Import(const ImportData& IData) const ;

	void Save(ResourceMesh * mesh, const char * path) const;

private:
	//bool ResourceIsUsed(int index, Resource::ResourceType type, Resource*& res);

	//void AddResource(int index, Resource::ResourceType type, Resource* res);


private:
	
};

//used
struct ImportMeshData : public ImportData
{
	aiMesh* mesh = nullptr;
	ResourceMesh* new_mesh = nullptr;
};

class ImporterMesh 
{

public:
	ImporterMesh();
	virtual ~ImporterMesh();


	
};
#endif