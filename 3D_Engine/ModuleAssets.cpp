
#include "Application.h"
#include "ModuleAssets.h"


#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include "mmgr/mmgr.h"

#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>



Asset::Asset(Asset_Type type)
{
	
}

Asset::~Asset()
{



}

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

	

}

bool ModuleAssets::CleanUp() {
	// detach log stream
	aiDetachAllLogStreams();


	/*for (int i = 0; i < Meshes_Vec.size();++i) {
		
		glDeleteBuffers(2,Meshes_Vec[i]->buffer);
		glDeleteBuffers(1,&Meshes_Vec[i]->VAO);




	}*/


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

			//Meshes_Vec.push_back(NewMesh);

		}
	}
	else
		LOG("|[error]: Error loading scene %s", path);

	return true;

}