
#include "Application.h"
#include "ModuleAssets.h"


#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include "mmgr/mmgr.h"



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

	// detach log stream
	aiDetachAllLogStreams();

}

bool ModuleAssets::CleanUp() {


	return true;
}

bool ModuleAssets::ImportFiles(const char* path) {
	

	ImportMesh(path);

	return true;
}

bool ModuleAssets::ImportMesh(const char* path) {

	const aiScene* Scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (Scene != nullptr && Scene->HasMeshes())
	{
		for (uint i = 0; i < Scene->mNumMeshes; ++i)
		{
		





		}
	}
	else
		LOG("|[error]: Error loading scene %s", path);

	return true;

}