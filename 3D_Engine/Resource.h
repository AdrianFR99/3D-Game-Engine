#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>


class Resource
{
public:
	enum class ResourceType
	{
		RT_NULL,
		RT_TEXTURE,
		RT_MESH,

	};

	// structure
	Resource(std::string unique_id, ResourceType type);
	virtual ~Resource();
	virtual void CleanUp() {};

	//setter
	void SetFileName(std::string file_name);

	//getter
	ResourceType GetType();
	bool IsUsed();
	int  UsedCount();

	//Loaders
	void LoadMem();
	void UnloadMem();

	//Vars
	std::string GetFileName();
	std::string GetUniqueId();



private:

	virtual void LoadToMemory() {};
	virtual void UnloadFromMemory() {};

private:

	ResourceType type = ResourceType::RT_NULL;
	std::string  unique_id;
	int			 count_ref = 0;

	std::string file_name;
};

#endif