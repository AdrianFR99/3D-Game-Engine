#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "Maths.h"
#include "ModuleAssets.h"
#include"WindowHierarchy.h"
#include "ModuleGameobject.h"


ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
	EditorCam =CreateNewCamera();
	CurrentCam = EditorCam;


}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;
	
	/*App->GearConsole.AddLog(" Set 3D camera in position");*/

	return ret;
}

// Called to init variables
void ModuleCamera3D::Load(nlohmann::json& file)
{
	LOG("Load variables from Json to module Camera3D");
	App->GearConsole.AddLog(" Load Config variables for Camera ");

//	premadeDist = file["Modules"]["Camera"]["PremadeDistance"];
	mouse_sensitivity = file["Modules"]["Camera"]["Mouse_sensitivity"];
	wheel_speed = file["Modules"]["Camera"]["Wheel_speed"];
	camera_speed = file["Modules"]["Camera"]["Camera_speed"];

		
}

// Called to save variables
void ModuleCamera3D::Save(nlohmann::json& file)
{
	LOG("Save variables from Module Camera to Config");
	App->GearConsole.AddLog(" Save variables from Module Camera to Config ");

	//file["Modules"]["Camera"]["PremadeDistance"] = premadeDist;
	file["Modules"]["Camera"]["Mouse_sensitivity"] = mouse_sensitivity;
	file["Modules"]["Camera"]["Wheel_speed"] = wheel_speed;
	file["Modules"]["Camera"]["Camera_speed"] = camera_speed;

}


// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	DeleteAllCameras();

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	vec3 newPos(0,0,0);
	float cam_speed = camera_speed * dt;

	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		cam_speed = camera_speed * 2 * dt;

	// Mouse motion ----------------

	// while Right click freely look arrpund and be able to move with wasd keys
	if(App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{

		// WASP movement
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			EditorCam->MoveFront(cam_speed);
		if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
				EditorCam->MoveBack(cam_speed);
		if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			EditorCam->MoveLeft(cam_speed);
		if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) 
			EditorCam->MoveRight(cam_speed);

			
			Reference += newPos;
		// end of wasp move

		// mouse position and free look
			EditorCam->RotateYourself(App->input->GetMouseXMotion(), App->input->GetMouseYMotion());

		
		float Sensitivity = 0.25f;

		Position -= Reference;

		Position = Reference + Z * length(Position);
	}

	//mouse wheel

	if(App->input->GetMouseZ()==1)
		EditorCam->MoveFront(camera_speed);
	else if(App->input->GetMouseZ() == -1)
		EditorCam->MoveBack(camera_speed);
	


	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {

		//rotate around the object
		EditorCam->Orbit(float3(0, 0, 0), App->input->GetMouseXMotion(), App->input->GetMouseYMotion());

		
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_UP)
	{
		if (App->Gameobjects->GameobjectList.size() != 0)
		{
			Gameobject* centerOfView;
			centerOfView = App->UI_Layer->HierarchyPanel->getActiveGameobject();
			if (centerOfView != nullptr)
			{
				premadeDist = centerOfView->CameraDistance;
				Reference.x = centerOfView->xPos;
				Reference.y = centerOfView->yPos;
				Reference.z = centerOfView->zPos;
			}
			else
			{
				premadeDist = App->Gameobjects->GameobjectList[0]->CameraDistance;
				Reference.x = App->Gameobjects->GameobjectList[0]->xPos;
				Reference.y = App->Gameobjects->GameobjectList[0]->yPos;
				Reference.z = App->Gameobjects->GameobjectList[0]->zPos;
			}
			Position = Reference + Z * premadeDist;
		}
		else
		{
			Position = Reference + Z * 15.0;
		}

		//Reference= vec3(0, 0, 0);
		//Position = Reference + Z * premadeDist;
	}





	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void Camera3D::Look(const float3 &Position)
{
	float3 Targetdir = Position - CamFrustum.pos;

	float3x3 mAux = float3x3::LookAt(CamFrustum.front, Targetdir.Normalized(), CamFrustum.up, float3::unitY);

	CamFrustum.front = mAux.MulDir(CamFrustum.front).Normalized();
	CamFrustum.up = mAux.MulDir(CamFrustum.up).Normalized();

	
}

// -----------------------------------------------------------------




// -----------------------------------------------------------------

