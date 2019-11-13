#ifndef __MODULECAMERA3D_H__
#ifndef __CAMERA3D_H__

#define __MODULECAMERA3D_H__
#define __CAMERA3D_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "MathGeoLib/include/MathBuildConfig.h"

class Camera3D {


	Camera3D(){}
public:
	//setters

	void SetCamPos(const float3&newpos);
	void SetToFront(const float3&frontDir);
	void SetToUp(const float3&upDir);


	//getters

private:

	Frustum CamFrustrum;



};


class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);

	bool CleanUp();
	void Load(nlohmann::json& file);
	void Save(nlohmann::json& file);
	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	void Rotate(const const vec3 &Reference);
	
	float* GetViewMatrix();

	//Camera creatiom Handlers

	 Camera3D*CreateNewCamera();
	 bool DeleteCamera(Camera3D*target);
	 bool DeleteAllCameras();

	// camera movement
	void Orbit(const vec3 & rotate_center, const float & motion_x, const float & motion_y);
	void RotateYourself(const float& motion_x, const float& motion_y);

private:

	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;
	float premadeDist = -1.0f;
	

	float mouse_sensitivity =0.0f;
	float wheel_speed = 0.0f;
	float camera_speed = 0.0f;

private:

	Camera3D*CurrentCam=nullptr;
	Camera3D*EditorCam=nullptr;

	std::vector<Camera3D*>VecCameras;

	mat4x4 ViewMatrix, ViewMatrixInverse;
};

#endif//CAMERA3D
#endif//MODULECAMERA3D