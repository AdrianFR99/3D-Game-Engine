
#include "Application.h"
#include "ModuleAssets.h"
#include "AssetMesh.h"
#include "Event.h"
#include "Primitives.h"

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

	//LoadFiles(App->AssetModel.data());

	Primitives*aux = nullptr;
	aux = new Primitives(Primitive_Type::CYLINDER);
	
	return true;
}


void ModuleAssets::Draw() {

	glEnable(GL_TEXTURE_2D);


	for (int i = 0; i < Meshes_Vec.size();++i) {

		if (Meshes_Vec[i] != nullptr) {
			// Vertex
			
			
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			
			if(App->Textures->CurrentTex!=nullptr)
			glBindTexture(GL_TEXTURE_2D,App->Textures->CurrentTex->id); // start using texture
			else
			glBindTexture(GL_TEXTURE_2D, App->Textures->CheckeredID); // start using texture
			
			glActiveTexture(GL_TEXTURE0);
			glBindBuffer(GL_ARRAY_BUFFER, Meshes_Vec[i]->UVC); // start using created buffer (tex coords)
			glTexCoordPointer(2, GL_FLOAT, 0, NULL); // Specify type of data format			
			
			
			glEnableClientState(GL_VERTEX_ARRAY);

			glBindBuffer(GL_ARRAY_BUFFER, Meshes_Vec[i]->VBO);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			// Index
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Meshes_Vec[i]->IBO);
			// Draw
			glDrawElements((GLenum)GL_TRIANGLES,Meshes_Vec[i]->num_index, GL_UNSIGNED_INT, NULL);



			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			

			if (Meshes_Vec[i]->normals!=nullptr)
			{
				Meshes_Vec[i]->DrawNormals(1.0f,1,float3(0.0f, 0.5f, 0.5f), float3(0.0f, 1.0f, 0.0f),1.0f);
			
			}


		
		}

			   

	}


	if (Primitives_Vec.size() > 0) {

		for (int i = 0; i < Primitives_Vec.size(); ++i)
			Primitives_Vec[i]->Draw();
		
	}
	

}

bool ModuleAssets::CleanUp() {
	// detach log stream
	aiDetachAllLogStreams();


	for (int i = 0; i < Meshes_Vec.size();++i) {
		
		glDeleteBuffers(1,&Meshes_Vec[i]->VBO);
		glDeleteBuffers(1,&Meshes_Vec[i]->IBO);
		glDeleteBuffers(1, &Meshes_Vec[i]->UVC);
		

		RELEASE_ARRAY(Meshes_Vec[i]->vertices);
		RELEASE_ARRAY(Meshes_Vec[i]->indices);
		RELEASE_ARRAY(Meshes_Vec[i]->normals);
		RELEASE_ARRAY(Meshes_Vec[i]->normals_faces);
		RELEASE_ARRAY(Meshes_Vec[i]->normals_faces_pos);
		RELEASE_ARRAY(Meshes_Vec[i]->uv_coord);

		//delete(Meshes_Vec[i]);
		RELEASE(Meshes_Vec[i]);
	}

		Meshes_Vec.clear();

	return true;
}

bool ModuleAssets::LoadFiles(const char* path) {
	
	std::string path_Aux = path;

	if (path_Aux.find(".fbx") != std::string::npos)
		LoadMesh(path);
	else if (path_Aux.find(".png") != std::string::npos || path_Aux.find(".dds") != std::string::npos)
		App->Textures->CreateTexture(path);
	

	App->GearConsole.AddLog(" Loading File %s",path);

	return true;
}

bool ModuleAssets::LoadMesh(const char* path) {

	App->GearConsole.AddLog(" Loading Mesh from %s ",path);

	const aiScene* Scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (Scene != nullptr && Scene->HasMeshes())
	{
		for (uint i = 0; i < Scene->mNumMeshes; ++i)
		{

			AssetMesh* NewMesh = new AssetMesh;

			NewMesh->importMesh(Scene->mMeshes[i]);

			Meshes_Vec.push_back(NewMesh);

		}
	}
	else
	{

		LOG("|[error]: Error loading scene %s", path);
		App->GearConsole.AddLog(" Error Loading Mesh, no meshes or irregular path ");
	}

	return true;

}

void ModuleAssets::CallbackEvent(const Event& event) {

	switch (event.type)
	{
	case Event::EventType::file_dropped:

	
		LoadFiles(event.string);

		break;
	}



}