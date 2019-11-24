#include "ResourceTextureLoader.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "ModuleTexture.h"
#include "ResourceManager.h"
#include "ModuleEngineUI.h"
#include "WindowHierarchy.h"
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

void ResourceTextureLoader::import2(const char * file_path)
{
	// --- Get Selected Game Object's Material ---
	Gameobject* Selected = App->UI_Layer->HierarchyPanel->getActiveGameobject();
	ComponentMaterial* mat = nullptr;

	if (Selected)
	{
		mat = Selected->materialPointer;
		if (mat == nullptr)
		{

			Selected->CreateComponent(Selected, MATERIAL, true);
			mat = Selected->materialPointer;
			if (mat->Resource_Material == nullptr)
			{
				ResourceTexture* tmp2 = (ResourceTexture*)App->RS->CreateNewResource(Resource::ResourceType::RT_TEXTURE, "");
				Selected->materialPointer->Resource_Material = tmp2;
				/*std::vector<Resource*> resources;
				App->Textures->LoadID(file_path, resources,*tmp2);
				tmp2->LoadToMemory();*/
			}
		}
		if (mat)
		{

			std::string destination = ASSETS_FOLDER;
			std::string filename;
			std::string path;
			std::string ext;
			App->fs->SplitFilePath(file_path, &path, &filename, &ext);
			destination.append(filename);

			if (!App->fs->Exists(destination.data()))
				App->fs->CopyFromOutsideFS(file_path, destination.data());

			ResourceTexture* tex = nullptr;

			// searh for img in assets 
			if (App->RS->IsFileImported(destination.data()))
			{
				std::string uid = App->RS->GetUIDFromMeta(destination.data());

				std::string lib_Tex = TEXTURES_FOLDER;
				lib_Tex.append(uid);
				lib_Tex.append(".dds");

				tex = (ResourceTexture*)App->RS->GetResource(lib_Tex.data());

			}

			//


			//
			if (tex != nullptr)
			{

				mat->Resource_Material = tex;

			}
			else
			{
				std::vector<Resource*> resources;
				App->Textures->LoadID(file_path, resources, *mat->Resource_Material);
				mat->Resource_Material->LoadToMemory();
				/*uint id = mat->GetCurrentTextureID();
				App->Gameobject->SetTextureToActiveGameobject(id);
*/
				std::string lib_Tex = TEXTURES_FOLDER;
				lib_Tex.append(std::to_string(mat->Resource_Material->DiffuseID));
				lib_Tex.append(".dds");

				mat->Resource_Material->resource_file = lib_Tex.data();
				mat->Resource_Material->file_name = (lib_Tex.data());
			}

			//App->scene_manager->GetSelectedGameObject()->SetMaterial(mat);

		}
	}
}

