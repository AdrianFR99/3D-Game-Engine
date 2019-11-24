
#include "Application.h"
#include "ResourceSceneLoader.h"
#include "ModuleAssets.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "ModuleEngineUI.h"
#include "WindowHierarchy.h"
#include "Gameobject.h"
#include "ModuleFileSystem.h"
#include "ResourceMeshLoader.h"
#include "ResourceTextureLoader.h"
#include "ResourceManager.h"
#include "ResourceMesh.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#include "mmgr/mmgr.h"

SceneLoader::SceneLoader()
{
	ImporterMesh = new ResourceMeshLoader;
	ImporterMaterial = new ResourceTextureLoader;
}

SceneLoader::~SceneLoader()
{
	delete ImporterMesh;
	delete ImporterMaterial;
}


bool SceneLoader::Import(const char * File_path) const
{
	
	// Get File Name
	std::string extension;
	std::string Filename;
	App->FileSystem->GetExtensionAndFilename(File_path,Filename, extension);

	// Get apth to file in assets folder ---
	std::string relative_path = ASSETS_FOLDER;
	relative_path.append(Filename);
	relative_path.append(extension);

	// Check if File is already in assets
	if (App->RS->IsFileImported(relative_path.data()))
	{

		//load from assets
		std::string model_uid = App->RS->GetUIDFromMeta(relative_path.data());

		if (extension == ".fbx" || extension == ".FBX")
		{
			std::string model_path = MODELS_FOLDER;
			model_path.append(model_uid);
			model_path.append(".model");
			Load(model_path.data());
		}

		return false;
	}
	else
	{
		// Make copy if it does not exist in asset folder
		App->Assets->CloneToAsset(File_path, relative_path);

		// Load buffer with asset folder file
		char* buffer;
		uint size = App->FileSystem->Load(relative_path.data(), &buffer);

		//  Import assimp scene
		const aiScene* scene = aiImportFileFromMemory(buffer, size, aiProcessPreset_TargetRealtime_MaxQuality, nullptr);

		//  Release buffer 
		if (buffer && size > 0)
		{
			delete[] buffer;

		}

		// if scene has messhes load them
	if (scene != nullptr && scene->HasMeshes())
	{
		App->Assets->SceneLoader(scene,relative_path,Filename);


		// release assimp scne
		aiReleaseImport(scene);

	}
	else
		LOG("|[error]: Error loading FBX %s", &File_path);

	}
	return true;
}

bool SceneLoader::Load(const char * exported_file) const
{
	// --- Load Scene/model file ---
		App->GetJsonLoader()->Load(exported_file);
		nlohmann::json file = App->GetJsonLoader()->getFile();


	std::vector<Gameobject*> objects;

	for (nlohmann::json::iterator it = file.begin(); it != file.end(); ++it)
	{
		// --- Create a Game Object for each node ---
		Gameobject* new_go = App->Gameobject->CreateEmpty();//must be fatherles

		// --- Retrieve GO's UID and name ---
		new_go->nameGameObject = it.key().data();
		std::string uid = file[it.key()]["UID"];
		new_go->ID = std::stoi(uid);

		// --- Iterate components ---
		nlohmann::json components = file[it.key()]["Components"];

		ComponentTransform* transform = transform = new_go->transformPointer;

		std::string posx = components["0"]["positionx"];
		std::string posy = components["0"]["positiony"];
		std::string posz = components["0"]["positionz"];

		std::string rotx = components["0"]["rotationx"];
		std::string roty = components["0"]["rotationy"];
		std::string rotz = components["0"]["rotationz"];

		std::string scalex = components["0"]["scalex"];
		std::string scaley = components["0"]["scaley"];
		std::string scalez = components["0"]["scalez"];

		for (nlohmann::json::iterator it2 = components.begin(); it2 != components.end(); ++it2)
		{
			// --- Determine ComponentType ---
			std::string val = it2.key();
			uint value = std::stoi(val);
			CompType type = (CompType)value;

			// --- Create components to fill ---
			ComponentMesh* mesh = nullptr;
			ComponentMaterial* mat = nullptr;
			ResourceMesh* rmesh = nullptr;
			ResourceTexture* texture = nullptr;
			std::string tmp;

			// --- Get path to component file ---
			std::string component_path;

			if (type != CompType::TRANSFORM)
			{
				std::string tmppath = components[val];
				component_path = tmppath;
			}

			std::string diffuse_uid;
			uint count;
			//aqui
			switch (type)
			{
			case CompType::TRANSFORM:
				transform->SetPosition(float3(std::stof(posx), std::stof(posy), std::stof(posz)));
				transform->SetRotation(float3{ RADTODEG*std::stof(rotx), RADTODEG*std::stof(roty), RADTODEG*std::stof(rotz) });
				transform->Scale(float3(std::stof(scalex), std::stof(scaley), std::stof(scalez)));
				break;

			case CompType::MATERIAL:
				// --- Check if Library file exists ---
				if (App->FileSystem->Exists(component_path.data()))
				{
					new_go->CreateComponent(new_go, MATERIAL, true);
					texture = (ResourceTexture*)App->RS->CreateNewResource(Resource::ResourceType::RT_TEXTURE, "");
					new_go->materialPointer->Resource_Material = texture;
					texture->CreateMaterial();
					texture->original_file = component_path;
					App->UI_Layer->HierarchyPanel->SetActiveGameobject(new_go);
					ImporterMaterial->Load(component_path.data(), *texture);
					

					/*diffuse_uid = component_path;
					App->FileSystem->SplitFilePath(component_path.data(), nullptr, &diffuse_uid);
					count = diffuse_uid.find_last_of(".");
					diffuse_uid = diffuse_uid.substr(0, count);
					mat->resource_material->resource_diffuse->SetUID(std::stoi(diffuse_uid));
					

					new_go->SetMaterial(mat);*/
				}
				else
					LOG("|[error]: Could not find %s", component_path.data());

				break;

			case CompType::MESH:

				// --- Check if Library file exists ---
				if (App->FileSystem->Exists(component_path.data()))
				{
					
					new_go->CreateComponent(new_go, MESH, true);
					mesh = new_go->meshPointer;
					ResourceMesh* tmp = mesh->Meshes_Vec = (ResourceMesh*)App->RS->CreateNewResource(Resource::ResourceType::RT_MESH, "");
					new_go->meshPointer->Meshes_Vec = tmp;
					AssetMesh* newasset = new AssetMesh;
					new_go->meshPointer->Meshes_Vec->Meshes_Vec = newasset;
						ImporterMesh->Load(component_path.data(), *mesh->Meshes_Vec);
					
				}
				else
					LOG("|[error]: Could not find %s", component_path.data());
				break;

			}
		}

		//transform->update_transform = true;
		objects.push_back(new_go);
	}

	// --- Parent GO's ---
	/*for (uint i = 0; i < objects.size(); ++i)
	{
		std::string parent_uid = file[objects[i]->GetName()]["Parent"];
		uint p_uid = std::stoi(parent_uid);

		for (uint j = 0; j < objects.size(); ++j)
		{
			if (p_uid == objects[j]->GetUID())
			{
				objects[j]->AddChildGO(objects[i]);
				continue;
			}
		}
	}

	App->scene_manager->GetRootGO()->OnUpdateTransform();*/

	return true;
}

