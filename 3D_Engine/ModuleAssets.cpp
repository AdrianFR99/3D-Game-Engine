
#include "Application.h"
#include "ModuleAssets.h"
#include "AssetMesh.h"
#include "Event.h"
#include "Primitives.h"
#include "ModuleGameobject.h"
#include "ComponentMesh.h"
#include "ModuleTexture.h"
#include "ModuleEngineUI.h"
#include"WindowHierarchy.h"

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
bool ModuleAssets::Init(){

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

	
	

	if (tmp->meshPointer->Primitives_Vec.size() > 0) {

		for (int i = 0; i < tmp->meshPointer->Primitives_Vec.size(); ++i)
			tmp->meshPointer->Primitives_Vec[i]->Draw(tmp);
	}

	for (int i = 0; i < tmp->meshPointer->Meshes_Vec.size();++i) {

		if (tmp->meshPointer->Meshes_Vec[i] != nullptr) {
			// Vertex


			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			//texture
			if (TextNormal)
			{
				glBindTexture(GL_TEXTURE_2D, tmp->materialPointer->GetCurrentTextureID()); // start using texture
				glActiveTexture(GL_TEXTURE0);
				glBindBuffer(GL_ARRAY_BUFFER, tmp->meshPointer->Meshes_Vec[i]->UVC); // start using created buffer (tex coords)
				glTexCoordPointer(2, GL_FLOAT, 0, NULL); // Specify type of data format
			}
			else if (TextChecker) //TODO must change this to selec objects and change individually
			{
				glBindTexture(GL_TEXTURE_2D,tmp->materialPointer->GetCurrentTextureID()); // start using texture
				glActiveTexture(GL_TEXTURE0);
				glBindBuffer(GL_ARRAY_BUFFER, tmp->meshPointer->Meshes_Vec[i]->UVC); // start using created buffer (tex coords)
				glTexCoordPointer(2, GL_FLOAT, 0, NULL); // Specify type of data format
			}


			glEnableClientState(GL_VERTEX_ARRAY);

			glBindBuffer(GL_ARRAY_BUFFER, tmp->meshPointer->Meshes_Vec[i]->VBO);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			// Index
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmp->meshPointer->Meshes_Vec[i]->IBO);
			// Draw
			glDrawElements((GLenum)GL_TRIANGLES, tmp->meshPointer->Meshes_Vec[i]->num_index, GL_UNSIGNED_INT, NULL);



			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


			if (tmp->meshPointer->Meshes_Vec[i]->normals!=nullptr && (DrawFaceNormals || DrawVertexNormals))
			{
				tmp->meshPointer->Meshes_Vec[i]->DrawNormals(1.0f,1,float3(0.0f, 0.5f, 0.5f), float3(0.0f, 1.0f, 0.0f),1.0f, DrawFaceNormals, DrawVertexNormals);

			}



		}



	}




}

bool ModuleAssets::CleanUp(Gameobject* tmp) {
	// detach log stream
	aiDetachAllLogStreams();


	for (int i = 0; i < tmp->meshPointer->Meshes_Vec.size();++i) {

		glDeleteBuffers(1, &tmp->meshPointer->Meshes_Vec[i]->VBO);
		glDeleteBuffers(1, &tmp->meshPointer->Meshes_Vec[i]->IBO);
		glDeleteBuffers(1, &tmp->meshPointer->Meshes_Vec[i]->UVC);


		// Manual Release for MMGR
		if (tmp->meshPointer->Meshes_Vec[i]->vertices != nullptr)
		{

			delete[] tmp->meshPointer->Meshes_Vec[i]->vertices; 

			tmp->meshPointer->Meshes_Vec[i]->vertices = nullptr;
		}
		if (tmp->meshPointer->Meshes_Vec[i]->indices != nullptr)
		{
			delete[] tmp->meshPointer->Meshes_Vec[i]->indices;

			tmp->meshPointer->Meshes_Vec[i]->indices = nullptr;

		}
		if (tmp->meshPointer->Meshes_Vec[i]->normals != nullptr)
		{
			delete[] tmp->meshPointer->Meshes_Vec[i]->normals;

			tmp->meshPointer->Meshes_Vec[i]->normals = nullptr;

		}
		if (tmp->meshPointer->Meshes_Vec[i]->normals_faces != nullptr)
		{
			delete[] tmp->meshPointer->Meshes_Vec[i]->normals_faces;

			tmp->meshPointer->Meshes_Vec[i]->normals_faces = nullptr;
		}
		if (tmp->meshPointer->Meshes_Vec[i]->normals_faces_pos != nullptr)
		{
			delete[] tmp->meshPointer->Meshes_Vec[i]->normals_faces_pos;

			tmp->meshPointer->Meshes_Vec[i]->normals_faces_pos = nullptr;
		}
		if (tmp->meshPointer->Meshes_Vec[i]->uv_coord != nullptr) 
		{
			delete[] tmp->meshPointer->Meshes_Vec[i]->uv_coord;

			tmp->meshPointer->Meshes_Vec[i]->uv_coord = nullptr;

		}
		if (tmp->meshPointer->Meshes_Vec[i] != nullptr) 
		{
			delete tmp->meshPointer->Meshes_Vec[i];

			tmp->meshPointer->Meshes_Vec[i] = nullptr;

		}

			
		
	}

	tmp->meshPointer->Meshes_Vec.clear();

		App->camera->premadeDist = -1.0f;
		App->camera->Reference = vec3(0, 0, 0);

		//TODO2
		//primitive clean up
	return true;
}

