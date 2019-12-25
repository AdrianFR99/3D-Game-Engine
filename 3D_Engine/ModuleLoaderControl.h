#ifndef __MODULE_IMPORTER_H__
#define __MODULE_IMPORTER_H__

#include "Module.h"

class SceneLoader;

class ModuleImporter : public Module
{
public:
	// --- Basic ---
	ModuleImporter(Application* app, bool start_enabled);
	~ModuleImporter();
	bool Init(nlohmann::json file);
	bool Start();
	bool CleanUp();
	// -- SDL Event take
	void CallbackEvent(const Event& event) override;

	// --- Getters ---
	SceneLoader* GetImporterScene() const;

	

private:
	SceneLoader* SceneImporter = nullptr;

};

#endif