//void ModuleCamera3D::CalculateViewMatrix()
//{
//	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f,
//		X.y, Y.y, Z.y, 0.0f,
//		X.z, Y.z, Z.z, 0.0f,
//		-dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
//	ViewMatrixInverse = inverse(ViewMatrix);
//}

//// Called for rotating in a point
//void Camera3D::Rotate(const float&rotationX,const float&rotationY)
//{
//	/*Reference = ReferencetoRot;*/
//
//	/*X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
//	Y = cross(Z, X);
//
//	CalculateViewMatrix();*/
//
//	//Create quaternions with its determinant rotation
//	Quat RotX=Quat::RotateY(rotationX);//Quat::RotateAxisAngle(Frustum.Up,rotationX);
//	Quat RotY = Quat::RotateZ(rotationY);//Quat::RotateAxisAngle(frustum.WorldRight(),rotationY);
//
//	//Multiply quats w 
//	//SetToFront(RotX.Mul(CamFrustum.Front()).Normalized());
//	//SetToFront(RotY.Mul(CamFrustum.Front()).Normalized());//
//
//	//SetToUp(RotX.Mul(CamFrustum.Up).Normalized());//
//	//SetToUp(RotY.Mul(CamFrustum.Up()).Normalized());
//}
//


 Camera3D*ModuleCamera3D::CreateNewCamera() {


	Camera3D*aux=nullptr;
	aux = new Camera3D;
	VecCameras.push_back(aux);
	
	return aux;
}
 bool ModuleCamera3D::DeleteCamera(Camera3D*target) {


	 RELEASE(target);

	 return true;
 }

 bool ModuleCamera3D::DeleteAllCameras() {

	 for(int i=0;i<VecCameras.size();++i)
	 RELEASE(VecCameras[i]);

	 return true;
 }

 const float* ModuleCamera3D::GLViewMatrix() {

	 float4x4 viewGL=CurrentCam->GetViewMatrix();
	 return  viewGL.Transposed().ptr();

 }

 const float* ModuleCamera3D::GLProjectionMatrix() {


	 float4x4 projGL = CurrentCam->GetProjectionMatrix();
	 return  projGL.Transposed().ptr();


 }
 
////similar to rotate, to orbit
void Camera3D::Orbit(const float3& orbit_center, const float& motion_x, const float& motion_y)
{
	
	float3 focus = CamFrustum.pos - orbit_center;

	Quat Rotatey(CamFrustum.up, motion_x*App->camera->mouse_sensitivity);
	Quat Rotatex(CamFrustum.WorldRight(),motion_y*App->camera->mouse_sensitivity);

	focus = Rotatex.Transform(focus);
	focus = Rotatey.Transform(focus);

	SetCamPos(focus + orbit_center);

	Look(orbit_center);
}

void Camera3D::RotateYourself(const float& motion_x, const float& motion_y)
{

	Quat rotation_x = Quat::RotateY(motion_x*App->camera->mouse_sensitivity);
	SetToFront(rotation_x.Mul(CamFrustum.front).Normalized());
	SetToUp(rotation_x.Mul(CamFrustum.up).Normalized());

	Quat rotation_y = Quat::RotateAxisAngle(CamFrustum.WorldRight(), motion_y*App->camera->mouse_sensitivity);
	SetToFront(rotation_y.Mul(CamFrustum.front).Normalized());
	SetToUp(rotation_y.Mul(CamFrustum.up).Normalized());

}

	



//camera3D Class----------------

Camera3D::Camera3D() {


	SetCamPos(float3(0.f,10.f,-10.f));
	SetToFront(float3::unitZ);
	SetToUp(float3::unitY);
	SetFarPlane_Dist(10000.0f);
	SetNearPlane_Dist(0.1f);
	SetTypeFrustum(PerspectiveFrustum);
	
	SetVeticalFOV(30);
	SetHorizontalFOV(60);
	SetAspectRatio((float)SCREEN_WIDTH/ (float)SCREEN_HEIGHT);
	SetFOV(90);

}

const void Camera3D::SetCamPos(const float3&newpos) {


	CamFrustum.pos = newpos;
	UpdateMatrices();

}

const void Camera3D::SetToFront(const float3&frontDir) {



	CamFrustum.front = frontDir;
	UpdateMatrices();


}

const void Camera3D::SetToUp(const float3&upDir) {

	CamFrustum.up = upDir;
	UpdateMatrices();
	
}

const void Camera3D::MoveUp(const float&Displacement){


	if (Displacement > 0) {
	
		float3 mov = float3::zero;
		mov += CamFrustum.up*Displacement;
		CamFrustum.Translate(mov);

	}
}

