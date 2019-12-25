#include "ComponentMesh.h"
#include "Application.h"
#include "Primitives.h"
#include "Globals.h"

#include"mmgr/mmgr.h"


ComponentMesh::ComponentMesh(Gameobject * owner, CompType newtype) : Component(newtype, owner)
{
	//set name and type

	belongsTo = owner;
	if (owner->nameGameObject.size() != 0)
		nameComponent = owner->nameGameObject;
	else
		nameComponent = "mesh";

	
	Init();
}

ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::Init()
{
	Enable();
	if(Meshes_Vec!=nullptr)
	num_meshes = 1;
	else
	num_meshes = 0;
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

	Meshes_Vec->CleanUp();

	Meshes_Vec = nullptr;

	
	
	
	
}

void ComponentMesh::Enable()
{
	active = true;
}

void ComponentMesh::Disable()
{
	active = false;
}

void ComponentMesh::NormalDisplay(bool faces, bool vertex)
{
	normalsDrawFaces = faces;
	normalsDrawVertex = vertex;
}

void ComponentMesh::SetResourceMesh(ResourceMesh * resource)
{
	Meshes_Vec = resource;
}
