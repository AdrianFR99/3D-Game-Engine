
#include "Application.h"
#include "ModuleAssets.h"
#include "AssetMesh.h"
#include "Event.h"
#include "Primitives.h"
#include "ModuleGameobject.h"
#include "ComponentMesh.h"
#include "ResourceManager.h"
#include "ComponentTransform.h"
#include "ModuleTexture.h"
#include "ModuleEngineUI.h"
#include "WindowHierarchy.h"
#include "ModuleScene.h"
#include "ResourceManager.h"
#include "ResourceSceneLoader.h"
#include "imgui_defines.h"

#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"


#pragma comment (lib, "Assimp/libx86/assimp.lib")


#include "mmgr/mmgr.h"


ModuleAssets::ModuleAssets(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleAssets::~ModuleAssets()
{
}
bool ModuleAssets::Init(nlohmann::json config) {

	// Stream log messages to Debug window
	struct aiLogStream stream;
	//stream.callback = MyAssimpCallback;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return true;
}

bool ModuleAssets::Start() {


	return true;
}


void ModuleAssets::Draw(Gameobject* tmp) {

	// Push matrix
	glPushMatrix();
	glMultMatrixf(tmp->transformPointer->GetGlobalTransform().Transposed().ptr());

	if (tmp->meshPointer->active != false)
	{

		if (tmp->meshPointer->Meshes_Vec->Primitives_Vec != nullptr) {

				tmp->meshPointer->Meshes_Vec->Primitives_Vec->Draw(tmp);
		}

		if ( tmp->meshPointer->Meshes_Vec->mesh_asset != nullptr)
		{

			if (tmp->meshPointer->Meshes_Vec->mesh_asset->active != false)
			{

				if (tmp->meshPointer->Meshes_Vec->mesh_asset != nullptr) {
					// Vertex


					glEnableClientState(GL_TEXTURE_COORD_ARRAY);

					//texture
					if (tmp->materialPointer != nullptr)
					{
					if (tmp->materialPointer->active != false)
					{
						glBindTexture(GL_TEXTURE_2D, tmp->materialPointer->GetCurrentTextureID()); // start using texture
						glEnableClientState(GL_TEXTURE_COORD_ARRAY);
						glActiveTexture(GL_TEXTURE0);
						glBindBuffer(GL_ARRAY_BUFFER, tmp->meshPointer->Meshes_Vec->mesh_asset->UVC); // start using created buffer (tex coords)
						glTexCoordPointer(3, GL_FLOAT, 0, NULL); // Specify type of data format
					}
					else
					{
						glBindTexture(GL_TEXTURE_2D, -1); // start using texture
						glActiveTexture(GL_TEXTURE0);
						glBindBuffer(GL_ARRAY_BUFFER, tmp->meshPointer->Meshes_Vec->mesh_asset->UVC); // start using created buffer (tex coords)
						glTexCoordPointer(3, GL_FLOAT, 0, NULL); // Specify type of data format
					}
					//else if (TextChecker) //TODO must change this to selec objects and change individually
					//{
					//	glBindTexture(GL_TEXTURE_2D,tmp->materialPointer->GetCurrentTextureID()); // start using texture
					//	glActiveTexture(GL_TEXTURE0);
					//	glBindBuffer(GL_ARRAY_BUFFER, tmp->meshPointer->Meshes_Vec[i]->UVC); // start using created buffer (tex coords)
					//	glTexCoordPointer(2, GL_FLOAT, 0, NULL); // Specify type of data format
					//}
					}


					glEnableClientState(GL_VERTEX_ARRAY);

					glBindBuffer(GL_ARRAY_BUFFER, tmp->meshPointer->Meshes_Vec->mesh_asset->VBO);
					glVertexPointer(3, GL_FLOAT, 0, NULL);
					// Index
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmp->meshPointer->Meshes_Vec->mesh_asset->IBO);
					// Draw

					glDrawElements((GLenum)GL_TRIANGLES, tmp->meshPointer->Meshes_Vec->mesh_asset->num_index, GL_UNSIGNED_INT, NULL);



					glDisableClientState(GL_TEXTURE_COORD_ARRAY);
					glDisableClientState(GL_VERTEX_ARRAY);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


					if (tmp->meshPointer->Meshes_Vec->mesh_asset->normals!=nullptr && (DrawFaceNormals || DrawVertexNormals))
					{
						tmp->meshPointer->Meshes_Vec->mesh_asset->DrawNormals(1.0f,1,float3(0.0f, 0.5f, 0.5f), float3(0.0f, 1.0f, 0.0f),1.0f, DrawFaceNormals, DrawVertexNormals);

					}

					if (tmp->meshPointer->Meshes_Vec->mesh_asset->normals != nullptr && (tmp->meshPointer->normalsDrawFaces || tmp->meshPointer->normalsDrawVertex))
					{

						tmp->meshPointer->Meshes_Vec->mesh_asset->DrawNormals(1.0f, 1, float3(0.0f, 0.5f, 0.5f), float3(0.0f, 1.0f, 0.0f), 1.0f, tmp->meshPointer->normalsDrawFaces, tmp->meshPointer->normalsDrawVertex);

					}





				}

			}


		}

	}

	// Reset
	glBindTexture(GL_TEXTURE_2D, 0);

	// Pop matrix
	glPopMatrix();

	// Pop matrix
	glPopMatrix();


}