std::string SceneLoader::SaveSceneToFile(std::vector<Gameobject*>& scene_gos, std::string& scene_name, ExportFileTypes exportedfile_type) const
{
	// --- Save Scene/Model to file ---

	nlohmann::json file;

	
	for (int i = 0; i < scene_gos.size(); ++i)
	{
		
		// --- Create GO Structure ---
		file[scene_gos[i]->nameGameObject];
		file[scene_gos[i]->nameGameObject]["UID"] = std::to_string(scene_gos[i]->ID);
		if (scene_gos[i]->Father!=nullptr)
			file[scene_gos[i]->nameGameObject]["Parent"] = std::to_string(scene_gos[i]->Father->ID);
		else
			file[scene_gos[i]->nameGameObject]["Parent"] = std::to_string(0);
		file[scene_gos[i]->nameGameObject]["Components"];

		if  ( scene_gos[i]->ComponentList.size() > 0)
		{


			std::string component_path;
			float3 position = scene_gos[i]->transformPointer->GetPosition();
			float3 rotation = scene_gos[i]->transformPointer->GetRotation();
			float3 scale = scene_gos[i]->transformPointer->GetScale();

			// --- Save Components to files ---

			
			if (scene_gos[i]->transformPointer!=nullptr)
			{
				// --- Store path to component file ---
				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::TRANSFORM)];

				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::TRANSFORM)]["positionx"] = std::to_string(position.x);
				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::TRANSFORM)]["positiony"] = std::to_string(position.y);
				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::TRANSFORM)]["positionz"] = std::to_string(position.z);

				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::TRANSFORM)]["rotationx"] = std::to_string(rotation.x);
				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::TRANSFORM)]["rotationy"] = std::to_string(rotation.y);
				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::TRANSFORM)]["rotationz"] = std::to_string(rotation.z);

				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::TRANSFORM)]["scalex"] = std::to_string(scale.x);
				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::TRANSFORM)]["scaley"] = std::to_string(scale.y);
				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::TRANSFORM)]["scalez"] = std::to_string(scale.z);

			}
			if (scene_gos[i]->meshPointer != nullptr)
			{
				
				component_path = MESHES_FOLDER;
				component_path.append(std::to_string(App->GetRandom().Int()));
				component_path.append(".mesh");
				ImporterMesh->Save(scene_gos[i]->meshPointer->Meshes_Vec, component_path.data());

				// --- Store path to component file ---
				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::MESH)] = component_path;
					

			}
			if (scene_gos[i]->materialPointer != nullptr)
			{
				component_path = TEXTURES_FOLDER;
				component_path.append(scene_gos[i]->materialPointer->Resource_Material->GetUniqueId());
				component_path.append(".dds");
				
				file[scene_gos[i]->nameGameObject]["Components"][std::to_string((uint)CompType::MATERIAL)] = scene_gos[i]->materialPointer->Resource_Material->original_file;
				


			}
		
			


		}
	}
	// --- Serialize JSON to string ---
	std::string data;
	data = App->GetJsonLoader()->Serialize(file);

	// --- Set destination file given exportfile type ---
	std::string nwstruid;
	std::string path;
	uint new_uid;
	std::string filename = ASSETS_FOLDER;
	filename.append(scene_name);

	switch (exportedfile_type)
	{
	case MODEL:
		path = MODELS_FOLDER;
		new_uid = App->GetRandom().Int();
		nwstruid = std::to_string(new_uid);
		path.append(std::to_string(new_uid));
		path.append(".model");
		filename.append(".fbx");
		App->RS->CreateMetaFromUID(nwstruid, filename.data());
		break;

	case SCENE:
		path = SCENES_FOLDER;
		path.append(scene_name);
		path.append(".scene");
		break;
	}

	// --- Finally Save to file ---
	char* buffer = (char*)data.data();
	uint size = data.length();

	App->FileSystem->Save(path.data(), buffer, size);

	return path;
}
