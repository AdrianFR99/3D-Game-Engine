
#ifndef __COMPONENTMATERIAL_H__
#define __COMPONENTMATERIAL_H__

#include "Component.h"
#include "Assimp/include/material.h"

class Gameobject;

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(Gameobject* owner, CompType newtype);
	virtual ~ComponentMaterial();

	void Init();
	void Update();
	void CleanUp();
	void Draw();

	void SetTextureID(uint diffuse);
	void SerTextureChekeredID(uint chekers);
	void SetTexturePath(std::string path);
	void CreateMaterial(aiMaterial*Material,aiTextureType type,uint index, std::string path);

	std::string GetTexturePath();
	uint const GetCurrentTextureID()const;
	uint const GetCheckeredTextureID()const;
	void UseCheckered(bool use);

	void Enable();
	void Disable();


	aiMaterial* Comp_Material;
private:

	std::string TexturePath;
	uint currentID = 0;
	uint ID;
	uint ID2;

};

#endif //COMOPNENTMATERIAL