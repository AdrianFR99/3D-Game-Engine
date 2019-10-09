#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"



#define MAX_LIGHTS 8



typedef unsigned int GLuint;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	void changeLight(bool value);



public:

	void CreateCubeIndices(int posX, int posZ, int posY,int AristaMagnitude,float*index);

	void CreateCubeVertices(int posX, int posZ, int posY, int AristaMagnitude, float*vertices);
	


public:


	GLuint buffer[3];

	GLuint vao;

	uint p;


	uint ID_indices = 1;
	uint num_indices = 36;

	uint ID_Vertices = 1;
	uint num_Vertices =24;


	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};