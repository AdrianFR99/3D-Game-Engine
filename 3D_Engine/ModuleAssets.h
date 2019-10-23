#ifndef __MODULEASSETS_H__
#define __MODULEASSETS_H__

#include<vector>
#include "Globals.h"
#include "Module.h"


class AssetMesh;
class Primitives;

class ModuleAssets:	public Module
{
public:

	ModuleAssets(Application* app, bool start_enabled = true);
	
	virtual ~ModuleAssets();
	bool Init();
	bool Start();
	
	

	void Draw();
	
	bool CleanUp();
	
	void CallbackEvent(const Event& event) override;
	
	bool LoadFiles(const char* path);
	bool LoadMesh(const char* path);

	std::vector<AssetMesh*> Meshes_Vec;
	std::vector<Primitives*> Primitives_Vec;
};




#endif //__MODULEASSETS_H__