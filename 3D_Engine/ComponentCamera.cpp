#include "ComponentCamera.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ComponentTransform.h"


ComponentCamera::ComponentCamera(Gameobject * owner, CompType newtype):Component(newtype, owner)
{

	float3 pos = belongsTo->transformPointer->GetPosition();
	float Near = 5.0f;
	float Far = 20.0f;

	CameraComponent = App->camera->CreateNewCamera(pos,Far, Near);

}


ComponentCamera::~ComponentCamera()
{
}

void ComponentCamera::Draw() {

	DebugDrawFrustum(&CameraComponent->GetFrustum(),WHITE,2.5f);

}

void ComponentCamera::Update() {


	


}

void ComponentCamera::UpdateCamera() {

	float3 pos = belongsTo->transformPointer->GetPosition();
	float3 Z = belongsTo->transformPointer->GetGlobalTransform().WorldZ();
	float3 Y = belongsTo->transformPointer->GetGlobalTransform().WorldY();
	
	CameraComponent->SetCamPos(pos);
	CameraComponent->SetToFront(Z);
	CameraComponent->SetToUp(Y);




}