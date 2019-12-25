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
		App->FileSystem->NormalizePath(DroppedFile_path);

		// 3D model case
		if (DroppedFile_path.find(".fbx") != std::string::npos || DroppedFile_path.find(".FBX") != std::string::npos)
		{

			SceneImporter->Import(DroppedFile_path.data());
		}
		else if (DroppedFile_path.find(".png") != std::string::npos || DroppedFile_path.find(".PNG") != std::string::npos || DroppedFile_path.find(".dds") != std::string::npos || DroppedFile_path.find(".DDS") != std::string::npos || DroppedFile_path.find(".tga") != std::string::npos || DroppedFile_path.find(".TGA") != std::string::npos)
		{
			SceneImporter->ImporterMaterial->import2(DroppedFile_path.data());

		

		}
	}



}


SceneLoader * ModuleImporter::GetImporterScene() const
{
	return SceneImporter;
}

