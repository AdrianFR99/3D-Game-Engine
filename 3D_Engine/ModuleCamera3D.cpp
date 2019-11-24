#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "Maths.h"
#include "ModuleAssets.h"
#include"WindowHierarchy.h"
#include "ModuleGameobject.h"
#include "ComponentTransform.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	float3 aux={ 0.0f,10.0f,-15.0f };
	float Near = 0.1f;
	float Far = 1000.0f;

	EditorCam =CreateNewCamera(aux,Far,Near);
	CurrentCam = EditorCam;


}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;
	PointOfFocus = float3(0.0f, 0.0f, 0.0f);
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

	 float cam_speed = camera_speed * dt;

	 if(App->UI_Layer->HierarchyPanel->getActiveGameobject()!=nullptr)
	 PointOfFocus = App->UI_Layer->HierarchyPanel->getActiveGameobject()->transformPointer->GetPosition();

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


		// mouse position and free look
			EditorCam->RotateYourself(App->input->GetMouseXMotion(), App->input->GetMouseYMotion());


		float Sensitivity = 0.25f;

	}

	//mouse wheel

	if(App->input->GetMouseZ()==1)
		EditorCam->MoveFront(camera_speed);
	else if(App->input->GetMouseZ() == -1)
		EditorCam->MoveBack(camera_speed);




	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {

		//rotate around the object
		EditorCam->Orbit(PointOfFocus, App->input->GetMouseXMotion(), App->input->GetMouseYMotion());


	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_UP)
	{


		EditorCam->CenterCam(PointOfFocus,20.0f);

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


 Camera3D*ModuleCamera3D::CreateNewCamera() {


	Camera3D*aux=nullptr;
	aux = new Camera3D;
	VecCameras.push_back(aux);

	return aux;
}

 Camera3D*ModuleCamera3D::CreateNewCamera(float3&pos, float&FarPlane, float&NearPlane) {


	 Camera3D*aux = nullptr;
	 aux = new Camera3D(pos,FarPlane,NearPlane);
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

	 float4x4 viewGL=CurrentCam->GetFrustum().ViewMatrix();
	 return  viewGL.Transposed().ptr();

 }

 const float* ModuleCamera3D::GLProjectionMatrix() {


	 float4x4 projGL =CurrentCam->GetFrustum().ProjectionMatrix();
	 return  projGL.Transposed().ptr();


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

Camera3D::Camera3D(float3&pos, float& FarPlane, float& NearPlane) {

	SetCamPos(pos);
	SetToFront(float3::unitZ);
	SetToUp(float3::unitY);
	SetFarPlane_Dist(FarPlane);
	SetNearPlane_Dist(NearPlane);
	SetTypeFrustum(PerspectiveFrustum);

	SetVeticalFOV(30);
	SetHorizontalFOV(60);
	SetFOV(90);
	SetAspectRatio((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);



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

////similar to rotate, to orbit
void Camera3D::Orbit(const float3& orbit_center, const float& motion_x, const float& motion_y)
{

	float3 focus = CamFrustum.pos - orbit_center;

	Quat Rotatey(CamFrustum.up, motion_x*App->camera->mouse_sensitivity);
	Quat Rotatex(CamFrustum.WorldRight(), motion_y*App->camera->mouse_sensitivity);

	focus = Rotatex.Transform(focus);
	focus = Rotatey.Transform(focus);

	SetCamPos(focus + orbit_center);

	Look(orbit_center);
}

void Camera3D::RotateYourself(const float& motion_x, const float& motion_y)
{
	float motionx;
	float motiony;

	if (inverseCameraControls == false) {
		 motionx = -motion_x;
		 motiony = -motion_y;
	}
	else {

		motionx =motion_x;
		motiony =motion_y;
	}


	Quat rotation_x = Quat::RotateY(motionx*App->camera->mouse_sensitivity);
	SetToFront(rotation_x.Mul(CamFrustum.front).Normalized());
	SetToUp(rotation_x.Mul(CamFrustum.up).Normalized());

	Quat rotation_y = Quat::RotateAxisAngle(CamFrustum.WorldRight(), motiony*App->camera->mouse_sensitivity);
	SetToFront(rotation_y.Mul(CamFrustum.front).Normalized());
	SetToUp(rotation_y.Mul(CamFrustum.up).Normalized());

}

void  Camera3D::CenterCam(const float3&focus, const float&distance) {

	float3 direction = CamFrustum.pos - focus;
	SetCamPos(direction.Normalized() * distance);
	Look(focus);
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

const float3x4 Camera3D::GetWorldMatrix()const { return World_Matrix; }
const float3x4	Camera3D::GetViewMatrix() const { return View_Matrix; }
const float4x4	Camera3D::GetProjectionMatrix() const { return Projection_Matrix; }
const float4x4	Camera3D::GetViewProjectedMatrix() const { return ViewProjected_Matrix; }



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


	CamFrustum.horizontalFov =2.0f*Atan(Tan(VertFOV*0.5f) * AspectRatio_);
	AspectRatio = AspectRatio_;
	UpdateProjectionMatrices();
}


const void Camera3D::SetAspectRatio(const float&Ratio) {


	SetAspectRatioAndVFOV(Ratio,CamFrustum.verticalFov);

}

const void Camera3D::SetFOV(const float&VFOV) {


	SetVeticalFOV(DEGTORAD*VFOV);
	SetAspectRatio(AspectRatio = CamFrustum.AspectRatio());



	FOV = VFOV;
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


bool ModuleCamera3D::InsideFrustum(const AABB&Element,Frustum&fr) {


	float3 Corners[8];
	Element.GetCornerPoints(Corners);



	for (int i = 0; i < 6; ++i) {


		uint counter=8;

		for (int j = 0; j < 8;++j) {


			if (fr.GetPlane(i).IsOnPositiveSide(Corners[j]))
				--counter;

 		}
		if (counter == 0) {
			return false;

		}

	}


	return true;

}

void ModuleCamera3D::DrawIfInside(Frustum&fr) {


	std::vector<Gameobject*>Aux = App->Gameobjects->GameobjectList;

	for(std::vector<Gameobject*>::iterator it = Aux.begin(); it != Aux.end();++it)
	{

		if (InsideFrustum((*it)->GetAABB(),fr)) {

			(*it)->DrawGO=true;
			(*it)->Draw();

     	}
		else {
			(*it)->DrawGO = false;

		}
	}



}
