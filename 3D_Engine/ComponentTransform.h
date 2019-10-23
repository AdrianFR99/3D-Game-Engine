#ifndef __COMPONENTTRANSFORM_H__
#define __COMPONENTTRANSFORM_H__

#include "Component.h"
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


private:


};

#endif //COMOPNENTTRANSFROM