#include "ComponentMaterial.h"
#include "Component.h"


ComponentMaterial::ComponentMaterial(Gameobject * owner, CompType newtype) : Component(newtype, owner)
{
	//set name and type
	belongsTo = owner;
	if (owner->nameGameObject.size() != 0)
		nameComponent = owner->nameGameObject;
	else
		nameComponent = "material";
	Init();
}

ComponentMaterial::~ComponentMaterial()
{
}

void ComponentMaterial::Init()
{
	Enable();
}

void ComponentMaterial::Update()
{

}


void ComponentMaterial::Draw()
{

}

void ComponentMaterial::SetTextureID(uint diffuse)
{
	ID = diffuse;
	currentID = ID;
}

void ComponentMaterial::SerTextureChekeredID(uint chekers)
{
	ID2 = chekers;
}

void ComponentMaterial::SetTexturePath(std::string path)
{
	TexturePath = path.data();
}

std::string ComponentMaterial::GetTexturePath()
{
	return TexturePath;
}

void ComponentMaterial::Cleanup()
{

}

uint const ComponentMaterial::GetCurrentTextureID() const
{
	return currentID;
}

uint const ComponentMaterial::GetCheckeredTextureID() const
{
	return ID2;
}

void ComponentMaterial::UseCheckered(bool use)
{
	if (use)
		currentID = ID2;
	else
		currentID = ID;
}

void ComponentMaterial::Enable()
{
	active = true;
}

void ComponentMaterial::Disable()
{
}
