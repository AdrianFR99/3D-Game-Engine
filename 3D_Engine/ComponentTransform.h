#ifndef __COMPONENTTRANSFORM_H__
#define __COMPONENTTRANSFORM_H__

#include "Component.h"
#include "MathGeoLib\include\MathBuildConfig.h"
#include "MathGeoLib\include\MathGeoLib.h"


class Gameobject;

class ComponentTransform : public Component
{
public:
	ComponentTransform(Gameobject* owner, CompType newtype);
	virtual ~ComponentTransform();

	void Init();
	void Update();
	void CleanUp();
	
	void Enable();
	void Disable();

	float4x4 const GetTransform() const;
	float3 const GetPosition() const;
	float3 const GetRotation() const;
	float3 const GetScale() const;

	float4x4 const GetGlobalTransform() const;

	

	//set
	const void SetPosition(const float3 &pos);
	const void SetRotation(const float3 &pos);
	const void SetScale(const float3 &pos);

	//Recaluclate matrix
	void RecalculateMatrix();


public:
	float4x4 transform = float4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	/*float4x4 zero = float4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	float4x4 identity = float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);*/
private:

	float4x4 local_transform;
	float4x4 global_transform;

	float3 local_position;
	Quat local_rotation;
	float3 local_scale;

};

#endif //COMOPNENTTRANSFROM