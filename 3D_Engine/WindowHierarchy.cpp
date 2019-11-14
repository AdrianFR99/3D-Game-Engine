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
		/*else if (ImGui::IsMouseClicked(1))
		{
			activeOBJ = ToDisplay;
			DisplayItemWindow();
		}*/
			


		
		// Our buttons are both drag sources and drag targets here!
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("toDisplay", ToDisplay, sizeof(Gameobject)); 
			Pulled = ToDisplay;
			ImGui::EndDragDropSource();
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("toDispaly"))
			{
				App->Gameobjects->ChangeParenting(Pulled, ToDisplay);
				Pulled=nullptr;
			}

			ImGui::EndDragDropTarget();
		}

		//  Set Game Object to be destroyed 
		if ( ToDisplay == activeOBJ && App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN)
		{
			ToDisplay->toDelete = true;
		}

		//  Display children  

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
				App->Gameobjects->SetToDestroy(activeOBJ);
			
		}

		ImGui::EndPopup();
	}
}

void WindowHierarchy::CleanActiveGameobject()
{
	activeOBJ = nullptr;
}