const void Camera3D::MoveDown(const float&Displacement) {



	if (Displacement > 0) {

		float3 mov = float3::zero;
		mov -= CamFrustum.up*Displacement;
		CamFrustum.Translate(mov);

	}
}
const void Camera3D::MoveFront(const float&Displacement) {


	if (Displacement > 0) {

		float3 mov = float3::zero;
		mov += CamFrustum.front*Displacement;
		CamFrustum.Translate(mov);

	}


}
const void Camera3D::MoveBack(const float&Displacement) {


	if (Displacement > 0) {

		float3 mov = float3::zero;
		mov -= CamFrustum.front*Displacement;
		CamFrustum.Translate(mov);

	}


}
const void Camera3D::MoveLeft(const float&Displacement) {


	if (Displacement > 0) {

		float3 mov = float3::zero;
		mov -= CamFrustum.WorldRight().Normalized()*Displacement;
		CamFrustum.Translate(mov);

	}
}
const void Camera3D::MoveRight(const float&Displacement) {


	if (Displacement > 0) {

		float3 mov = float3::zero;
		mov += CamFrustum.WorldRight().Normalized()*Displacement;
		CamFrustum.Translate(mov);

	}
}

const Frustum Camera3D::GetFrustum()const { return CamFrustum; }

const float Camera3D::GetNearPlane()const {return CamFrustum.nearPlaneDistance;}
const float Camera3D::GetFarPlane()const {return CamFrustum.farPlaneDistance;}

const float3x4 Camera3D::GetWorldMatrix()const { return CamFrustum.WorldMatrix(); }
const float3x4	Camera3D::GetViewMatrix() const { return CamFrustum.ViewMatrix(); }
const float4x4	Camera3D::GetProjectionMatrix() const { return CamFrustum.ProjectionMatrix(); }
const float4x4	Camera3D::GetViewProjectedMatrix() const { return CamFrustum.ViewProjMatrix(); }



const void Camera3D::SetHorizontalFOV(const float&HorizFOV) {


	CamFrustum.horizontalFov = HorizFOV;
	AspectRatio = CamFrustum.AspectRatio();
	UpdateProjectionMatrices();
}
const void Camera3D::SetVeticalFOV(const float&VertFOV) {

	CamFrustum.verticalFov = VertFOV;
	AspectRatio = CamFrustum.AspectRatio();
	UpdateProjectionMatrices();
}
const void Camera3D::SetAspectRatioAndVFOV(const float&AspectRatio_,const float&VertFOV) {


	CamFrustum.horizontalFov =2.0f*Atan((Tan(VertFOV*0.5f) / AspectRatio));
	AspectRatio = AspectRatio_;
	UpdateProjectionMatrices();
}
const void Camera3D::SetAspectRatioAndHFOV(const float&AspectRatio_, const float&HorizFOV) {


	CamFrustum.verticalFov = Atan(Tan(HorizFOV*0.5f)*AspectRatio)/0.5f;
	AspectRatio = AspectRatio_;
	UpdateProjectionMatrices();
}

const void Camera3D::SetAspectRatio(const float&Ratio) {


	SetAspectRatioAndVFOV(Ratio,CamFrustum.verticalFov);

}

const void Camera3D::SetFOV(const float&VFOV) {


	SetAspectRatioAndVFOV(AspectRatio, DEGTORAD*VFOV);

}


const void Camera3D::SetFarPlane_Dist(const float&Distance) {

	CamFrustum.farPlaneDistance = Distance;
	
	UpdateProjectionMatrices();
}

const void Camera3D::SetNearPlane_Dist(const float&Distance) {

	CamFrustum.nearPlaneDistance = Distance;
	UpdateProjectionMatrices();
}

const void Camera3D::SetTypeFrustum(FrustumType type) {

	CamFrustum.type = type;
}

const void Camera3D::UpdateMatrices() {

	World_Matrix = CamFrustum.WorldMatrix();
	View_Matrix = CamFrustum.ViewMatrix();
	Projection_Matrix = CamFrustum.ProjectionMatrix();
	ViewProjected_Matrix = Projection_Matrix * View_Matrix;

}

const void Camera3D::UpdateProjectionMatrices() {

	Projection_Matrix = CamFrustum.ProjectionMatrix();
	ViewProjected_Matrix= Projection_Matrix * View_Matrix;

}