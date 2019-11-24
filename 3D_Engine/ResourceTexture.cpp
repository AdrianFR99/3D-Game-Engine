#include "ResourceTexture.h"
#include "Application.h"


ResourceTexture::ResourceTexture(std::string unique_id) : Resource(unique_id, Resource::ResourceType::RT_TEXTURE)
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

void ResourceTexture::CreateMaterial() {


	//DiffuseID = currentID;
	CheckeredID = App->Textures->ChekeredID;

	currentID = CheckeredID;

	Comp_Material.path = "---";
	//Comp_Material.type = Texture_Type::NONE;

}