bool ModuleAssets::CleanUp(Gameobject* tmp) {
	// detach log stream
	aiDetachAllLogStreams();


	if  ( tmp->meshPointer->Meshes_Vec->mesh_asset != nullptr) {

		glDeleteBuffers(1, &tmp->meshPointer->Meshes_Vec->mesh_asset->VBO);
		glDeleteBuffers(1, &tmp->meshPointer->Meshes_Vec->mesh_asset->IBO);
		glDeleteBuffers(1, &tmp->meshPointer->Meshes_Vec->mesh_asset->UVC);


		// Manual Release for MMGR
		if (tmp->meshPointer->Meshes_Vec->mesh_asset->vertices != nullptr)
		{

			delete[] tmp->meshPointer->Meshes_Vec->mesh_asset->vertices;

			tmp->meshPointer->Meshes_Vec->mesh_asset->vertices = nullptr;
		}
		if (tmp->meshPointer->Meshes_Vec->mesh_asset->indices != nullptr)
		{
			delete[] tmp->meshPointer->Meshes_Vec->mesh_asset->indices;

			tmp->meshPointer->Meshes_Vec->mesh_asset->indices = nullptr;

		}
		if (tmp->meshPointer->Meshes_Vec->mesh_asset->normals != nullptr)
		{
			delete[] tmp->meshPointer->Meshes_Vec->mesh_asset->normals;

			tmp->meshPointer->Meshes_Vec->mesh_asset->normals = nullptr;

		}
		if (tmp->meshPointer->Meshes_Vec->mesh_asset->normals_faces != nullptr)
		{
			delete[] tmp->meshPointer->Meshes_Vec->mesh_asset->normals_faces;

			tmp->meshPointer->Meshes_Vec->mesh_asset->normals_faces = nullptr;
		}
		if (tmp->meshPointer->Meshes_Vec->mesh_asset->normals_faces_pos != nullptr)
		{
			delete[] tmp->meshPointer->Meshes_Vec->mesh_asset->normals_faces_pos;

			tmp->meshPointer->Meshes_Vec->mesh_asset->normals_faces_pos = nullptr;
		}
		if (tmp->meshPointer->Meshes_Vec->mesh_asset->uv_coord != nullptr)
		{
			delete[] tmp->meshPointer->Meshes_Vec->mesh_asset->uv_coord;

			tmp->meshPointer->Meshes_Vec->mesh_asset->uv_coord = nullptr;

		}
		if (tmp->meshPointer->Meshes_Vec->mesh_asset != nullptr)
		{
			delete tmp->meshPointer->Meshes_Vec->mesh_asset;

			tmp->meshPointer->Meshes_Vec->mesh_asset = nullptr;

		}



	}

	//tmp->meshPointer->Meshes_Vec->Meshes_Vec.clear();

		App->camera->premadeDist = -1.0f;
		App->camera->Reference = vec3(0, 0, 0);

		//TODO2
		//primitive clean up
	return true;
}

