#include "ResourceTexture.h"
#include "Application.h"


ResourceTexture::ResourceTexture(std::string unique_id) : Resource(unique_id, RT_TEXTURE)
{
	/*unique_id = _unique_id;
	type = _type;
	count_ref = 0;*/
}

ResourceTexture::~ResourceTexture()
{
}

void ResourceTexture::CleanUp()
{
	
}

void ResourceTexture::CreateMaterial(std::string&path) {
	

	currentID = App->Textures->CreateTexture(path.data(), *this);
	DiffuseID = currentID;
	CheckeredID = App->Textures->ChekeredID;

	if (currentID == NULL) {
		currentID = CheckeredID;
	}

	Comp_Material.path = path;
	Comp_Material.type = Texture_Type::DIFFUSE;


}