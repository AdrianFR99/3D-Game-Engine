#include "WindowHierarchy.h"
#include "Application.h"
#include "imgui_defines.h"

#include "mmgr/mmgr.h"


WindowHierarchy::WindowHierarchy(char*title) : WindowUI(title)
{


}

WindowHierarchy::~WindowHierarchy()
{
}

bool WindowHierarchy::Display() {

	if (active)
		Hierarchy_Window();

	//Drop of Drag and drop
	DragDrop();

	//Set to del
	Delete();
	
	return true;
}

void WindowHierarchy::Hierarchy_Window() {
	
	if (ImGui::Begin("Hierarchy"),&active)
	{
	
		std::vector<Gameobject*> toDisplay = App->SceneEngine->scene->GameObject_Child_Vec;
		// iterate recursively in the childs of scene
		for (std::vector<Gameobject*>::iterator it = toDisplay.begin(); it != toDisplay.end(); ++it)
		{
			RecursiveDraw((*it));
		}
		ImGui::End();
	}
	 
	
}

void WindowHierarchy::RecursiveDraw(Gameobject * ToDisplay)
{
	//  Set Imgui node flags 
	ImGuiTreeNodeFlags node_flags = base_flags;

	// Flag Conditions
	if (ToDisplay == activeOBJ)
		node_flags |= ImGuiTreeNodeFlags_Selected;
	if (ToDisplay->GameObject_Child_Vec.size() == 0)
		node_flags |= ImGuiTreeNodeFlags_Leaf;

	// Create current node and get if it is opened or not 
	if (ImGui::TreeNodeEx((void*)(intptr_t)ToDisplay->ID, node_flags, ToDisplay->nameGameObject.data()))
	{

		//  If clicked
		if (ImGui::IsItemClicked())
		{
			activeOBJ=ToDisplay;

		}
	
			

		//drag and drop
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("toDisplay", ToDisplay, sizeof(Gameobject));
			Pulled = ToDisplay;
			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (Pulled != ToDisplay->Father)
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("toDisplay"))
				{
					Droped = ToDisplay;
						/*App->Gameobjects->ChangeParenting(Pulled, ToDisplay);*/
					Drag = true;
				}

				ImGui::EndDragDropTarget();

			}

		}




		//  Set Game Object to be destroyed 
		if ( ToDisplay == activeOBJ && App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN)
		{
			DeleteGameObj = true;
			toDel = ToDisplay;
		}

		// display children  
		// recursive call
		if (ToDisplay->GameObject_Child_Vec.size() > 0)
		{
			for (std::vector<Gameobject*>::iterator it = ToDisplay->GameObject_Child_Vec.begin(); it != ToDisplay->GameObject_Child_Vec.end(); ++it)
			{
				RecursiveDraw(*it);
			}
		}


		
				ImGui::TreePop();
	}

}

Gameobject* WindowHierarchy::getActiveGameobject()
{
	return activeOBJ;
}

void WindowHierarchy::DisplayItemWindow()
{
	
	ImGui::OpenPopup("Hierarchy Tools");
	if (ImGui::BeginPopup("Hierarchy Tools"))
	{
		if (ImGui::MenuItem("Delete"))
		{
			if (activeOBJ!=nullptr)
				App->Gameobject->SetToDestroy(activeOBJ);
			
		}

		ImGui::EndPopup();
	}
}

void WindowHierarchy::CleanActiveGameobject()
{
	activeOBJ = nullptr;
}

void WindowHierarchy::DragDrop()
{
	if (Drag)
	{
		
		App->Gameobject->ChangeParenting(Pulled, Droped);

		Drag = false;
		Pulled = nullptr;
		Droped = nullptr;
	}
	
}

void WindowHierarchy::Delete()
{
	if (DeleteGameObj)
	{
		toDel->toDelete = true;
		DeleteGameObj = false;
		toDel = nullptr;
	}

}

void WindowHierarchy::SetActiveGameobject(Gameobject* go)
{
	 activeOBJ=go;
}