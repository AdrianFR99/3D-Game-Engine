#ifndef _COMPONENTCAMERA_H__
#define _COMPONENTCAMERA_H__

#include "Component.h"
class ComponentCamera :	public Component
{
public:
	ComponentCamera(Gameobject * owner, CompType newtype);
	~ComponentCamera();
};

#endif