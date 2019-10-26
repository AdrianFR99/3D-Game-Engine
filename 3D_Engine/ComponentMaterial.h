
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
	void Cleanup();
	void Draw();

	void SetTextureID(uint diffuse);
	void SerTextureChekeredID(uint chekers);
	void SetTexturePath(std::string path);

	std::string GetTexturePath();
	uint const GetCurrentTextureID()const;
	uint const GetCheckeredTextureID()const;
	void UseCheckered(bool use);

	void Enable();
	void Disable();


private:

	std::string TexturePath;
	uint currentID = 0;
	uint ID;
	uint ID2;

};

#endif //COMOPNENTMATERIAL