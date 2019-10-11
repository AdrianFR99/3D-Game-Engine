#include "ModuleAssets.h"
#include "Globals.h"
#include "Application.h"

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


	return true;
}

bool ModuleAssets::Start() {


	return true;
}

void ModuleAssets::Draw() {



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