bool ModuleAssets::LoadFiles(const char* path) {

	std::string path_Aux = path;

	if (path_Aux.find(".fbx") != std::string::npos || path_Aux.find(".FBX") != std::string::npos) {
		App->Gameobjects->CleanUp();
		LoadMesh(path);
	}
	else if (path_Aux.find(".png") != std::string::npos || path_Aux.find(".dds") != std::string::npos) {

		//TODO: With inspector
		int id = -1;
		bool found = false;
		found = App->Textures->findTextureinList(path, id);
		if (found == false)
		{

			id=App->Textures->CreateTexture(path);
		}
		if (id != -1 )
		{
			Gameobject* activeGameObject = nullptr;
			activeGameObject = App->UI_Layer->HierarchyPanel->getActiveGameobject();
			if (App->Gameobjects->GameobjectList.size()>0) {

				if (activeGameObject!=nullptr)
				{
					activeGameObject->materialPointer->SetTextureID(id);
				}
				else
				{
					App->Gameobjects->GameobjectList[0]->materialPointer->SetTextureID(id);

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
		Gameobject* tmp = App->Gameobjects->CreateGameObject();
		tmp->CreateComponent(tmp, MESH, true);

		//insert name game obj
		std::string filename = path;
		std::size_t size = filename.find_last_of(".");
		std::size_t found = filename.find_last_of("/\\");
		size = (int)size - (int)found;
		filename = filename.substr(found + 1,size-1);
		tmp->nameGameObject = filename;

		if (Scene->HasMaterials()) {

			aiString Texture_path;

			aiMaterial* mat = Scene->mMaterials[0];
			mat->GetTexture(aiTextureType_DIFFUSE,0,&Texture_path);

			//Todo
			std::string filename = path;
			std::size_t found = filename.find_last_of("/\\");
			filename = filename.substr(0, found+1);
			filename.append(Texture_path.C_Str());


			tmp->CreateComponent(tmp, MATERIAL, true);
			tmp->materialPointer->CreateMaterial(filename);

		}

		for (uint i = 0; i < Scene->mNumMeshes; ++i)
		{
			AssetMesh* NewMesh = new AssetMesh;
			NewMesh->importMesh(Scene->mMeshes[i]);
			tmp->meshPointer->Meshes_Vec.push_back(NewMesh);

			for (int i = 0; i < tmp->meshPointer->Meshes_Vec.size(); ++i) {

				if (tmp->meshPointer->Meshes_Vec[i]->faraway > tmp->CameraDistance)
					tmp->CameraDistance = tmp->meshPointer->Meshes_Vec[i]->faraway;

				if (tmp->meshPointer->Meshes_Vec[i]->medX > tmp->xPos)
					tmp->xPos = tmp->meshPointer->Meshes_Vec[i]->medX;

				if (tmp->meshPointer->Meshes_Vec[i]->medY > tmp->yPos)
					tmp->yPos = tmp->meshPointer->Meshes_Vec[i]->medY;

				if (tmp->meshPointer->Meshes_Vec[i]->medZ > tmp->zPos)
					tmp->zPos = tmp->meshPointer->Meshes_Vec[i]->medZ;
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
	Gameobject* tmp = App->Gameobjects->CreateGameObject();
	tmp->CreateComponent(tmp, MESH, true);

	std::string nameid = std::to_string(tmp->ID);

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

	Primitives*aux = nullptr;
	aux = new Primitives(type);

	tmp->CreateComponent(tmp, MATERIAL, true);
	tmp->materialPointer->CreateMaterial();

	tmp->materialPointer->UseCheckered(true);

	/*tmp->materialPointer->UseCheckered(true);*/
	//TODO
	//make switch and pass parameter to function for what to create
	tmp->meshPointer->Primitives_Vec.push_back(aux);

	tmp->CameraDistance = aux->faraway;

	tmp->xPos = aux->medX;
	tmp->yPos = aux->medY;
	tmp->zPos = aux->medZ;
	

}

void ModuleAssets::CallbackEvent(const Event& event) {

	switch (event.type)
	{
	case Event::EventType::file_dropped:

		
		LoadFiles(event.string);

		break;
	}



}
