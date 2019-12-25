#include "Application.h"
#include "ComponentMaterial.h"
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
	//change current resource using
	if (Resource_Material != nullptr)
	{
	Resource_Material->currentID = diffuse;

	}
	

}

void ComponentMaterial::SetDiffuseID(uint diffuse)
{
	// set resource for diffuse
	if (Resource_Material != nullptr)
	{
	Resource_Material->DiffuseID = diffuse;

	}
	
}

std::string const ComponentMaterial::GetTexturePath() const
{
	
	//get texture path from resource
	if (Resource_Material == nullptr)
		int a = 0;

	return Resource_Material->Comp_Material.path.data();
}

void ComponentMaterial::CleanUp()
{
	Resource_Material->CleanUp();

	Resource_Material = nullptr;


}

uint const ComponentMaterial::GetCurrentTextureID() const
{
	//get active resource text id

	if (Resource_Material == nullptr)
		int a = 0;

	return Resource_Material->currentID;
}

void ComponentMaterial::UseCheckered(bool use)
{
	//change between resource for diffuse and for chekered 
	if (use)
		Resource_Material->currentID = Resource_Material->CheckeredID;
	else
		Resource_Material->currentID = Resource_Material->DiffuseID;
}

void ComponentMaterial::Enable()
{
	active = true;
}

void ComponentMaterial::Disable()
{
	active = false;
}



void ComponentMaterial::SetResource(ResourceTexture * resource)
{
	Resource_Material = resource;
}
