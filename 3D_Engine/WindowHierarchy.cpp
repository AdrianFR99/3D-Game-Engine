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
	 
	//Delete
	
	if (to_destroy)
	{
		/*App->scene_manager->DestroyGameObject(to_destroy);
		to_destroy = nullptr;
		CleanActiveGameobject();*/
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
			activeOBJ=ToDisplay;

		
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
		if (ImGui::IsWindowFocused() && ToDisplay == activeOBJ && App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN)
		{
		
			to_destroy = ToDisplay;
		}

		//  Display children  

			// rcursive call
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

void WindowHierarchy::CleanActiveGameobject()
{
	activeOBJ = nullptr;
}
