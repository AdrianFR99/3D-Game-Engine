#include "ComponentMesh.h"
#include "Component.h"
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

	
	if (Primitives_Vec.size() > 0) {
		for (int i = 0; i < Primitives_Vec.size(); ++i) {
			Primitives_Vec[i]->CleanUp();
			
			
			if (Primitives_Vec[i] != nullptr) {
				delete Primitives_Vec[i]; \
					Primitives_Vec[i] = nullptr;
			}

		}

	}
	


	//TODO2
	//must complete cleanup from primitive
}

void ComponentMesh::Enable()
{
}

void ComponentMesh::Disable()
{
}
