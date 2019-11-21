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


bool ResourceMeshLoader::Export(const char * path, ResourceMesh* mesh)
{
	bool ret = true;

	std::string name = mesh->GetUniqueId();

	// -------------------------------------
	// FILE --------------------------------
	// -------------------------------------
	uint ranges[3] = { mesh->GetNumVertices(), mesh->GetNumIndices()};
	uint size = sizeof(ranges) +
		sizeof(uint) * mesh->GetNumIndices() +
		sizeof(float) * mesh->GetNumVertices() * 3;
		

	// Allocate data
	char* data = new char[size];
	char* cursor = data;

	// Store ranges
	uint bytes = sizeof(ranges);
	memcpy(cursor, ranges, bytes);
	cursor += bytes;

	// Store indices
	bytes = sizeof(uint) * mesh->GetNumIndices();
	memcpy(cursor, mesh->GetIndices(), bytes);
	cursor += bytes;

	// Store vertices
	bytes = sizeof(float) * mesh->GetNumVertices() * 3;
	memcpy(cursor, mesh->GetVertices(), bytes);
	cursor += bytes;


	//fopen
	if (App->fs->FileSave(path, data, name.c_str(), "GearMesh", size) == false)
	{
		return false;
	}

	RELEASE_ARRAY(data);

	// -------------------------------------
	// META --------------------------------
	// -------------------------------------
	std::string meta_name = path + name + ".meta";

	/*nlohmann::json* doc = App.->LoadJSON(meta_name.c_str());
	if (doc == nullptr)
		doc = App->json->CreateJSON(meta_name.c_str());

	if (doc != nullptr)
	{
		doc->Clear();

		doc->SetString("uid", mesh->GetUniqueId().c_str());
		doc->SetString("name", mesh->GetFileName().c_str());

		doc->Save();
	}

	App->json->UnloadJSON(doc);*/

	return ret;
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
