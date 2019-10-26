#include "ComponentTransform.h"


ComponentTransform::ComponentTransform(Gameobject * owner, CompType newtype) : Component(newtype, owner)
{
	//set name and type
	belongsTo = owner;
	if (owner->nameGameObject.size() != 0)
		nameComponent = owner->nameGameObject;
	else
		nameComponent = "transform";
	Init();
}

ComponentTransform::~ComponentTransform()
{

}

void ComponentTransform::Init()
{
	transform;
	Enable();
}

void ComponentTransform::Update()
{

}

void ComponentTransform::Cleanup()
{
	
	transform.zero;
	active = false;
	belongsTo = nullptr;
	
}

void ComponentTransform::Enable()
{
	active = true;
}

void ComponentTransform::Disable()
{
	active = false;
}

float4x4 const ComponentTransform::GetTransform() const
{
	return transform;
}

float3 const ComponentTransform::GetPosition() const
{
	float3 position(transform[3][0], transform[3][1], transform[3][2]);
	return position;
}

float3 const ComponentTransform::GetRotation() const
{
	return float3(0,0,0);
}

float3 const ComponentTransform::GetScale() const
{
	float x = Sqrt(Pow(transform[0][0], 2) + Pow(transform[0][1], 2) + Pow(transform[0][2], 2));
	float y = Sqrt(Pow(transform[1][0], 2) + Pow(transform[1][1], 2) + Pow(transform[1][2], 2));
	float z = Sqrt(Pow(transform[2][0], 2) + Pow(transform[2][1], 2) + Pow(transform[2][2], 2));

	return float3(x,y,z);
}
