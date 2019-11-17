#include "ResourceManager.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "ResourceMeshLoader.h"
#include "ResourceTextureLoader.h"
#include "Globals.h"


ResourceManager::ResourceManager(Application* app, bool start_enabled):Module( app,start_enabled)
{
	mesh_loader = new ResourceMeshLoader();
	texture_loader = new ResourceTextureLoader();
}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::Start()
{
	bool ret = true;

	std::string new_n;
	//bool f = App->fs->CheckNameCollision("D:\documentos\GitHub\3D-Game-Engine\3D_Engine\Game\SettingConfig.json", new_n);

	return ret;
}

bool ResourceManager::CleanUp()
{
	bool ret = true;

	DeleteAllResources();

	RELEASE(mesh_loader);
	RELEASE(texture_loader);

	return ret;
}

Resource * ResourceManager::Get(std::string _unique_id)
{
	std::map<std::string, Resource*>::iterator it = resources.find(_unique_id);

	if (it != resources.end())
		return it->second;

	return nullptr;
}

Resource * ResourceManager::CreateNewResource(ResourceType type, std::string _unique_id)
{
	std::string new_id;

	if (_unique_id == "")
		new_id = GetNewUID();
	else
		new_id = _unique_id;

	Resource* res = Get(_unique_id);

	if (res == nullptr)
	{
		switch (type)
		{
		case ResourceType::RT_MESH:
			res = new ResourceMesh(new_id);
			break;
		case ResourceType::RT_TEXTURE:
			res = new ResourceTexture(new_id);
			break;
		
		}

		if (res != nullptr)
		{
			resources[new_id] = res;
		}
	}

	return res;
}

void ResourceManager::DeleteResource(std::string unique_id)
{
	std::map<std::string, Resource*>::iterator it = resources.find(unique_id);

	if (it != resources.end())
	{
		it->second->CleanUp();
		RELEASE(it->second);
		resources.erase(it);
	}
}

void ResourceManager::SaveResourceIntoFile(Resource * res)
{
	if (res != nullptr)
	{
		switch (res->GetType())
		{
		case ResourceType::RT_MESH:
			mesh_loader->Export(App->fs->GetLibraryMeshPath().c_str(), (ResourceMesh*)res);
			break;
		case ResourceType::RT_TEXTURE:
			texture_loader->Export(App->fs->GetLibraryTexturePath().c_str(), (ResourceTexture*)res);
			break;
		
		}
	}
}

bool ResourceManager::LoadResource(const char * file_path)
{
	std::vector<Resource*> resources;
	return LoadResource(file_path, resources);
}

bool ResourceManager::LoadResource(const char * file_path, std::vector<Resource*>& resources)
{
	bool ret = false;

	resources.clear();

	std::string name = App->fs->GetFileNameFromFilePath(file_path);
	std::string extension = App->fs->ToLowerCase(App->fs->GetFileExtension(name.c_str()));

	bool valid_extension = false;

	if (App->fs->TextCmp("fbx", extension.c_str()))
	{
		ret = mesh_loader->Load(file_path, resources, true);
		valid_extension = true;
	}
	else if (App->fs->TextCmp("png", extension.c_str()) || App->fs->TextCmp("dds", extension.c_str()) || App->fs->TextCmp("tga", extension.c_str()))
	{
		ret = texture_loader->Load(file_path, resources);
	}

	if (ret)
	{
		App->fs->FileCopyPaste(file_path, App->fs->GetAssetsPath().c_str());

		// Save meta file ---------------------------
		std::string uid = GetNewUID();
		std::string json_name = App->fs->GetAssetsPath() + name + ".meta";
		//nlohmann::json meta = JsonLoader.Save CreateJSON(json_name.c_str());
		nlohmann::json meta;
		JsonLoader.Save(json_name.data(),meta);

		if (meta)
		{
			meta->SetString("uid", uid.c_str());

			meta->SetArray("resources");
			for (std::vector<Resource*>::iterator res = resources.begin(); res != resources.end(); ++res)
			{
				meta->AddStringToArray("resources", (*res)->GetUniqueId().c_str());
			}

			meta->Save();
		}

	}

	return ret;
}

void ResourceManager::ImportAllResources()
{
	mesh_loader->ImportAllMeshes();
	texture_loader->ImportAllTextures();
}

void ResourceManager::LoadFileIntoScene(const char * file_path)
{
	std::string name = App->fs->GetFileNameFromFilePath(file_path);
	std::string extension = App->fs->ToLowerCase(App->fs->GetFileExtension(name.c_str()));

	if (App->fs->TextCmp("fbx", extension.c_str()))
	{
		mesh_loader->LoadIntoScene(file_path);
	}
	else if (App->fs->TextCmp("png", extension.c_str()) || App->fs->TextCmp("dds", extension.c_str()) || App->fs->TextCmp("tga", extension.c_str()))
	{

	}
}

void ResourceManager::DeImportFile(const char * file_path)
{
	std::string name = App->fs->GetFileNameFromFilePath(file_path);
	std::string extension = App->fs->ToLowerCase(App->fs->GetFileExtension(name.c_str()));

	if (App->fs->TextCmp("fbx", extension.c_str()))
	{
		mesh_loader->Unload(file_path);
	}
	else if (App->fs->TextCmp("png", extension.c_str()) || App->fs->TextCmp("dds", extension.c_str()) || App->fs->TextCmp("tga", extension.c_str()))
	{
		texture_loader->Unload(file_path);
	}
}

ResourceMeshLoader * ResourceManager::GetMeshLoader()
{
	return mesh_loader;
}

ResourceTextureLoader * ResourceManager::GetTextureLoader()
{
	return texture_loader;
}

std::string ResourceManager::GetNewUID()
{
	return GetUIDRandomHexadecimal();
}

void ResourceManager::OnLoadFile(const char * file_path, const char * file_name, const char * file_extension)
{
	LoadResource(file_path);
}

void ResourceManager::DeleteAllResources()
{
	for (std::map<std::string, Resource*>::iterator it = resources.begin(); it != resources.end();)
	{
		(*it).second->CleanUp();
		RELEASE(it->second);
		it = resources.erase(it);
	}
}
