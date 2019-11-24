#ifndef __IMPORTER_SCENE_H__
#define __IMPORTER_SCENE_H__

#include <vector>
#include "Globals.h"

class ResourceMeshLoader;
class ResourceTextureLoader;
struct aiNode;
struct aiScene;
class ComponentMaterial;
class Gameobject;



enum ExportFileTypes
{
	MODEL,
	SCENE
};

class SceneLoader 
{

public:
	SceneLoader();
	virtual ~SceneLoader();

	bool Import(const char* File_path) const ;
	bool Load(const char* exported_file) const ;
	std::string SaveSceneToFile(std::vector<Gameobject*>& scene_gos, std::string& scene_name, ExportFileTypes exportedfile_type) const;

	ResourceMeshLoader* ImporterMesh = nullptr;
	ResourceTextureLoader* ImporterMaterial = nullptr;
private:
};

#endif
