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
	if (mesh_asset != nullptr)
	{
		ret = mesh_asset->VBO;
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
	if (mesh_asset != nullptr)
	{
		ret = mesh_asset->num_vertex;
	}
	else {
		ret = Primitives_Vec->num_vertex;
	}
	return ret;
	
}

uint ResourceMesh::GetIdIndices()
{
	uint ret;
	if (mesh_asset != nullptr)
	{
		ret = mesh_asset->IBO;
	}
	else {
		ret = Primitives_Vec->IBO;
	}
	return ret;
	
}

uint ResourceMesh::GetNumIndices()
{
	uint ret;
	if (mesh_asset != nullptr)
	{
		ret = mesh_asset->num_index;
	}
	else {
		ret = Primitives_Vec->num_index;
	}
	return ret;
	
}

float3 * ResourceMesh::GetVertices()
{
	float3* ret;
	if (mesh_asset != nullptr)
	{
		ret = mesh_asset->vertices;
	}
	else {
		ret = Primitives_Vec->vertices;
	}
	return ret;
}

uint ResourceMesh::GetNumNormal()
{
	uint ret;
	if (mesh_asset != nullptr)
	{
		ret = mesh_asset->num_normals;
	}
	else {
		ret = Primitives_Vec->num_normals;
	}
	return ret;
}

uint ResourceMesh::GetNumNormalFaces()
{
	uint ret;
	if (mesh_asset != nullptr)
	{
		ret = mesh_asset->num_normals_faces;
	}
	else {
		ret = Primitives_Vec->num_normals_faces;
	}
	return ret;
	
}

uint * ResourceMesh::GetIndices()
{
	uint* ret;
	if (mesh_asset != nullptr)
	{
		ret = mesh_asset->indices;
	}
	else {
		ret = Primitives_Vec->indices;
	}
	return ret;
}

void ResourceMesh::SetFaces(float * _vertices, uint _num_vertices, uint * _indices, uint _num_indices)
{
	if (_num_vertices > 0)
	{
		// Vertices
		mesh_asset->vertices = new float3[_num_vertices * 3];
		memcpy(mesh_asset->vertices, _vertices, sizeof(float) * _num_vertices * 3);
		mesh_asset->num_vertex = _num_vertices;

		if (_num_indices > 0)
		{
			// Indices
			mesh_asset->indices = new uint[_num_indices];
			memcpy(mesh_asset->indices, _indices, sizeof(uint) * _num_indices);
			mesh_asset->num_index = _num_indices;
		}

	
	}
}

void ResourceMesh::SetUvs(float * _uvs, uint _num_uvs)
{
	if (_num_uvs > 0)
	{
		// UVs
		mesh_asset->uv_coord = new float[_num_uvs * 3];
		memcpy(mesh_asset->uv_coord, _uvs, sizeof(float) * _num_uvs * 3);
		mesh_asset->num_uv = _num_uvs;
	}
}