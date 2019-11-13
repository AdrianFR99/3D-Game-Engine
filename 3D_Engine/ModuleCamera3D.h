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

public:

	Camera3D() {}

	const void SetCamPos(const float3&newpos);
	const void SetToFront(const float3&frontDir);
	const void SetToUp(const float3&upDir);
	   
	//movement
	const void MoveUp(const float&Displacement);
	const void MoveDown(const float&Displacement);
	const void MoveFront(const float&Displacement);
	const void MoveBack(const float&Displacement);
	const void MoveLeft(const float&Displacement);
	const void MoveRight(const float&Displacement);


	void UpdateMatrices();

private:

	Frustum CamFrustrum;

	float3x4 World_Matrix;
	float3x4 View_Matrix;
	float4x4 Projection_Matrix;

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