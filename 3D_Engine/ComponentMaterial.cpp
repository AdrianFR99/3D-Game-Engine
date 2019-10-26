#include "Application.h"
#include "ComponentMaterial.h"
#include "Component.h"
#include "ModuleTexture.h"


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
	currentID = diffuse;

}

std::string const ComponentMaterial::GetTexturePath() const
{
	return Comp_Material.path;
}

void ComponentMaterial::Cleanup()
{



}

uint const ComponentMaterial::GetCurrentTextureID() const
{
	return currentID;
}

void ComponentMaterial::UseCheckered(bool use)
{
	//if (use)
	//	currentID = ID2;
	//else
	//	currentID = ID;
}

void ComponentMaterial::Enable()
{
	active = true;
}

void ComponentMaterial::Disable()
{
}

void ComponentMaterial::CreateMaterial(std::string&path) {


	currentID=App->Textures->CreateTexture(path.data());

	if (currentID==NULL) {
		CheckeredID = App->Textures->ChekeredID;
		currentID = CheckeredID;
	}
	
	Comp_Material.path= path;
	Comp_Material.type = Texture_Type::DIFFUSE;


}

void ComponentMaterial::CreateMaterial() {

	CheckeredID = App->Textures->ChekeredID;
	currentID = CheckeredID;

	Comp_Material.path = "---";
	Comp_Material.type = Texture_Type::NONE;

}