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
		
		
		std::vector<Gameobject*> toDisplay = App->Gameobjects->GameobjectList;
		for (std::vector<Gameobject*>::iterator it = toDisplay.begin(); it != toDisplay.end(); ++it)
		{
			ImGui::PushID((*it)->ID);
			if ((*it)->nameGameObject.size() != 0)
			{
				if (ImGui::Selectable((*it)->nameGameObject.data(), activeOBJ==(*it)))
				{

					
					activeOBJ=(*it);
					
				}

			}
			else
			{
				if (ImGui::Selectable("Gameobject"), (*it)->ID, selected)
				{

					if (selected)
					{
						activeOBJ = (*it);
					}
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
