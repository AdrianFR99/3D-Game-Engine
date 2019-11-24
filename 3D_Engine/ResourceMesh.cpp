#include "ResourceMesh.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

ResourceMesh::ResourceMesh(std::string _unique_id) : Resource(_unique_id, Resource::ResourceType::RT_MESH)
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


uint ResourceMesh::GetIdVertices()
{
	uint ret;
	if (Meshes_Vec != nullptr)
	{
		ret = Meshes_Vec->VBO;
	}
	else 
	{
		ret=Primitives_Vec->VBO;
	}
	return ret;
}

uint ResourceMesh::GetNumVertices()
{
	uint ret;
	if (Meshes_Vec != nullptr)
	{
		ret = Meshes_Vec->num_vertex;
	}
	else {
		ret = Primitives_Vec->num_vertex;
	}
	return ret;
	
}

uint ResourceMesh::GetIdIndices()
{
	uint ret;
	if (Meshes_Vec != nullptr)
	{
		ret = Meshes_Vec->IBO;
	}
	else {
		ret = Primitives_Vec->IBO;
	}
	return ret;
	
}

uint ResourceMesh::GetNumIndices()
{
	uint ret;
	if (Meshes_Vec != nullptr)
	{
		ret = Meshes_Vec->num_index;
	}
	else {
		ret = Primitives_Vec->num_index;
	}
	return ret;
	
}

float3 * ResourceMesh::GetVertices()
{
	float3* ret;
	if (Meshes_Vec != nullptr)
	{
		ret = Meshes_Vec->vertices;
	}
	else {
		ret = Primitives_Vec->vertices;
	}
	return ret;
}

uint ResourceMesh::GetNumNormal()
{
	uint ret;
	if (Meshes_Vec != nullptr)
	{
		ret = Meshes_Vec->num_normals;
	}
	else {
		ret = Primitives_Vec->num_normals;
	}
	return ret;
}

uint ResourceMesh::GetNumNormalFaces()
{
	uint ret;
	if (Meshes_Vec != nullptr)
	{
		ret = Meshes_Vec->num_normals_faces;
	}
	else {
		ret = Primitives_Vec->num_normals_faces;
	}
	return ret;
	
}

uint * ResourceMesh::GetIndices()
{
	uint* ret;
	if (Meshes_Vec != nullptr)
	{
		ret = Meshes_Vec->indices;
	}
	else {
		ret = Primitives_Vec->indices;
	}
	return ret;
}

