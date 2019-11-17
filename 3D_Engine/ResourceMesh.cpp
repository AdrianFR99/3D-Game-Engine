#include "ResourceMesh.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

ResourceMesh::ResourceMesh(std::string unique_id) : Resource(unique_id, RT_MESH)
{
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

