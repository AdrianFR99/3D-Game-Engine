#include "Gameobject.h"
#include "Component.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentCamera.h"
#include "DebugDraw.h"

#include "glew/include/glew.h"

#include "mmgr/mmgr.h"

Gameobject::Gameobject(int id)
{
	ID = id;
	CreateComponent(this, TRANSFORM, true);
	Enable();
	Father = nullptr;

    //default OBB && AABB if there is no mesh
	
	
	def.SetFrom(AABB(transformPointer->GetPosition()-float3::one, transformPointer->GetPosition()+float3::one));
	
}

Gameobject::~Gameobject()
{

}

void Gameobject::Update()
{
	
	for (int i = 0; i < ComponentList.size();++i) {
		
		ComponentList[i]->Update();

	}

}


void Gameobject::Draw()
{
	for (int i = 0; i < ComponentList.size(); ++i) {

		ComponentList[i]->Draw();

	}

	if(DrawBBOs==true)
	DrawOBB_Box();

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

			hasTransform = true;

		break;
		case MESH:


			temp = new ComponentMesh(this, MESH);
			meshPointer = (ComponentMesh*)temp;
			temp = meshPointer;
			counter++;

			hasMesh = true;


			break;
		case MATERIAL:

			temp = new ComponentMaterial(this, MATERIAL);
			materialPointer = (ComponentMaterial*)temp;
			temp = materialPointer;
			counter++;

			hasMaterial = true;

			break;

		case CAMERA:

			temp = new ComponentCamera(this,CAMERA);
			CameraPointer = (ComponentCamera*)temp;
			temp = CameraPointer;
			counter++;

			hasCamera = true;

			break;

		break;


	}

	//add to list
	if (counter != 0 && counter <=1 && temp != nullptr)
	{
		ComponentList.push_back(temp);

	}

}

void Gameobject::DrawOBB_Box() {

	
	
	if (DrawOBB == true) {

		float3 Corners[8];
		obb.GetCornerPoints(Corners);
		DebugDrawBox(Corners, WHITE, 2.5f);

	}

	if (DrawAABB==true) {

		float3 CornersAABB[8];
		aabb.GetCornerPoints(CornersAABB);
		DebugDrawBox(CornersAABB, GREEN, 2.5f);
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

	UpdateBBOs();

	if (CameraPointer != nullptr)
		CameraPointer->UpdateCamera();

}

void Gameobject::SetBBOs() {

	obb = meshPointer->Meshes_Vec[0]->bbox;
	obb.Transform(transformPointer->GetGlobalTransform());

	aabb.SetNegativeInfinity();
	aabb.Enclose(obb);
}

void Gameobject::UpdateBBOs(){




	if (hasMesh==true) {
	
		if (meshPointer->Meshes_Vec.size()>0)
			obb.SetFrom(meshPointer->Meshes_Vec[0]->GetBBox());
		else if(meshPointer->Primitives_Vec.size()>0)
			obb.SetFrom(meshPointer->Primitives_Vec[0]->GetBBox());
	
		obb.Transform(transformPointer->GetGlobalTransform());
		aabb.SetFrom(obb);
	}
	else{

		obb.SetFrom(def);
		obb.Transform(transformPointer->GetGlobalTransform());
		aabb.SetFrom(obb);

	}

}