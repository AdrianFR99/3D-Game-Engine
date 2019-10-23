#include "ComponentTransform.h"
#include "Component.h"


ComponentTransform::ComponentTransform(Gameobject * owner, CompType newtype) : Component(newtype, owner)
{
	//set name and type
	Init();
}

ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::Init()
{
}

void ComponentTransform::Update()
{

}

void ComponentTransform::CleanUp()
{

}

void ComponentTransform::Enable()
{
}

void ComponentTransform::Disable()
{
}