bool ModuleAssets::LoadFiles(const char* path) {

	std::string path_Aux = path;

	if (path_Aux.find(".fbx") != std::string::npos || path_Aux.find(".FBX") != std::string::npos) {


		LoadMesh(path);
	}

	else if (path_Aux.find(".png") != std::string::npos || path_Aux.find(".dds") != std::string::npos) {


		int id = -1;
		bool found = false;
		std::string referenceID = "none";
		found = App->Textures->findTextureinList(path, id, referenceID);
		ResourceTexture* re = nullptr;

		if (found == false)
		{
			re = (ResourceTexture*)App->RS->CreateNewResource(Resource::ResourceType::RT_TEXTURE, "");
			id = App->Textures->CreateTexture(path,*re);
		}
		if (id != -1 )
		{
			if (found && referenceID != "none")
			{
				re = (ResourceTexture*)App->RS->Get(referenceID);
			}
			Gameobject* activeGameObject = nullptr;
			activeGameObject = App->UI_Layer->HierarchyPanel->getActiveGameobject();

			if (App->Gameobject->GameobjectList.size()>0) {

				if (activeGameObject!=nullptr )
				{

					if (activeGameObject->materialPointer != nullptr)
					{
						activeGameObject->materialPointer->Resource_Material = re;
						activeGameObject->materialPointer->SetTextureID(id);
						activeGameObject->materialPointer->SetDiffuseID(id);

					}
					else if (activeGameObject->materialPointer == nullptr)
					{
						activeGameObject->CreateComponent(activeGameObject, MATERIAL, true);
						activeGameObject->materialPointer->Resource_Material = re;
						activeGameObject->materialPointer->SetTextureID(id);
						activeGameObject->materialPointer->SetDiffuseID(id);
					}
				}
				else
				{
					if (App->Gameobject->GameobjectList[1]->materialPointer != nullptr)
					{
						App->Gameobject->GameobjectList[1]->materialPointer->Resource_Material = re;
						App->Gameobject->GameobjectList[1]->materialPointer->SetTextureID(id);
						App->Gameobject->GameobjectList[1]->materialPointer->SetDiffuseID(id);
					}
					else if (activeGameObject->materialPointer == nullptr)
					{
						App->Gameobject->GameobjectList[1]->CreateComponent(App->Gameobject->GameobjectList[1], MATERIAL, true);
						App->Gameobject->GameobjectList[1]->materialPointer->Resource_Material = re;
						App->Gameobject->GameobjectList[1]->materialPointer->SetTextureID(id);
						App->Gameobject->GameobjectList[1]->materialPointer->SetDiffuseID(id);
					}


				}

			}

		}




	}


	App->GearConsole.AddLog(" Loading File %s",path);

	return true;
}

