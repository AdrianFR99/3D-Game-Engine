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
	local_rotation = float3(0, 0, 0);
	local_rotation_quat = Quat::identity;
	local_scale = float3(1, 1, 1);

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
	local_rotation = float3(0, 0, 0);
	local_rotation_quat = Quat::identity;
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
	return local_rotation;
}

Quat const ComponentTransform::GetRotationQuat() const
{
	return local_rotation_quat;
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
	float3 diff = pos - local_rotation;
	Quat quat_diff = Quat::FromEulerXYZ(diff.x*DEGTORAD, diff.y*DEGTORAD, diff.z*DEGTORAD);
	local_rotation_quat = local_rotation_quat * quat_diff;
	local_rotation = pos;

	RecalculateMatrix();
}


const void ComponentTransform::SetRotationQuat(const Quat & quat)
{
	local_rotation_quat = quat;
	local_rotation = local_rotation_quat.ToEulerXYZ() * RADTODEG;

	RecalculateMatrix();
}


const void ComponentTransform::SetScale(const float3 & pos)
{
	local_scale = float3(1, 1, 1);
}

void ComponentTransform::RecalculateMatrix()
{
	local_transform = float4x4::FromTRS(local_position, local_rotation_quat, local_scale);
	belongsTo->UpdateTransform = true;
}


