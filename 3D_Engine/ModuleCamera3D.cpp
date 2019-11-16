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
		//RotateYourself(App->input->GetMouseXMotion(), App->input->GetMouseYMotion());

		
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
		//Orbit(vec3(0, 0, 0), App->input->GetMouseXMotion(), App->input->GetMouseYMotion());

		
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

	// Recalculate matrix -------------
	CalculateViewMatrix();



	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}



// -----------------------------------------------------------------

void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f,
		X.y, Y.y, Z.y, 0.0f,
		X.z, Y.z, Z.z, 0.0f,
		-dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}

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
//void Camera3D::Orbit(const vec3& orbit_center, const float& motion_x, const float& motion_y)
//{
//	Reference = orbit_center;
//
//	int dx = -motion_x;
//	int dy = -motion_y;
//
//	Position -= Reference;
//
//	if (dx != 0)
//	{
//		float DeltaX = (float)dx;
//
//		// Rotate arround the y axis
//		X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
//		Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
//		Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
//	}
//
//	if (dy != 0)
//	{
//		float DeltaY = (float)dy;
//
//		// Rotate arround the X direction
//		Y = rotate(Y, DeltaY, X);
//		Z = rotate(Z, DeltaY, X);
//	}
//
//	Position = Reference + Z * length(Position);
//}
//
//void Camera3D::RotateYourself(const float& motion_x, const float& motion_y)
//{
//	Reference = Position;
//
//	int dx = -motion_x;
//	int dy = -motion_y;
//
//	Position -= Reference;
//
//	if (dx != 0)
//	{
//		float DeltaX = (float)dx * mouse_sensitivity;
//
//		X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
//		Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
//		Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
//	}
//
//	if (dy != 0)
//	{
//		float DeltaY = (float)dy * mouse_sensitivity;
//
//		Y = rotate(Y, DeltaY, X);
//		Z = rotate(Z, DeltaY, X);
//	}
//
//	Position = Reference + Z * length(Position);
//}


//camera3D Class----------------

Camera3D::Camera3D() {


	SetCamPos(float3(0.f,10.f,-10.f));
	SetToFront(float3::unitZ);
	SetToUp(float3::unitY);
	SetFarPlane_Dist(10000.0f);
	SetNearPlane_Dist(0.1f);
	SetTypeFrustum(PerspectiveFrustum);

	SetAspectRatio(1.3f);
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
}
const void Camera3D::SetVeticalFOV(const float&VertFOV) {

	CamFrustum.verticalFov = VertFOV;
	AspectRatio = CamFrustum.AspectRatio();
}
const void Camera3D::SetAspectRatioAndVFOV(const float&AspectRatio_,const float&VertFOV) {


	CamFrustum.horizontalFov =2.0f*Atan((Tan(VertFOV*0.5f) / AspectRatio));
	AspectRatio = AspectRatio_;

}
const void Camera3D::SetAspectRatioAndHFOV(const float&AspectRatio_, const float&HorizFOV) {


	CamFrustum.verticalFov = Atan(Tan(HorizFOV*0.5f)*AspectRatio)/0.5f;
	AspectRatio = AspectRatio_;

}

const void Camera3D::SetAspectRatio(const float&Ratio) {


	SetAspectRatioAndVFOV(Ratio,CamFrustum.verticalFov);

}

const void Camera3D::SetFOV(const float&VFOV) {


	SetAspectRatioAndVFOV(AspectRatio, DEGTORAD*VFOV);

}


const void Camera3D::SetFarPlane_Dist(const float&Distance) {

	CamFrustum.nearPlaneDistance = CamFrustum.nearPlaneDistance;
	CamFrustum.farPlaneDistance = Distance;
	UpdateProjectionMatrices();
}

const void Camera3D::SetNearPlane_Dist(const float&Distance) {

	CamFrustum.nearPlaneDistance = Distance;
	CamFrustum.farPlaneDistance =CamFrustum.farPlaneDistance;
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