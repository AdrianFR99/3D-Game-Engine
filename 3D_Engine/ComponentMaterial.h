
#ifndef __COMPONENTMATERIAL_H__
#define __COMPONENTMATERIAL_H__

#include "Component.h"
#include "Assimp/include/material.h"
#include "ResourceTexture.h"

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
	void SetDiffuseID(uint diffuse);
	
	void SetResource(ResourceTexture* resource);

	std::string const GetTexturePath()const;
	uint const GetCurrentTextureID()const;
	
	void UseCheckered(bool use);

	void Enable();
	void Disable();

	ResourceTexture* Resource_Material = nullptr;

	
private:
	

};

#endif //COMOPNENTMATERIAL