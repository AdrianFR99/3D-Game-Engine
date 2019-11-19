#ifndef __RESOURCE_TEXTURE_H__
#define __RESOURCE_TEXTURE_H__

#include "Resource.h"
#include <string>
#include "Globals.h"
//#include "ModuleTexture.h"

enum class Texture_Type {

	NONE,
	DIFFUSE,
	SPECULAR,
	UNKNOWN

};


struct Material {

	std::string path;
	Texture_Type type;
};

class ResourceTexture : public Resource
{
public:
	ResourceTexture(std::string unique_id);
	virtual ~ResourceTexture();

	void CleanUp();

	void CreateMaterial(std::string & path);

	void CreateMaterial();

	uint DiffuseID = 0;
	uint currentID = 0;
	uint CheckeredID = 0;

	Material Comp_Material;
private:


};

#endif