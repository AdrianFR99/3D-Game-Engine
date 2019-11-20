#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "Module.h"
#include <vector>
#include "JSONLoader.h"
#include "Resource.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"


class ResourceManager : public Module
{
public:
	ResourceManager(Application* app, bool start_enabled);
	virtual ~ResourceManager();

	bool Start();
	bool CleanUp();

	
	bool LoadResource(const char* file_path);
	bool LoadResource(const char* file_path, std::vector<Resource*>& resources);
	
	void SaveResourceIntoFile(Resource* res);
	Resource * Get(std::string _unique_id);
	Resource * CreateNewResource(ResourceType type, std::string _unique_id);
	

	
	int GetNewUID();

private:
	void OnLoadFile(const char* file_path, const char* file_name, const char* file_extension);
	void DeleteAllResources();

public:
	

private:
	std::map<std::string, Resource*> resources;

	
};

#endif