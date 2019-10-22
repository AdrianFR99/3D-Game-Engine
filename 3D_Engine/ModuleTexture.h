#ifndef __MODULETEXTURE_H__
#define __MODULETEXTURE_H__

#include "Globals.h"
#include "Module.h"

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64


struct Texture {

	std::string path;
	uint id;
};

class ModuleTexture :
	public Module
{
public:
	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();


	bool Init();
	bool Start();
	bool CleanUp();

	uint CreateCheckeredTex();
	uint CreateTexture(const char*path);
	void SetTextureOptions(int ClampOptions,int FilterMag,int FilterMin);
	uint ToTexBuffer(uint size, int format, int width, int height,const void* Texture);

public:
	
	Texture* tex = nullptr;

	std::vector<Texture*> TextureIDs;
	uint ID;
};

#endif //__MODULETEXTURE_H__