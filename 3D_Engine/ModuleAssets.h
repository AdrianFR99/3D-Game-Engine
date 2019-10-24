#ifndef __MODULEASSETS_H__
#define __MODULEASSETS_H__

#include<vector>
#include "Globals.h"
#include "Module.h"
#include "Gameobject.h"


class AssetMesh;

class ModuleAssets:	public Module
{
public:

	ModuleAssets(Application* app, bool start_enabled = true);
	
	virtual ~ModuleAssets();
	bool Init();
	bool Start();
	
	

	void Draw(Gameobject* tmp);
	
	bool CleanUp(Gameobject* tmp);
	
	void ReceiveEvent(const Event& event) override;
	
	bool LoadFiles(const char* path);
	bool LoadMesh(const char* path);

	//std::vector<AssetMesh*> Meshes_Vec;

	bool DrawFaceNormals = false;
	bool DrawVertexNormals = false;

	bool TextChecker = false;
	bool TextNormal = true;
};




#endif //__MODULEASSETS_H__