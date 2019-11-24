#include "ModuleLoaderControl.h"
#include "Application.h"
#include "ModuleTexture.h"

#include "ResourceSceneLoader.h"
#include "ResourceTextureLoader.h"
#include "ModuleFileSystem.h"
#include "ModuleEngineUI.h"
#include "WindowHierarchy.h"
#include "Event.h"

#include "GameObject.h"
#include "ComponentMaterial.h"

#include "ResourceManager.h"
#include "ResourceTexture.h"


#include "Assimp/include/cimport.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include "mmgr/mmgr.h"

void MyAssimpCallback(const char * msg, char * userData)
{
	// --- Get Assimp LOGS and print them to console ---
	LOG("[Assimp]: %s", msg);
}

ModuleImporter::ModuleImporter(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	SceneImporter = new SceneLoader;
}

ModuleImporter::~ModuleImporter()
{
}

bool ModuleImporter::Init(nlohmann::json file)
{
	// --- Stream LOG messages to MyAssimpCallback, that sends them to console ---
	struct aiLogStream stream;
	stream.callback = MyAssimpCallback;
	aiAttachLogStream(&stream);

	return true;
}

bool ModuleImporter::Start()
{
	//LoadFromPath("Assets/BakerHouse.fbx");
	//IScene->Load("Library/Models/BakerHouse.model");
	return true;
}


bool ModuleImporter::CleanUp()
{
	// --- Detach assimp log stream ---
	aiDetachAllLogStreams();

	// --- Destroy all Importers ---
	if (SceneImporter)
	{
		delete SceneImporter;
		SceneImporter = nullptr;
	}

	return true;
}

void ModuleImporter::CallbackEvent(const Event& event) {

	switch (event.type)
	{
	case Event::EventType::file_dropped:


		std::string DroppedFile_path = event.string;
		App->fs->NormalizePath(DroppedFile_path);

		// 3D model case
		if (DroppedFile_path.find(".fbx") != std::string::npos || DroppedFile_path.find(".FBX") != std::string::npos)
		{

			SceneImporter->Import(DroppedFile_path.data());
		}
		else if (DroppedFile_path.find(".png") != std::string::npos || DroppedFile_path.find(".PNG") != std::string::npos || DroppedFile_path.find(".dds") != std::string::npos || DroppedFile_path.find(".DDS") != std::string::npos)
		{
			SceneImporter->ImporterMaterial->import2(DroppedFile_path.data());

		

		}
	}



}


SceneLoader * ModuleImporter::GetImporterScene() const
{
	return SceneImporter;
}

bool ModuleImporter::LoadFromPath(const char* path) const
{
	//bool ret = true;

	//// MYTODO: Could JSONLoader be a new importer?

	//if (path)
	//{
	//	std::string DroppedFile_path = path;
	//	App->fs->NormalizePath(DroppedFile_path);

	//	// If it is a 3D Model ...
	//	if (DroppedFile_path.find(".fbx") != std::string::npos || DroppedFile_path.find(".FBX") != std::string::npos)
	//	{
	//		ImportData data;
	//		ret = IScene->Import(DroppedFile_path.data(), data);
	//	}
	//	// If it is a json file ...
	//	else if (DroppedFile_path.find(".json") != std::string::npos || DroppedFile_path.find(".JSON") != std::string::npos)
	//	{

	//	}
	//	// If it is an image file file ...
	//	else if (DroppedFile_path.find(".dds") != std::string::npos || DroppedFile_path.find(".png") != std::string::npos)
	//	{

	//		// --- Get Selected Game Object's Material ---
	//		Gameobject* Selected = App->UI_Layer->HierarchyPanel->getActiveGameobject();
	//		ComponentMaterial* mat = nullptr;

	//		if (Selected)
	//		{
	//			mat = Selected->materialPointer;

	//			if (mat)
	//			{
	//				if (mat->Resource_Material->Comp_Material.path == "Default")
	//				{
	//					mat->CreateMaterial();
	//					mat->resource_material = (ResourceMaterial*)App->resources->CreateResource(Resource::ResourceType::MATERIAL);
	//				}

	//				std::string destination = ASSETS_FOLDER;
	//				std::string filename;
	//				App->fs->SplitFilePath(path, nullptr, &filename, nullptr);
	//				destination.append(filename);

	//				if (!App->fs->Exists(destination.data()))
	//					App->fs->CopyFromOutsideFS(path, destination.data());

	//				ResourceTexture* tex = nullptr;

	//				// --- Look for meta, if found load image from library ---
	//				if (App->resources->IsFileImported(destination.data()))
	//				{
	//					uint uid = App->resources->GetUIDFromMeta(destination.data());

	//					std::string lib_Tex = TEXTURES_FOLDER;
	//					lib_Tex.append(std::to_string(uid));
	//					lib_Tex.append(".dds");

	//					tex = (ResourceTexture*)App->resources->GetResource(lib_Tex.data());

	//				}
	//				else
	//					tex = (ResourceTexture*)App->resources->GetResource(destination.data());

	//				if (tex)
	//				{
	//					if (mat->resource_material->resource_diffuse)
	//					{
	//						mat->resource_material->resource_diffuse->instances--;
	//						// MYTODO: UNLOAD RESOURCE FROM MEMORY
	//					}

	//					mat->resource_material->resource_diffuse = tex;
	//				}
	//				else
	//				{
	//					mat->resource_material->resource_diffuse = (ResourceTexture*)App->resources->CreateResource(Resource::ResourceType::TEXTURE);
	//					App->scene_manager->SetTextureToSelectedGO(App->textures->CreateTextureFromFile(destination.data(), mat->resource_material->resource_diffuse->Texture_width, mat->resource_material->resource_diffuse->Texture_height, mat->resource_material->resource_diffuse->GetUID()));

	//					std::string lib_Tex = TEXTURES_FOLDER;
	//					lib_Tex.append(std::to_string(mat->resource_material->resource_diffuse->GetUID()));
	//					lib_Tex.append(".dds");

	//					mat->resource_material->resource_diffuse->Texture_path = lib_Tex.data();
	//					mat->resource_material->resource_diffuse->SetOriginalFilename(lib_Tex.data());
	//				}

	//				App->scene_manager->GetSelectedGameObject()->SetMaterial(mat);

	//			}

	//		}
	//		else
	//			ret = false;
	//	}
	//}
	//else
	//	ret = false;

//carefull
	return false;
}