bool ModuleAssets::LoadMesh(const char* path) {

	App->GearConsole.AddLog(" Loading Mesh from %s ",path);

	const aiScene* Scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (Scene != nullptr && Scene->HasMeshes())
	{
		Gameobject* father;
		for (uint i = 0; i < Scene->mNumMeshes; ++i)
		{
			Gameobject* tmpGO = App->Gameobject->CreateGameObject();
			tmpGO->CreateComponent(tmpGO, MESH, true);

			ResourceMesh* tmp = (ResourceMesh*)App->RS->CreateNewResource(Resource::ResourceType::RT_MESH,"");
			tmpGO->meshPointer->Meshes_Vec = tmp;

			//insert name game obj
			std::string filename = path;
			std::size_t size = filename.find_last_of(".");
			std::size_t found = filename.find_last_of("/\\");
			size = (int)size - (int)found;
			filename = filename.substr(found + 1,size-1);
			int numb = (int)i;
			std::string number = std::to_string(numb);
			filename.append(number);
			tmp->SetFileName(filename);
			tmpGO->nameGameObject=filename;
			if (i == 0)
			{
				father = tmpGO;
				tmpGO->Father = App->SceneEngine->GetSceneGameObjcet();
			}
			else if (father!=nullptr)
			{
				tmpGO->Father = father;
			}



			AssetMesh* NewMesh = new AssetMesh;
			NewMesh->importMesh(Scene->mMeshes[i]);
			//tmp->meshPointer->Meshes_Vec->Meshes_Vec.push_back(NewMesh);
			//Assign AABB&OBB

			//tmp->SetBBOs();

			NewMesh->importMesh(Scene->mMeshes[i]);

			tmp->mesh_asset = NewMesh;

			std::string component_path = "Library/Meshes/ ";
			component_path.append(std::to_string(App->GetRandom().Int()));
			component_path.append(".mesh");
			App->RS->meshLoader->Save(tmp, component_path.data());


			if (Scene->HasMaterials()) {

				tmpGO->CreateComponent(tmpGO, MATERIAL, true);
				ResourceTexture* tmp2 = (ResourceTexture*)App->RS->CreateNewResource(Resource::ResourceType::RT_TEXTURE, "");
				tmpGO->materialPointer->Resource_Material = tmp2;
				aiString Texture_path;

				aiMaterial* mat = Scene->mMaterials[0];
				mat->GetTexture(aiTextureType_DIFFUSE,0,&Texture_path);

				std::string filename = path;
				std::size_t found = filename.find_last_of("/\\");
				filename = filename.substr(0, found+1);
				filename.append(Texture_path.C_Str());


				tmp2->CreateMaterial(filename);
				//tmp->Default_texture = tmp2;
			}

			if (i==0)
			{
				Gameobject* scene = App->SceneEngine->GetSceneGameObjcet();
				scene->GameObject_Child_Vec.push_back(tmpGO);
			}
			else
			{
				father->GameObject_Child_Vec.push_back(tmpGO);
			}

		}


	}
	else
	{

		LOG("|[error]: Error loading scene %s", path);
		App->GearConsole.AddLog(" Error Loading Mesh, no meshes or irregular path ");
	}

	return true;

}


void ModuleAssets::CreatePrimitive(Primitive_Type type)
{
	Gameobject* tmp = App->Gameobject->CreateGameObject();
	tmp->CreateComponent(tmp, MESH, true);

	ResourceMesh* tmpRes = (ResourceMesh*)App->RS->CreateNewResource(Resource::ResourceType::RT_MESH, "");
	tmp->meshPointer->Meshes_Vec = tmpRes;

	std::string nameid = std::to_string(tmp->ID);

	tmp->Father = App->SceneEngine->GetSceneGameObjcet();
	Gameobject* scene = App->SceneEngine->GetSceneGameObjcet();
	scene->GameObject_Child_Vec.push_back(tmp);
	switch (type)
	{
	case Primitive_Type::CUBE:
		tmp->nameGameObject = "cube";
		tmp->nameGameObject.append(nameid);
		break;
	case Primitive_Type::SPHERE:
		tmp->nameGameObject = "sphere";
		tmp->nameGameObject.append(nameid);
		break;
	case Primitive_Type::CYLINDER:
		tmp->nameGameObject = "cylinder";
		tmp->nameGameObject.append(nameid);
		break;
	case Primitive_Type::CONE:
		tmp->nameGameObject = "cone";
		tmp->nameGameObject.append(nameid);
		break;
	case Primitive_Type::DODECA:
		tmp->nameGameObject = "dodeca";
		tmp->nameGameObject.append(nameid);
		break;
	case Primitive_Type::TETRA:
		tmp->nameGameObject = "tetra";
		tmp->nameGameObject.append(nameid);
		break;
	case Primitive_Type::OCTO:
		tmp->nameGameObject = "tetra";
		tmp->nameGameObject.append(nameid);
		break;
	case Primitive_Type::ICOSA:
		tmp->nameGameObject = "icosa";
		tmp->nameGameObject.append(nameid);
		break;
	case Primitive_Type::BOTTLE:
		tmp->nameGameObject = "bottle";
		tmp->nameGameObject.append(nameid);
		break;
	default:
		tmp->nameGameObject = "primitive";
		tmp->nameGameObject.append(nameid);
		break;
	}

	tmpRes->SetFileName(tmp->nameGameObject);

	Primitives*aux = nullptr;
	aux = new Primitives(type);

	tmpRes->Primitives_Vec = aux;

	tmp->CreateComponent(tmp, MATERIAL, true);
	ResourceTexture* tmp2 = (ResourceTexture*)App->RS->CreateNewResource(Resource::ResourceType::RT_TEXTURE, "");
	tmp->materialPointer->Resource_Material = tmp2;


	tmp2->CreateMaterial();

	tmp->materialPointer->UseCheckered(true);

	/*tmp->materialPointer->UseCheckered(true);*/
	//TODO
	//make switch and pass parameter to function for what to create
	tmp->meshPointer->Meshes_Vec->Primitives_Vec = aux;




}

