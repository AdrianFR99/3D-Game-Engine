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

public:
	float4x4 transform;
};

#endif //COMOPNENTTRANSFROM