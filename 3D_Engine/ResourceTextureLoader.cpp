#include "ResourceTextureLoader.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "ModuleTexture.h"
#include "ResourceManager.h"

#include "ComponentMaterial.h"
#include "ResourceTexture.h"

#include "Assimp/include/scene.h"

#include "mmgr/mmgr.h"

ResourceTextureLoader::ResourceTextureLoader()
{
}

ResourceTextureLoader::~ResourceTextureLoader()
{
}

// --- Create Material from Scene and path to file ---
bool ResourceTextureLoader::Import(const char * File_path, const ImportData & IData) const
{
	ImportMaterialData MData = (ImportMaterialData&)IData;

	// --- Get Directory from filename ---
	std::string directory = File_path;
	directory = App->fs->GetPathFromFilePath(directory.data());

	if (MData.scene->HasMaterials())
	{
		// --- Get scene's first material ---
		aiMaterial* material = MData.scene->mMaterials[0];

		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString Texture_path;

			// --- Specify type of texture to retrieve (in this case DIFFUSE/ALBEDO)---
			material->GetTexture(aiTextureType_DIFFUSE, 0, &Texture_path);

			// --- Build whole path to texture file ---
			directory.append(Texture_path.C_Str());

			// --- If we find the texture file, load it ---


			/*ResourceTexture* texture = (ResourceTexture*)App->resources->GetResource(directory.data());

			if (texture)
			{
				MData.new_material->resource_diffuse = texture;
				texture->instances++;
			}
			else
			{
				MData.new_material->resource_diffuse = (ResourceTexture*)App->resources->CreateResource(Resource::ResourceType::TEXTURE);
				MData.new_material->resource_diffuse->buffer_id = App->textures->CreateTextureFromFile(directory.data(), MData.new_material->resource_diffuse->Texture_width, MData.new_material->resource_diffuse->Texture_height, MData.new_material->resource_diffuse->GetUID());
				MData.new_material->resource_diffuse->SetOriginalFilename(directory.data());
				MData.new_material->resource_diffuse->Texture_path = directory.data();
				App->resources->CreateMetaFromUID(MData.new_material->resource_diffuse->GetUID(), directory.data());
			}*/


		}
	}

	return true;
}

void ResourceTextureLoader::Load(const char * filename, ResourceTexture& mat)
{
	// --- Load from Library ---
	// --- LibUID won't be overwritten since we are loading from library ---
	//modify to pass a material and fillo the data 
	std::string path = filename;
	mat.CreateMaterial(path);
	//mat.DiffuseID = App->Textures->CreateTextureFromFile(filename, mat.resource_diffuse->Texture_width, mat.resource_diffuse->Texture_height, mat.resource_diffuse->GetUID());
	
	
}
