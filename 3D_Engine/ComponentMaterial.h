
#ifndef __COMPONENTMATERIAL_H__
#define __COMPONENTMATERIAL_H__

#include "Component.h"
class Gameobject;

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(Gameobject* owner, CompType newtype);
	virtual ~ComponentMaterial();

	void Init();
	void Update();
	void CleanUp();

	void Enable();
	void Disable();


private:


};

#endif //COMOPNENTMATERIAL