
#ifndef __COMPONENTMATERIAL_H__
#define __COMPONENTMATERIAL_H__

#include "Component.h"
#include "Assimp/include/material.h"
#include "ResourceTexture.h"

class Gameobject;
//enum class 	Texture_Type;
//
//struct Material {
//
//	std::string path;
//	Texture_Type type;
//};

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
	void CreateMaterial(std::string&path);
	void CreateMaterial();
	void SetResource(ResourceTexture* resource);

	std::string const GetTexturePath()const;
	uint const GetCurrentTextureID()const;
	
	void UseCheckered(bool use);

	void Enable();
	void Disable();

	ResourceTexture* Resource_Material;

	//Material Comp_Material;
private:
	//uint DiffuseID;
	//uint currentID;
	//uint CheckeredID;

};

#endif //COMOPNENTMATERIAL