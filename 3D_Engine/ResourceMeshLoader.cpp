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






void ResourceMeshLoader::Save(ResourceMesh * mesh, const char* path) const
{
	//

	//

	// amount of indices / vertices / normals / texture_coords / AABB
	uint ranges[4] = { mesh->GetNumIndices(), mesh->GetNumVertices(), mesh->GetNumNormal(), mesh->GetNumNormalFaces()  };

	uint size = sizeof(ranges) + sizeof(uint) * mesh->GetNumIndices() + sizeof(float3) * mesh->GetNumVertices() + sizeof(float3)*mesh->GetNumNormal() + sizeof(float)* mesh->GetNumNormalFaces();

	char* data = new char[size]; // Allocate
	char* cursor = data;

	uint bytes = sizeof(ranges); // First store ranges
	memcpy(cursor, ranges, bytes);

	// --- Store Indices ---
	cursor += bytes;
	bytes = sizeof(uint) * mesh->GetNumIndices();
	memcpy(cursor, mesh->Meshes_Vec->indices, bytes);

	// --- Store Vertices ---
	cursor += bytes;
	bytes = sizeof(float3) * mesh->GetNumVertices();
	memcpy(cursor, mesh->Meshes_Vec->vertices, bytes);

	// --- Store Normals ---
	cursor += bytes;
	bytes = sizeof(float3) * mesh->GetNumNormal();
	memcpy(cursor, mesh->Meshes_Vec->normals, bytes);

	// --- Store Normal Faces ---
	cursor += bytes;
	bytes = sizeof(uint) * mesh->GetNumNormalFaces();
	memcpy(cursor, mesh->Meshes_Vec->normals_faces, bytes);

	App->fs->Save(path, data, size);

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


