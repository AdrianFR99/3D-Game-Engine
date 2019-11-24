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

void ResourceTexture::SetData(byte * _texture_data, uint _texture_data_lenght, uint _width, uint _height, int _format, uint _wrap_s, uint _wrap_t, uint _mag, uint _min)
{
	if (_texture_data_lenght > 0)
	{
		texture_data = new byte[_texture_data_lenght];
		memcpy(texture_data, _texture_data, _texture_data_lenght * sizeof(byte));
	}

	texture_data_size = _texture_data_lenght;
	format = _format;
	size.x = _width;
	size.y = _height;
	wrap_s = _wrap_s;
	wrap_t = _wrap_t;
	mag = _mag;
	min = _min;
}

void ResourceTexture::LoadToMemory()
{
	if (texture_id == 0 && texture_data != nullptr && size.x > 0 && size.y > 0)
		texture_id = App->renderer3D->LoadTextureBuffer(texture_data, 1, format, size.x, size.y, wrap_s, wrap_t, mag, min);
	DiffuseID = texture_id;
	currentID = texture_id;
}