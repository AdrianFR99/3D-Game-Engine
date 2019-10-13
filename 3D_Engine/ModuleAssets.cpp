
#include "Application.h"
#include "ModuleAssets.h"
#include "AssetMesh.h"



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


void ModuleAssets::Draw() {

	

	for (int i = 0; i < Meshes_Vec.size();++i) {

		glBindVertexArray(Meshes_Vec[i]->VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Meshes_Vec[i]->IBO);

		glDrawElements(GL_TRIANGLES,Meshes_Vec[i]->num_index,GL_UNSIGNED_INT, NULL);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		glBindVertexArray(0);

	}



}

bool ModuleAssets::CleanUp() {
	// detach log stream
	aiDetachAllLogStreams();


	for (int i = 0; i < Meshes_Vec.size();++i) {
		
		glDeleteBuffers(1,&Meshes_Vec[i]->VBO);
		glDeleteBuffers(1,&Meshes_Vec[i]->IBO);
		glDeleteBuffers(1,&Meshes_Vec[i]->VAO);

		RELEASE_ARRAY(Meshes_Vec[i]->vertices);
		RELEASE_ARRAY(Meshes_Vec[i]->indices);
	
		delete(Meshes_Vec[i]);
	}


	return true;
}

bool ModuleAssets::LoadFiles(const char* path) {
	

	LoadMesh(path);

	return true;
}

bool ModuleAssets::LoadMesh(const char* path) {

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
		LOG("|[error]: Error loading scene %s", path);

	return true;

}