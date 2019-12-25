#ifndef __ComponentBillboard_h__
#define __ComponentBillboard_h__

#include "Component.h"
class ComponentBillboard :
	public Component
{
public:
	ComponentBillboard(Gameobject * owner, CompType newtype);
	~ComponentBillboard();
};



#endif//ComponentBillboard