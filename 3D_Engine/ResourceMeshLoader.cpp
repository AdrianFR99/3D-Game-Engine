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


bool ResourceMeshLoader::ResourceIsUsed(int index, ResourceType type, Resource*& res)
{
	bool ret = false;

	for (std::vector<UsedResource>::iterator it = used_resources.begin(); it != used_resources.end(); it++)
	{
		if ((*it).GetIndex() == index && (*it).GetType() == type)
		{
			res = (*it).GetResource();
			ret = true;
			break;
		}
	}

	return ret;
}

void ResourceMeshLoader::AddResource(int index, ResourceType type, Resource * res)
{
	UsedResource used(res, index, type);
	used_resources.push_back(used);
}


void ResourceMeshLoader::Unload(const char * filepath)
{
	/*string path = App->fs->GetPathFromFilePath(filepath);
	string filename = App->fs->GetFileNameFromFilePath(filepath);
	string extension = App->fs->GetFileExtension(filename.c_str());
	string name = App->fs->GetFilenameWithoutExtension(filename.c_str(), false);

	string meta_path = path + filename + ".meta";
	string prefab_path = path + filename + ".prefab";

	JSON_Doc* meta = App->json->LoadJSON(meta_path.c_str());

	if (meta != nullptr)
	{
		int resources_count = meta->GetArrayCount("resources");

		for (int i = 0; i < resources_count; i++)
		{
			string res_uid = meta->GetStringFromArray("resources", i);

			string resource_path = App->fs->GetLibraryTexturePath() + res_uid + ".sustomesh";
			string resource_meta_path = App->fs->GetLibraryTexturePath() + res_uid + ".meta";

			App->gameobj->DeleteGameObjectsUsingResource(App->RS->Get(res_uid));

			App->fs->FileDelete(resource_path.c_str());
			App->fs->FileDelete(resource_meta_path.c_str());
		}
	}

	App->fs->FileDelete(meta_path.c_str());
	App->fs->FileDelete(prefab_path.c_str());
	App->fs->FileDelete(filepath);*/
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