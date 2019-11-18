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
	
	//currentID = diffuse;

}

void ComponentMaterial::SetDiffuseID(uint diffuse)
{
	// set resource for diffuse
	//DiffuseID = diffuse;
}

std::string const ComponentMaterial::GetTexturePath() const
{
	//get texture path from resource
	return Resource_Material->Comp_Material.path.data();
}

void ComponentMaterial::CleanUp()
{



}

uint const ComponentMaterial::GetCurrentTextureID() const
{
	//get active resource text id
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

void ComponentMaterial::CreateMaterial(std::string&path) {

	// maybe create a resource?? not sure, pls check
	/*currentID=App->Textures->CreateTexture(path.data());
	DiffuseID = currentID;
	CheckeredID = App->Textures->ChekeredID;

	if (currentID==NULL) {
		currentID = CheckeredID;
	}

	Comp_Material.path= path;
	Comp_Material.type = Texture_Type::DIFFUSE;

*/
}

void ComponentMaterial::CreateMaterial() {


	////DiffuseID = currentID;
	//CheckeredID = App->Textures->ChekeredID;

	//currentID = CheckeredID;

	//Comp_Material.path = "---";
	//Comp_Material.type = Texture_Type::NONE;

}

void ComponentMaterial::SetResource(ResourceTexture * resource)
{
	Resource_Material = resource;
}
