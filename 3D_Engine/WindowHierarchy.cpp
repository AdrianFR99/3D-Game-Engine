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

	bool selected = false;
	if (ImGui::Begin("Hierarchy"),&active)
	{
		
		
		std::vector<Gameobject*> toDisplay = App->Gameobjects->GameobjectList;
		for (std::vector<Gameobject*>::iterator it = toDisplay.begin(); it != toDisplay.end(); ++it)
		{
			ImGui::PushID((*it)->ID);

			if (ImGui::Selectable("Gameobject"),selected)
			{
				//// If ctrl is pressed do multiselection
				//if (App->input->GetKeyRepeat(SDL_SCANCODE_LCTRL) || App->input->GetKeyRepeat(SDL_SCANCODE_RCTRL))
				//{
				//	App->gameobj->AddGameObjectToSelected((*it));
				//}

				//// If shift is pressed do fill gap selection
				//else if (App->input->GetKeyRepeat(SDL_SCANCODE_LSHIFT) || App->input->GetKeyRepeat(SDL_SCANCODE_RSHIFT))
				//{

				//}

				// Monoselection
				//else
				//{
				/*	App->gameobj->ClearSelection();
					App->gameobj->AddGameObjectToSelected((*it));
				}*/

				if (selected)
				{
					activeOBJ=(*it);
				}
			}

			ImGui::PopID();
		}




		ImGui::End();


	}
}

Gameobject* WindowHierarchy::getActiveGameobject()
{
	return activeOBJ;
}
