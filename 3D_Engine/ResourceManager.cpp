#include "ResourceManager.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "Globals.h"


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

Resource * ResourceManager::CreateNewResource(ResourceType type, std::string _unique_id )
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

	//if (App->fs->TextCmp("fbx", extension.c_str()))
	//{
	//	ret = mesh_loader->Load(file_path, resources, true);
	//	valid_extension = true;
	//}
	//

	//if (ret)
	//{
	//	App->fs->FileCopyPaste(file_path, App->fs->GetAssetsPath().c_str());

	//	// Save meta file ---------------------------
	//	std::string uid = GetNewUID();
	//	std::string json_name = App->fs->GetAssetsPath() + name + ".meta";
	//	//nlohmann::json meta = JsonLoader.Save CreateJSON(json_name.c_str());
	//	nlohmann::json meta;
	//	JsonLoader.Save(json_name.data(),meta);

	//	if (meta)
	//	{
	//		meta->SetString("uid", uid.c_str());

	//		meta->SetArray("resources");
	//		for (std::vector<Resource*>::iterator res = resources.begin(); res != resources.end(); ++res)
	//		{
	//			meta->AddStringToArray("resources", (*res)->GetUniqueId().c_str());
	//		}

	//		meta->Save();
	//	}

	//}

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

void ResourceManager::SaveResourceIntoFile(Resource * res)
{
	if (res != nullptr)
	{
	
		if (res->GetType() == RT_MESH)
		{
			//mesh_loader->Export(App->fs->GetLibraryMeshPath().c_str(), (ResourceMesh*)res);

		}
			
		
	}
	
}