#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "Module.h"
#include <vector>
#include "JSONLoader.h"
#include "Resource.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "ResourceMeshLoader.h"


struct RMetaData
{
	Resource::ResourceType type = Resource::ResourceType::RT_NULL;
	std::string fatherPath = "";
	std::string Name = "";
	std::string UID = "";

	bool Compare(const char* file, const char* name, Resource::ResourceType type)
	{
		return (fatherPath == file && Name == name && this->type == type);
	}

};

class ResourceManager : public Module
{
public:
	ResourceManager(Application* app, bool start_enabled);
	virtual ~ResourceManager();

	bool Start();
	bool CleanUp();

	
	bool LoadResource(const char* file_path);
	bool LoadResource(const char* file_path, std::vector<Resource*>& resources);
	
	//void SaveResourceIntoFile(Resource* res);
	void CreateMetaFromUID(std::string UID, const char * filename);
	bool IsFileImported(const char * file);
	std::string GetUIDFromMeta(const char * file);
	Resource * GetResource(const char * original_file);
	Resource * Get(std::string _unique_id);
	Resource * CreateNewResource(Resource::ResourceType type, std::string _unique_id);
	

	
	int GetNewUID();

private:
	void OnLoadFile(const char* file_path, const char* file_name, const char* file_extension);
	void DeleteAllResources();

public:
	
	ResourceMeshLoader* meshLoader;

private:
	std::map<std::string, Resource*> resources;

	std::map<std::string, RMetaData> libraryResources;


	
};

#endif