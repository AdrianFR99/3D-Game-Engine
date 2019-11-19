#ifndef __MODULETEXTURE_H__
#define __MODULETEXTURE_H__

#include "Globals.h"
#include "Module.h"
#include "ComponentMaterial.h"
#include "Gameobject.h"

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64


struct aiMaterial;


struct Texture {

	std::string path;
	uint id;
	int Height = 0;
	int Width = 0;
	std::string ResourceID ;
};

class ModuleTexture :
	public Module
{
public:
	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();


	bool Init(nlohmann::json config);
	bool Start();
	bool CleanUp();

	uint CreateCheckeredTex();
	uint CreateTexture(const char*path, ResourceTexture& resource);
	void SetTextureOptions(int ClampOptions,int FilterMag,int FilterMin);
	uint ToTexBuffer(uint size, int format, int width, int height,const void* Texture);

	void Load(nlohmann::json& file);
	void Save(nlohmann::json& file);
	void ReloadFromConfig();

	bool findTextureinList(std::string path,int& index,std::string& reference_name);

public:

	Texture* CurrentTex  = nullptr;


	std::vector<Texture*> TextureIDs;
	std::string TexturePath;
	uint ID;
	uint ChekeredID;
};

#endif //__MODULETEXTURE_H__
