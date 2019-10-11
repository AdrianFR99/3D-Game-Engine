#ifndef __MODULEASSETS_H__
#define __MODULEASSETS_H__

#include "Globals.h"
#include "Module.h"


class ModuleAssets:	public Module
{
public:

	ModuleAssets(Application* app, bool start_enabled = true);
	
	virtual ~ModuleAssets();
	bool Init();
	bool Start();
	
	/*update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);*/

	void Draw();
	
	bool CleanUp();
	bool ImportFiles(const char* path);
	
	bool ImportMesh(const char* path);


};




#endif //__MODULEASSETS_H__