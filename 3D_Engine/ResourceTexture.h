#ifndef __RESOURCE_TEXTURE_H__
#define __RESOURCE_TEXTURE_H__

#include "Resource.h"
#include <string>
#include "Globals.h"
#include "Maths.h"
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

	void SetData(byte * _texture_data, uint _texture_data_lenght, uint _width, uint _height, int _format, uint _wrap_s, uint _wrap_t, uint _mag, uint _min);

	void LoadToMemory();

	uint DiffuseID = 0;
	uint currentID = 0;
	uint CheckeredID = 0;

	Material Comp_Material;
private:
	byte*  texture_data = nullptr;
	uint   texture_data_size = 0;
	uint   texture_id = 0;
	int	   format = 0;
	float2 size = float2(0, 0);
	uint   wrap_s = 0;
	uint   wrap_t = 0;
	uint   mag = 0;
	uint   min = 0;
	bool   flipped = false;

};

#endif