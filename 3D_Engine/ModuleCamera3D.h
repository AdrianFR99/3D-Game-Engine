#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	void Rotate(const const vec3 &Reference);
	float* GetViewMatrix();

	// camera movement
	void Orbit(const vec3 & rotate_center, const float & motion_x, const float & motion_y);

private:

	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;

	

private:

	mat4x4 ViewMatrix, ViewMatrixInverse;
};