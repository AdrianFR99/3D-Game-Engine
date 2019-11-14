#include "Gameobject.h"
#include "Component.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"

#include "mmgr/mmgr.h"

Gameobject::Gameobject(int id)
{
	ID = id;
	CreateComponent(this, TRANSFORM, true);
	Enable();
	Father = nullptr;
}

Gameobject::~Gameobject()
{

}

void Gameobject::Update()
{
	
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

void Gameobject::CleanUp()
{
	active = false;
	ID = 0;


	for (int i = 0; i < ComponentList.size(); ++i) {


		ComponentList[i]->CleanUp();
		//delete(Meshes_Vec[i]);
	
		if (ComponentList[i] != nullptr) 
			delete ComponentList[i]; 
			ComponentList[i] = nullptr;



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


			temp = new ComponentTransform(this, TRANSFORM);
			transformPointer = (ComponentTransform*)temp;
			temp = transformPointer;
			counter++;

		break;
		case MESH:


			temp = new ComponentMesh(this, MESH);
			meshPointer = (ComponentMesh*)temp;
			temp = meshPointer;
			counter++;

		

		break;
		case MATERIAL:


			temp = new ComponentMaterial(this, MATERIAL);
			materialPointer = (ComponentMaterial*)temp;
			temp = materialPointer;
			counter++;


		break;


	}

	//add to list
	if (counter != 0 && counter <=1 && temp != nullptr)
	{
		ComponentList.push_back(temp);

	}

}

void Gameobject::UpdateGlobalTransform()
{
	this;
	if (Father != nullptr)
	{
		transformPointer->global_transform = Father->transformPointer->global_transform * transformPointer->local_transform;
	}
	if (!GameObject_Child_Vec.empty())
	{
		for (std::vector<Gameobject*>::iterator it = GameObject_Child_Vec.begin(); it != GameObject_Child_Vec.end(); it++)
		{
			(*it)->UpdateGlobalTransform();
		}
	}

}
