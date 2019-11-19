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

	ObjectPosition = float3(0, 0, 0);
	ObjectRotation = float3(0, 0, 0);
	ObjectQuat = Quat::identity;
	ObjectScale = float3(1, 1, 1);

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

	ObjectPosition = float3(0, 0, 0);
	ObjectRotation = float3(0, 0, 0);
	ObjectQuat = Quat::identity;
	ObjectScale = float3(1, 1, 1);

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
	return ObjectPosition;
}

float3 const ComponentTransform::GetRotation() const
{
	return ObjectRotation;
}

Quat const ComponentTransform::GetRotationQuat() const
{
	return ObjectQuat;
}

float3 const ComponentTransform::GetScale() const
{
	return ObjectScale;
}

float4x4 const ComponentTransform::GetGlobalTransform() const
{
	return global_transform;
}

const void ComponentTransform::SetPosition(const float3 & pos)
{
	ObjectPosition = pos;

	RecalculateMatrix();
	
}

const void ComponentTransform::SetRotation(const float3 & pos)
{
	float3 diff = pos - ObjectRotation;
	Quat quat_diff = Quat::FromEulerXYZ(diff.x*DEGTORAD, diff.y*DEGTORAD, diff.z*DEGTORAD);
	ObjectQuat = ObjectQuat * quat_diff;
	ObjectRotation = pos;

	RecalculateMatrix();
}


const void ComponentTransform::SetRotationQuat(const Quat & quat)
{
	ObjectQuat = quat;
	ObjectRotation = ObjectQuat.ToEulerXYZ() * RADTODEG;

	RecalculateMatrix();
}


const void ComponentTransform::SetScale(const float3 & pos)
{
	ObjectScale = pos;

	RecalculateMatrix();
}

const void ComponentTransform::Scale(const float3 & scale)
{
	ObjectScale += scale;

	RecalculateMatrix();
}

void ComponentTransform::RecalculateMatrix()
{
	local_transform = float4x4::FromTRS(ObjectPosition, ObjectQuat, ObjectScale);
	belongsTo->UpdateTransform = true;
}