void ModuleAssets::CloneToAsset(std::string filepath, std::string destination)
{
	// Make Copy in Asset Folder
	if (!App->FileSystem->Exists(destination.data()))
		App->FileSystem->CopyFromOutsideFS(filepath.data(), destination.data());
}

void ModuleAssets::SceneLoader( const aiScene * scene, std::string path, std::string Filename)
{
	std::vector<Gameobject*> scene_gos;

	// Load Scene by nodes ,scene_pos
	FirstLoad(path.data(),true,scene,scene_gos);


	// Export to OwnFormat
	std::string exported_file = App->importer->GetImporterScene()->SaveSceneToFile(scene_gos, Filename, MODEL);



}



bool ModuleAssets::FirstLoad(const char * filepath, bool as_new_gameobject, const aiScene* scene, std::vector<Gameobject*>& vector)
{
	bool ret = true;

	std::string path = App->FileSystem->GetPathFromFilePath(filepath);
	std::string filename = App->FileSystem->GetFileNameFromFilePath(filepath);
	std::string name;
	std::string ext;
	App->FileSystem->GetExtensionAndFilename(filename.c_str(),name,ext);
	LOG("\nStarting mesh scene Loading -------------------- \n\n");
	//scene = aiImportFile(filepath, aiProcessPreset_TargetRealtime_MaxQuality);
	LOG("Finishing mesh scene Loading ---------------------");

	if (scene == nullptr)
		ret = false;

	if (ret && !scene->HasMeshes())
	{
		LOG("WARNING, scene has no meshes!");
		ret = false;
	}

	if (ret)
	{
		aiNode* root = scene->mRootNode;

		// Root transform
		float3 position(0, 0, 0);
		Quat rotation(0, 0, 0, 0);
		float3 scale(0, 0, 0);

		aiVector3D aitranslation;
		aiVector3D aiscaling;
		aiQuaternion airotation;

		if (root != nullptr)
		{
			root->mTransformation.Decompose(aiscaling, airotation, aitranslation);
			position = float3(aitranslation.x, aitranslation.y, aitranslation.z);
			scale = float3(aiscaling.x, aiscaling.y, aiscaling.z);
			rotation = Quat(airotation.x, airotation.y, airotation.z, airotation.w);
		}

		// Create root go
		Gameobject* parent = nullptr;

		parent = App->Gameobject->CreateEmpty();
		parent->transformPointer->SetPosition(float3(position.x, position.y, position.z));
		parent->transformPointer->SetRotationQuat(Quat(rotation.x, rotation.y, rotation.w, rotation.z));
		parent->transformPointer->SetScale(float3(1, 1, 1));

		std::string filepath2 = App->FileSystem->GetFileNameFromFilePath(filepath);
		std::string name;
		App->FileSystem->GetExtensionAndFilename(filepath2.c_str(), name, ext);
		parent->nameGameObject=name;

		parent->UpdateTransform = true;
		//// Total mesh bbox
		//AABB total_abb;
		//total_abb.SetNegativeInfinity();

		// Keep track of resources loaded (avoid repeating)
		vector.push_back(parent);
		// Iterate

		for (int i = 0; i < root->mNumChildren; i++)
		{
			RecursiveLoadMesh( root->mChildren[i], scene, filepath, vector, parent);
		}

		App->SceneEngine->scene->GameObject_Child_Vec;
		int a = 0;
		// Set camera focus

	}


	return ret;
}

