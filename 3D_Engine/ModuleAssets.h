#ifndef __MODULEASSETS_H__
#define __MODULEASSETS_H__

#include<vector>
#include "Globals.h"
#include "Module.h"
#include "Gameobject.h"
#include "Primitives.h"

class AssetMesh;
class Primitives;
class aiScene;
class aiNode;

class ModuleAssets:	public Module
{
public:
	ALIGN_CLASS_TO_16
	ModuleAssets(Application* app, bool start_enabled = true);

	virtual ~ModuleAssets();
	bool Init(nlohmann::json config);
	bool Start();



	void Draw(Gameobject* tmp);

	bool CleanUp(Gameobject* tmp);

	

	
	bool LoadFiles(const char* path);
	bool LoadMesh(const char* path);

	void CreatePrimitive(Primitive_Type type);

	void CloneToAsset(std::string filepath, std::string destination);

	void NodeLoader(aiNode * node, const aiScene * scene, const char * File_path, std::vector<Gameobject*>& scene_gos, Gameobject* father = nullptr ) const;

	

	void SceneLoader( const aiScene* scene,std::string path, std::string Filename );
	
	bool DrawFaceNormals = false;
	bool DrawVertexNormals = false;

	bool TextChecker = false;
	bool TextNormal = true;

	

};




#endif //__MODULEASSETS_H__
