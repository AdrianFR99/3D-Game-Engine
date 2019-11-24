#include "ResourceMeshLoader.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ModuleCamera3D.h"
#include "ResourceManager.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "Globals.h"
#include "GameObject.h"
#include "ModuleFileSystem.h"
#include "JSONLoader.h"
#include "Assimp\include\cimport.h"
#include "Assimp\include\postprocess.h"
#include "Assimp\include\cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")


ResourceMeshLoader::ResourceMeshLoader()
{
}

ResourceMeshLoader::~ResourceMeshLoader()
{
}

void ResourceMeshLoader::Load(const char * filename, ResourceMesh & mesh) const
{

//	mesh.SetOriginalFilename(filename);

	// --- Load mesh data ---
	char* buffer;
	App->FileSystem->Load(filename, &buffer);
	char* cursor = buffer;

	// amount of indices / vertices / normals / texture_coords
	uint ranges[5];
	uint bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);

	mesh.mesh_asset->num_index = ranges[0];
	mesh.mesh_asset->num_vertex = ranges[1];
	mesh.mesh_asset->num_normals = ranges[2];
	mesh.mesh_asset->num_normals_faces = ranges[3];
	mesh.mesh_asset->num_uv = ranges[4];

	// --- Load indices ---
	cursor += bytes;
	bytes = sizeof(uint) * mesh.mesh_asset->num_index;
	mesh.mesh_asset->indices = new uint[mesh.mesh_asset->num_index];
	memcpy(mesh.mesh_asset->indices, cursor, bytes);

	//mesh.Meshes_Vec->IBO = App->renderer3D->CreateBufferFromData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh.Meshes_Vec->num_index, mesh.Meshes_Vec->indices);

	// --- Load Vertices ---
	cursor += bytes;
	bytes = sizeof(float) * 3 * mesh.mesh_asset->num_vertex;
	mesh.mesh_asset->vertices = new float3[mesh.mesh_asset->num_vertex];
	memcpy(mesh.mesh_asset->vertices, cursor, bytes);

	//mesh.Meshes_Vec->VBO = App->renderer3D->CreateBufferFromData(GL_ARRAY_BUFFER, sizeof(float3) * mesh.Meshes_Vec->num_vertex, mesh.Meshes_Vec->vertices);

	// --- Load Normals ---
	cursor += bytes;
	bytes = sizeof(float) * 3 * mesh.mesh_asset->num_normals;
	mesh.mesh_asset->normals = new float3[mesh.mesh_asset->num_normals];
	memcpy(mesh.mesh_asset->normals, cursor, bytes);

	// --- Load Normals Faces ---
	cursor += bytes;
	bytes = sizeof(float) * 3 * mesh.mesh_asset->num_normals_faces;
	mesh.mesh_asset->normals_faces = new float3[mesh.mesh_asset->num_normals_faces];
	memcpy(mesh.mesh_asset->normals_faces, cursor, bytes);

	// --- uVs ---
	cursor += bytes;
	bytes = sizeof(float) * 3 * mesh.mesh_asset->num_uv;
	mesh.mesh_asset->uv_coord = new float[mesh.mesh_asset->num_uv*3];
	memcpy(mesh.mesh_asset->uv_coord, cursor, bytes);

	//mesh.Meshes_Vec->UVC = App->renderer3D->CreateBufferFromData(GL_ARRAY_BUFFER, sizeof(float) * mesh.TexCoordsSize, mesh.TexCoords);
	mesh.mesh_asset->ToBuffer();
	// --- Delete buffer data ---
	if (buffer)
	{
		delete[] buffer;
		buffer = nullptr;
		cursor = nullptr;
	}

	
}




void ResourceMeshLoader::Save(ResourceMesh * mesh, const char* path) const
{
	//

	//

	// amount of indices / vertices / normals /noraml faces/ uvs / 
	uint ranges[5] = { mesh->GetNumIndices(), mesh->GetNumVertices(), mesh->GetNumNormal(), mesh->GetNumNormalFaces(), mesh->mesh_asset->num_uv };

	uint size = sizeof(ranges) + sizeof(uint) * mesh->GetNumIndices() + sizeof(float3) * mesh->GetNumVertices() + sizeof(float3)*mesh->GetNumNormal() + sizeof(float)* mesh->GetNumNormalFaces() + sizeof(float3) * mesh->mesh_asset->num_uv;

	char* data = new char[size]; // Allocate
	char* cursor = data;

	uint bytes = sizeof(ranges); // First store ranges
	memcpy(cursor, ranges, bytes);

	// --- Store Indices ---
	cursor += bytes;
	bytes = sizeof(uint) * mesh->GetNumIndices();
	memcpy(cursor, mesh->mesh_asset->indices, bytes);

	// --- Store Vertices ---
	cursor += bytes;
	bytes = sizeof(float3) * mesh->GetNumVertices();
	memcpy(cursor, mesh->mesh_asset->vertices, bytes);

	// --- Store Normals ---
	cursor += bytes;
	bytes = sizeof(float3) * mesh->GetNumNormal();
	memcpy(cursor, mesh->mesh_asset->normals, bytes);

	// --- Store Normal Faces ---
	cursor += bytes;
	bytes = sizeof(uint) * mesh->GetNumNormalFaces();
	memcpy(cursor, mesh->mesh_asset->normals_faces, bytes);

	// Store UVs
	cursor += bytes;
	bytes = sizeof(float) *3*mesh->mesh_asset->num_uv;
	memcpy(cursor, mesh->mesh_asset->uv_coord, bytes);


	App->FileSystem->Save(path, data, size);

	// --- Delete buffer data ---
	if (data)
	{
		delete[] data;
		data = nullptr;
		cursor = nullptr;
	}
}

ImporterMesh::ImporterMesh()
{
}

ImporterMesh::~ImporterMesh()
{
}