void ModuleAssets::RecursiveLoadMesh(aiNode * node, const aiScene * scene,  const char * full_path,
	std::vector<Gameobject*>& resources, Gameobject * parent)
{
	bool node_valid = true;

	if (node->mNumMeshes == 0)
		node_valid = false;

	/*AssetMesh* assetMesh = new AssetMesh;
	assetMesh.*/
	aiMesh* aimesh = nullptr;
	ResourceMesh* mesh = nullptr;
	Gameobject* go = nullptr;
	std::string name = node->mName.C_Str();

	for (int i = 0; i < node->mNumMeshes; i++)
	{
		bool mesh_valid = true;

		int mesh_index = node->mMeshes[i];
		aimesh = scene->mMeshes[mesh_index];

		// Check if its already loaded
		Resource* res_mesh = nullptr;
		bool mesh_already_loaded = false;
		/*if (ResourceIsUsed(mesh_index, RT_MESH, res_mesh))
		{
			mesh = (ResourceMesh*)res_mesh;
			mesh_already_loaded = true;
		}*/

		if (mesh_valid && node_valid && !mesh_already_loaded)
		{
			mesh = (ResourceMesh*)App->RS->CreateNewResource(Resource::ResourceType::RT_MESH, "");
			AssetMesh* NewMesh = new AssetMesh;
			mesh->mesh_asset = NewMesh;
			mesh->SetFileName(name.c_str());

			if (!aimesh->HasFaces())
			{
				LOG("WARNING, geometry has no faces!");
				mesh_valid = false;
			}
		}

		// VERTICES && INDICES
		if (mesh_valid && node_valid && !mesh_already_loaded)
		{
			float* vertices = new float[aimesh->mNumVertices * 3];
			memcpy(vertices, aimesh->mVertices, sizeof(float) * aimesh->mNumVertices * 3);

			uint* indices = new uint[aimesh->mNumFaces * 3];

			for (uint i = 0; i < aimesh->mNumFaces && mesh_valid; ++i)
			{
				if (aimesh->mFaces[i].mNumIndices == 3)
				{
					memcpy(&indices[i * 3], aimesh->mFaces[i].mIndices, 3 * sizeof(uint));
				}
				else
				{
					LOG("WARNING, geometry face with != 3 indices!");
					mesh_valid = false;
				}
			}

			mesh->SetFaces(vertices, aimesh->mNumVertices, indices, aimesh->mNumFaces * 3);

			RELEASE_ARRAY(vertices);
			RELEASE_ARRAY(indices);
		}

		// UVS
		if (mesh_valid && node_valid && !mesh_already_loaded && aimesh->HasTextureCoords(0))
		{
			float* uvs = new float[aimesh->mNumVertices * 3];
			memcpy(uvs, (float*)aimesh->mTextureCoords[0], sizeof(float) * aimesh->mNumVertices * 3);

			mesh->SetUvs(uvs, aimesh->mNumVertices);

			RELEASE_ARRAY(uvs);
		}

		// POSITION, ROTATION AND SCALE
		float3 position(0, 0, 0);
		Quat rotation(0, 0, 0, 0);
		float3 scale(0, 0, 0);

		float3 posi ;
		Quat roti ;
		float3 scali ;

		if (mesh_valid && node_valid)
		{
			aiVector3D aitranslation;
			aiVector3D aiscaling;
			aiQuaternion airotation;

			node->mTransformation.Decompose(aiscaling, airotation, aitranslation);
			position = float3(aitranslation.x, aitranslation.y, aitranslation.z);
			scale = float3(aiscaling.x, aiscaling.y, aiscaling.z);
			rotation = Quat(airotation.x, airotation.y, airotation.z, airotation.w);

			 posi = float3(position.x, position.y, position.z);
			 roti = Quat(rotation.x, rotation.y, rotation.w, rotation.z);
			 scali = float3(scale.x, scale.y, scale.z);




		}

		

		// MATERIALS
		ResourceTexture* texture = nullptr;
		std::string pathtext;
		std::vector<Resource*> tex;
		if (mesh_valid && node_valid)
		{
			// Check if its already loaded
			Resource* res_tex = nullptr;
			bool texture_already_loaded = false;
			/*if (ResourceIsUsed(aimesh->mMaterialIndex, RT_TEXTURE, res_tex))
			{
				texture = (ResourceTexture*)res_tex;
				texture_already_loaded = true;
			}*/

			if (!texture_already_loaded)
			{
				aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];

				pathtext = App->FileSystem->GetPathFromFilePath(full_path);

				// Difuse -------------------
				aiString file;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &file);
				pathtext += App->FileSystem->GetFileNameFromFilePath(file.C_Str());


				/*if (!tex.empty())
				{
					texture = (ResourceTexture*)*tex.begin();
					AddResource(aimesh->mMaterialIndex, RT_TEXTURE, texture);
				}*/
			}
		}




		// CREATE GAME OBJECT
		if (mesh_valid && node_valid && parent != nullptr)
		{
			go = App->Gameobject->CreateEmptyFatherLess();

			if (name == "")
				name = "no_name";

			go->nameGameObject=(name);

			parent->GameObject_Child_Vec.push_back(go);
			go->Father = parent;

			go->transformPointer->SetPosition(posi);
			go->transformPointer->SetRotationQuat(roti);
			go->transformPointer->SetScale(float3(1,1,1));

			go->CreateComponent(go, MESH, true);
			ComponentMesh* cmesh = go->meshPointer;
			cmesh->Meshes_Vec=(mesh);

			cmesh->Meshes_Vec->mesh_asset->GenerateAABB();
			////// SetBoxes
			go->SetBBOs();


			resources.push_back(go);

		


			//text
			App->UI_Layer->HierarchyPanel->SetActiveGameobject(go);
			App->RS->LoadResource(pathtext.c_str(), tex);
			/*if (texture != nullptr)
			{
				go->AddComponent(MATERIAL);
				ComponentMaterial* cmaterial = (ComponentMaterial*)go->GetComponent(MATERIAL);
				cmaterial->SetTexture(texture);
			}*/
		}

		/*if (mesh_valid && node_valid && !mesh_already_loaded && mesh != nullptr)
		{
			App->resource_manager->SaveResourceIntoFile(mesh);

			AddResource(mesh_index, RT_MESH, mesh);

			resources.push_back(mesh);
		}*/

		/*else if (!mesh_valid && !mesh_already_loaded && mesh != nullptr)
			App->RS->DeleteResource(mesh->GetUniqueId());*/
	}

	// Select parent
	Gameobject* pare = nullptr;
	if (node_valid && go != nullptr)
		pare = go;
	else
		pare = parent;


	if (mesh != nullptr) {

		mesh->mesh_asset->ToBuffer();
		go->UpdateTransform = true;
	}
	// RECURSE


	for (int i = 0; i < node->mNumChildren; i++)
	{
		RecursiveLoadMesh( node->mChildren[i], scene, full_path, resources, pare);
	}
}
