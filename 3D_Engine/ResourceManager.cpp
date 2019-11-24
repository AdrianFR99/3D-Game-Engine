#include "ResourceManager.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "ModuleLoaderControl.h"
#include "Globals.h"
#include "JSONLoader.h"

#include "ResourceSceneLoader.h"
#include "ResourceTextureLoader.h"

#include "mmgr/mmgr.h"

ResourceManager::ResourceManager(Application* app, bool start_enabled):Module( app,start_enabled)
{
	
}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::Start()
{
	bool ret = true;

	meshLoader = new ResourceMeshLoader;
	std::string new_n;
	

	return ret;
}

bool ResourceManager::CleanUp()
{
	bool ret = true;

	DeleteAllResources();



	return ret;
}

bool ResourceManager::LoadResource(const char * file_path)
{
	std::vector<Resource*> resources;
	return LoadResource(file_path, resources);
}

Resource * ResourceManager::Get(std::string _unique_id)
{
	std::map<std::string, Resource*>::iterator it = resources.find(_unique_id);

	if (it != resources.end())
		return it->second;

	return nullptr;
}

Resource * ResourceManager::CreateNewResource(Resource::ResourceType type, std::string _unique_id )
{
	int random = 0;
	std::string new_id;

	if (_unique_id == "")
	{
		random = GetNewUID();
		new_id = std::to_string(random);
	}
	else
		new_id = _unique_id;

	Resource* res = Get(_unique_id);

	if (res == nullptr)
	{
		switch (type)
		{
		case Resource::ResourceType::RT_MESH:
			res = new ResourceMesh(new_id);
			break;
		case Resource::ResourceType::RT_TEXTURE:
			res = new ResourceTexture(new_id);
			break;
		}
		if (res != nullptr)
		{
				resources[new_id] = res;
		}

		return res;
	}
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
		App->importer->GetImporterScene()->Import(file_path);
	}
	else if (App->fs->TextCmp("png", extension.c_str()) || App->fs->TextCmp("dds", extension.c_str()) || App->fs->TextCmp("tga", extension.c_str()))
	{
		App->importer->GetImporterScene()->ImporterMaterial->import2(file_path);


	}

	

	return ret;
}

int ResourceManager::GetNewUID()
{
	return App->GetRandom().Int();
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
		
		if (it->second != nullptr) 
		  delete it->second;
		it->second = nullptr;
	
		
		it = resources.erase(it);
	}
}

//void ResourceManager::SaveResourceIntoFile(Resource * res)
//{
//	if (res != nullptr)
//	{
//	
//		if (res->GetType() == RT_MESH)
//		{
//			//mesh_loader->Export(App->fs->GetLibraryMeshPath().c_str(), (ResourceMesh*)res);
//
//		}
//			
//		
//	}
//	
//}

void ResourceManager::CreateMetaFromUID(std::string UID, const char* filename)
{
	RMetaData meta;

	std::string jsondata;
	std::string meta_path;
	nlohmann::json jsonmeta;
	char* meta_buffer = nullptr;

	// --- Create Meta ---
	jsonmeta["UID"] = UID;
	jsondata = App->GetJsonLoader()->Serialize(jsonmeta);
	meta_buffer = (char*)jsondata.data();

	meta_path = filename;
	meta_path.append(".meta");

	libraryResources[UID] = meta;
	App->fs->Save(meta_path.data(), meta_buffer, jsondata.length());
}

bool ResourceManager::IsFileImported(const char * file)
{
	bool ret = false;

	std::string path = file;

	path.append(".meta");

	ret = App->fs->Exists(path.data());

	return ret;
}

std::string ResourceManager::GetUIDFromMeta(const char * file)
{
	std::string path = file;
	path.append(".meta");
	std::string UID;

	if (App->fs->Exists(path.data()))
	{
		App->GetJsonLoader()->Load(path.data());
		nlohmann::json file = App->GetJsonLoader()->getFile();
		std::string id = file["UID"];
		UID = id;
	}

	return UID.data();
}

Resource * ResourceManager::GetResource(const char * original_file)
{
	// --- If resource is loaded into memory, return pointer to it, else load it ---

	for (std::map<std::string, Resource*>::iterator it = resources.begin(); it != resources.end(); ++it)
	{
		std::string tmp = it->second->original_file;
		if (tmp.compare(original_file) == 0)
			return it->second;
	}

	return nullptr;
}