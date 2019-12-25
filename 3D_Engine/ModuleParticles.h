#ifndef __ModuleParticles_h__
#define __ModuleParticles_h__

#include "Module.h"

class ModuleParticles :
	public Module
{
public:
	ModuleParticles(Application* app, bool start_enabled);
	~ModuleParticles();

	bool Start() override;
	bool CleanUp() override;

	void AddParticleSystem();
	void RemoveParticleSystem();

	bool DrawParticleSystem();
	   






};

#endif