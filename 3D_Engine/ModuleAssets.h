#ifndef __MODULEASSETS_H__
#define __MODULEASSETS_H__

#include<vector>
#include "Globals.h"
#include "Module.h"
#include "Gameobject.h"

class AssetMesh;
class Primitives;

class ModuleAssets:	public Module
{
public:

	ModuleAssets(Application* app, bool start_enabled = true);

	virtual ~ModuleAssets();
	bool Init();
	bool Start();



	void Draw(Gameobject* tmp);

	bool CleanUp(Gameobject* tmp);

	void CallbackEvent(const Event& event) override;

	bool LoadFiles(const char* path);
	bool LoadMesh(const char* path);

	void CreatePrimitive();


	bool DrawFaceNormals = false;
	bool DrawVertexNormals = false;

	bool TextChecker = false;
	bool TextNormal = true;

	std::string Directory;

};




#endif //__MODULEASSETS_H__
