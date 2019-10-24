#include "ComponentMesh.h"
#include "Component.h"
#include "Application.h"


ComponentMesh::ComponentMesh(Gameobject * owner, CompType newtype) : Component(newtype, owner)
{
	//set name and type
	//set name and type

	belongsTo = owner;
	if (owner->nameGameObject != nullptr)
		nameComponent = owner->nameGameObject;
	else
		nameComponent = nullptr;
	Init();
}

ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::Init()
{
	Enable();
}

void ComponentMesh::Update()
{

}

void ComponentMesh::Draw()
{
	App->Assets->Draw(belongsTo);
}


void ComponentMesh::CleanUp()
{
	App->Assets->CleanUp(belongsTo);
}

void ComponentMesh::Enable()
{
}

void ComponentMesh::Disable()
{
}
