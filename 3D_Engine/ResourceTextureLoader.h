#ifndef __IMPORTER_MATERIAL_H__
#define __IMPORTER_MATERIAL_H__


#include "Globals.h"

struct aiScene;
class ResourceTexture;



struct ImportMaterialData : public ImportData
{
	const aiScene* scene = nullptr;
	ResourceTexture* new_material = nullptr;
};

class ResourceTextureLoader 
{

public:
	ResourceTextureLoader();
	virtual ~ResourceTextureLoader();

	bool Import(const char* File_path, const ImportData& IData) const;
	void Load(const char* filename, ResourceTexture& mat);
	void import2(const char* file_path);
};

#endif
