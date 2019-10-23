#include "Gameobject.h"
#include "Component.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"

Gameobject::Gameobject(int id)
{
	ID = id;
}

Gameobject::~Gameobject()
{

}

void Gameobject::Update()
{
	//nothing
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
