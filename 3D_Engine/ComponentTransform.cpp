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
	
	global_transform.SetIdentity();
	local_transform.SetIdentity();

	local_position = float3(0, 0, 0);
	local_scale = float3(1, 1, 1);
	local_rotation = Quat::identity;

	Enable();
}

void ComponentTransform::Update()
{

}

void ComponentTransform::CleanUp()
{
	transform.zero;
	active = false;
	belongsTo = nullptr;

	global_transform.SetIdentity();
	local_transform.SetIdentity();

	local_position = float3(0, 0, 0);
	local_rotation = Quat::identity;
	local_scale = float3(1, 1, 1);

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
	
	return local_position;
;
}

float3 const ComponentTransform::GetRotation() const
{
	return float3(0,0,0);
}

float3 const ComponentTransform::GetScale() const
{
	
	return local_scale;
}

float4x4 const ComponentTransform::GetGlobalTransform() const
{
	return global_transform;
}

const void ComponentTransform::SetPosition(const float3 & pos)
{
	local_position = pos;

	RecalculateMatrix();
	
}

const void ComponentTransform::SetRotation(const float3 & pos)
{
	
}

const void ComponentTransform::SetScale(const float3 & pos)
{
	local_scale = float3(1, 1, 1);
}

void ComponentTransform::RecalculateMatrix()
{
	local_transform = float4x4::FromTRS(local_position, local_rotation, local_scale);
	belongsTo->UpdateTransform = true;
}


