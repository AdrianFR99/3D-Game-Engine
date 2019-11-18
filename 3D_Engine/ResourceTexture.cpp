#include "ResourceTexture.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

ResourceTexture::ResourceTexture(std::string unique_id) : Resource(unique_id, RT_TEXTURE)
{
}

ResourceTexture::~ResourceTexture()
{
}

void ResourceTexture::CleanUp()
{
	
}

void ResourceTexture::CreateMaterial(std::string&path) {


	currentID = App->Textures->CreateTexture(path.data());
	DiffuseID = currentID;
	CheckeredID = App->Textures->ChekeredID;

	if (currentID == NULL) {
		currentID = CheckeredID;
	}

	Comp_Material.path = path;
	Comp_Material.type = Texture_Type::DIFFUSE;


}