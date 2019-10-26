#include "WindowInspector.h"
#include "Application.h"
#include "imgui_defines.h"
#include "WindowHierarchy.h"
#include "ModuleEngineUI.h"


#include "mmgr/mmgr.h"


WindowInspector::WindowInspector(char*title) : WindowUI(title)
{


}

WindowInspector::~WindowInspector()
{
}

bool WindowInspector::Display() {

	if (active)
		Inspector_Window();


	return true;
}


void WindowInspector::Inspector_Window() {

	
	if (ImGui::Begin("Inspector"), &active)
	{
		
		//display normal
		//texture path size
		//checkered material
		//geometry (verex faces triangles)

		activeobj = App->UI_Layer->HierarchyPanel->getActiveGameobject();

		if (activeobj != nullptr)
		{
			if (ImGui::CollapsingHeader("Transform"))
			{

				
				position =  activeobj->transformPointer->GetPosition();
				float toDisplay[3];
				toDisplay[0] = position.x;
				toDisplay[1] = position.y;
				toDisplay[2] = position.z;

				ImGui::InputFloat3("Position", toDisplay);

				rotation = activeobj->transformPointer->GetRotation();
				
				toDisplay[0] = rotation.x;
				toDisplay[1] = rotation.y;
				toDisplay[2] = rotation.z;

				ImGui::InputFloat3("Rotation", toDisplay);
				
				scale = activeobj->transformPointer->GetScale();

			
				toDisplay[0] = scale.x;
				toDisplay[1] = scale.y;
				toDisplay[2] = scale.z;

				ImGui::InputFloat3("Scale", toDisplay);


				
			}


		}
		ImGui::End();
	}


}