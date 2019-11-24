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
	num_meshes = Meshes_Vec.size();

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

	
	/*if (Primitives_Vec.size() > 0) {
		for (int i = 0; i < Primitives_Vec.size(); ++i) {
			Primitives_Vec[i]->CleanUp();
			
			
			if (Primitives_Vec[i] != nullptr) {
				delete Primitives_Vec[i]; \
					Primitives_Vec[i] = nullptr;
			}

		}

	}*/
	
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
