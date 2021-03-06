#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#include "DebugDraw.h"

#define MAX_LIGHTS 8



typedef unsigned int GLuint;
typedef struct par_shapes_mesh_s;


class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init(nlohmann::json config);
	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	void Load(nlohmann::json& file);
	void Save(nlohmann::json& file);
	void ReloadFromConfig();
	void OnResize(int width, int height);
	void changeLight(bool value);
	void DrawGrindAndAxis();

	uint LoadTextureBuffer(const void * texture, uint size, int format, int width, int height, uint wrap_s, uint wrap_t, uint mag, uint min);

	//changers
	const void ChangeAmbientSettings (bool & active, const float color [4] ) const;
	const void ChangeDiffuseSettings(bool & active, const float color[4] ) const;
	const void ChangeSpecularSettings(bool & active, const float color[4] ) const;

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	bool Vsync = false;

	bool DrawTree = true;



private:
	uint Light_num = 0;
};