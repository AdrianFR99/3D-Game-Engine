#include "ComponentCamera.h"
#include "Application.h"
#include "ModuleCamera3D.h"


ComponentCamera::ComponentCamera(Gameobject * owner, CompType newtype):Component(newtype, owner)
{

	CameraComponent = App->camera->CreateNewCamera();

}


ComponentCamera::~ComponentCamera()
{
}

void ComponentCamera::Draw() {

	App->renderer3D->debug.DebugDrawFrustum(&CameraComponent->GetFrustum(),WHITE,true,2.5f);

}