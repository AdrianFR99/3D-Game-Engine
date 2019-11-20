#include "ComponentCamera.h"
#include "Application.h"
#include "ModuleCamera3D.h"


ComponentCamera::ComponentCamera(Gameobject * owner, CompType newtype):Component(newtype, owner)
{

	float3 pos = { 10.0f,0.0f,0.0f };
	float Near = 5.0f;
	float Far = 20.0f;

	CameraComponent = App->camera->CreateNewCamera(pos,Near,Far);

}


ComponentCamera::~ComponentCamera()
{
}

void ComponentCamera::Draw() {

	DebugDrawFrustum(&CameraComponent->GetFrustum(),WHITE,2.5f);

}