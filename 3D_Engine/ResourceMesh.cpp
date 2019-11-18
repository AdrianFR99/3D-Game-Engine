#include "ResourceMesh.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

ResourceMesh::ResourceMesh(std::string _unique_id) : Resource(_unique_id, RT_MESH)
{
	/*unique_id = _unique_id;
	type = _type;
	count_ref = 0;*/

}

ResourceMesh::~ResourceMesh()
{
}

void ResourceMesh::CleanUp()
{
	//call module asset clean up
}



void ResourceMesh::Render()
{
	
}

void ResourceMesh::LoadToMemory()
{
	
}

void ResourceMesh::UnloadFromMemory()
{
	
}

