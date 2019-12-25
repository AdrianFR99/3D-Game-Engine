#ifndef __EmitterComponent_h__
#define __EmitterComponent_h__

#include "Component.h"


class EmitterComponent :
	public Component
{
public:
	EmitterComponent(Gameobject * owner, CompType newtype);
	~EmitterComponent();


};

#endif//EmitterComponent