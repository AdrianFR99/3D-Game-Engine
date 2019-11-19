#ifndef _COMPONENTCAMERA_H__
#define _COMPONENTCAMERA_H__



#include "Component.h"
class Camera3D;

class ComponentCamera :	public Component
{
public:
	ComponentCamera(Gameobject * owner, CompType newtype);
	~ComponentCamera();

	Camera3D*CameraComponent;


public:

	void Draw()override;

};

#endif