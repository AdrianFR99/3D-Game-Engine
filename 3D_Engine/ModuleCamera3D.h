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
	ALIGN_CLASS_TO_16

	Camera3D();
	Camera3D(float3&pos,float& FarPlane, float& NearPlane);
	//movement
	const void MoveUp(const float&Displacement);
	const void MoveDown(const float&Displacement);
	const void MoveFront(const float&Displacement);
	const void MoveBack(const float&Displacement);
	const void MoveLeft(const float&Displacement);
	const void MoveRight(const float&Displacement);
	//Rotation
	void Look(const float3 &Position);
	void Orbit(const float3 & rotate_center, const float & motion_x, const float & motion_y);
	void RotateYourself(const float& motion_x, const float& motion_y);
	void CenterCam(const float3&focus,const float&distance);

	//Getters

	//Frustum
	const Frustum GetFrustum()const;
	//Matrices
	const float3x4 GetWorldMatrix()const;
	const float3x4	GetViewMatrix() const ;
	const float4x4	GetProjectionMatrix() const ;
	const float4x4	GetViewProjectedMatrix() const ;
	//planes
	const float GetNearPlane()const;
	const float GetFarPlane()const;

	//Setters

	//CamPos & orientation
	const void SetCamPos(const float3&newpos);
	const void SetToFront(const float3&frontDir);//Z
	const void SetToUp(const float3&upDir);//Y

	//changes the HFOV independently of the Aspect ratio or the VFOV
	const void SetHorizontalFOV(const float&HorizFOV);
	//changes the VFOV independently of the Aspect ratio or the HFOV
	const void SetVeticalFOV(const float&VertFOV);
	//changes the HFOV depending on VFOV and the Aspect
	const void SetAspectRatioAndVFOV(const float&AspectRatio_, const float&VertFOV);
	//changes the VFOV depending on HFOV and the Aspect
	const void SetAspectRatioAndHFOV(const float&AspectRatio_, const float&HorizFOV);
	//We use SetAspectRatioAndVFOV and set VFOV as the current one, changing AspectRatio and HFOV and mantainig the VFOV
	const void SetAspectRatio(const float&Ratio);
	//We use SetAspectRatioAndVFOV and set AspectRatio as the current one, changing VFOV and HFOV and mantainig the Ratio
	const void SetFOV(const float&VFOV);

	//Frustum planes
	const void SetNearPlane_Dist(const float&Distance);
	const void SetFarPlane_Dist(const float&Distance);
	//type
	const void SetTypeFrustum(FrustumType type);
	
	//Matrices Handlers
	const void UpdateMatrices();
	const void UpdateProjectionMatrices();

public:

	float AspectRatio;
	float FOV;
	

public:

	bool inverseCameraControls=false;


private:

	Frustum CamFrustum;

	float3x4 World_Matrix;
	float3x4 View_Matrix;
	float4x4 Projection_Matrix;
	float4x4 ViewProjected_Matrix;
};


class ModuleCamera3D : public Module
{
public:
	ALIGN_CLASS_TO_16

	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);

	bool CleanUp();
	void Load(nlohmann::json& file);
	void Save(nlohmann::json& file);
	
	
	//Camera creatiom Handlers
	
	 Camera3D*CreateNewCamera();
	 Camera3D*CreateNewCamera(float3&pos,float&FarPlane,float&NearPlane);
	
	 bool DeleteCamera(Camera3D*target);
	 bool DeleteAllCameras();

	// camera movement
	

	 const float* GLViewMatrix();
	 const float* GLProjectionMatrix();



	/*void CalculateViewMatrix();*/

public:
	
	vec3 X, Y, Z, Position, Reference;
	float premadeDist = -1.0f;
	

	float mouse_sensitivity =0.0f;
	float wheel_speed = 0.0f;
	float camera_speed = 10.0f;


	Camera3D*CurrentCam = nullptr;
	Camera3D*EditorCam = nullptr;

	float3 PointOfFocus;
private:

	std::vector<Camera3D*>VecCameras;
	mat4x4 ViewMatrix, ViewMatrixInverse;
};

#endif//CAMERA3D
#endif//MODULECAMERA3D