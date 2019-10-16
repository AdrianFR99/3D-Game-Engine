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
	void SetTextureOptions(int ClampOptions,int FilterMag,int FilterMin);
	uint ToTexBuffer(uint size, int format, int width, int height,uint Wrapping, uint FilterMag, uint FilterMin, const void* Texture);

	

	uint IDChecker;
};

#endif //__MODULETEXTURE_H__