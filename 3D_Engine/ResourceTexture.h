#ifndef __RESOURCE_TEXTURE_H__
#define __RESOURCE_TEXTURE_H__

#include "Resource.h"
#include <string>
#include "Globals.h"
#include "Maths.h"
//#include "ModuleTexture.h"

enum class 	Texture_Type;

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


	Material Comp_Material;
	uint DiffuseID;
	uint currentID;
	uint CheckeredID;
private:


};

#endif