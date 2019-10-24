#include "Gameobject.h"
#include "Component.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"

Gameobject::Gameobject(int id)
{
	ID = id;
	CreateComponent(this, TRANSFORM, true);
	Enable();
}

Gameobject::~Gameobject()
{

}

void Gameobject::Update()
{
	//nothing
}


void Gameobject::Draw()
{
	for (int i = 0; i < ComponentList.size(); ++i) {

		ComponentList[i]->Draw();

	}
}

void Gameobject::Enable()
{
	active = true;
}

void Gameobject::Disable()
{
	active = false;
}

void Gameobject::Cleanup()
{
	active = false;
	nameGameObject = nullptr;
	ID = 0;

	for (int i = 0; i < ComponentList.size(); ++i) {

		ComponentList[i]->Cleanup();

		//delete(Meshes_Vec[i]);
		RELEASE(ComponentList[i]);
	}

	ComponentList.clear();
	 transformPointer = nullptr;
	 meshPointer = nullptr;
	 materialPointer = nullptr;
	//pointers must be set to null ptr;
}

void Gameobject::CreateComponent(Gameobject * object, CompType tocreate, bool active)
{
	Component* temp = nullptr;
	int counter = 0;

	// create the component
	switch (tocreate)
	{
		
		case TRANSFORM:
		{

			temp = new ComponentTransform(this, TRANSFORM);
			transformPointer = (ComponentTransform*)temp;
			counter++;
		}

		case MESH:
		{

			temp = new ComponentMesh(this, MESH);
			meshPointer = (ComponentMesh*)temp;
			counter++;
		}
		break;

		default: 
			break;

	}

	//add to list
	if (counter != 0 && counter <=1 && temp != nullptr)
	{
		ComponentList.push_back(temp);

	}

}
