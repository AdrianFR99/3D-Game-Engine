#ifndef __MODULETEXTURE_H__
#define __MODULETEXTURE_H__

#include "Globals.h"
#include "Module.h"


class ModuleTexture :
	public Module
{
public:
	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();


	bool Init();
	bool Start();
	bool CleanUp();

	void CreateCheckeredTex();
	void ToTexBuffer();


	uint IDChecker;
};

#endif //__MODULETEXTURE_H__