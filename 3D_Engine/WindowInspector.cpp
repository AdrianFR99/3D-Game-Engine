#include "WindowInspector.h"
#include "Application.h"
#include "imgui_defines.h"
#include "WindowHierarchy.h"
#include "ModuleEngineUI.h"
#include "ModuleTexture.h"


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

				ImGui::Spacing();
				ImGui::Separator();
				
			}
			if (ImGui::CollapsingHeader("Normals"))
			{
				if (ImGui::Checkbox("Draw Face Normals", &App->Assets->DrawFaceNormals))
				{


				}

				ImGui::SameLine();

				if (ImGui::Checkbox("Draw Vertex Normals", &App->Assets->DrawVertexNormals))
				{


				}

				ImGui::Spacing();
				ImGui::Separator();
				
			}
			if (ImGui::CollapsingHeader("Texture"))
			{

				ImGui::Text("Id: %i", activeobj->materialPointer->GetCurrentTextureID());

				ImGui::Text("Base File Location:");
				ImGui::SameLine();
				ImGui::TextColored(IMGUI_YELLOW, "%s", activeobj->materialPointer->Comp_Material.path.data());
				
				ImGui::Spacing();

				ImGui::Text("Size:");
				ImGui::SameLine();
				int texture = activeobj->materialPointer->GetCurrentTextureID();
				std::string height = std::to_string(App->Textures->TextureIDs[texture]->Height);
				std::string width = std::to_string(App->Textures->TextureIDs[texture]->Width);
				ImGui::TextColored(IMGUI_YELLOW, "%s x %s", height.data(),width.data());

				ImGui::Text("Preview:");
				ImGui::Image((ImTextureID)activeobj->materialPointer->GetCurrentTextureID(), ImVec2(150, 150));
				ImGui::Separator();


			}

			if (ImGui::CollapsingHeader("Material"))
			{

				if (ImGui::Checkbox("Diffuse Texture", &diffuse))
				{
					chekers = !chekers;
					if (diffuse)
					{
						activeobj->materialPointer->UseCheckered(false);
					}
					else
						activeobj->materialPointer->UseCheckered(true);
				}

				ImGui::SameLine();

				if (ImGui::Checkbox("Checkered Texture", &chekers))
				{
					diffuse = !diffuse;
					if (chekers)
					{
						activeobj->materialPointer->UseCheckered(true);
					}
					else
						activeobj->materialPointer->UseCheckered(false);
				}

				ImGui::Spacing();

				ImGui::Separator();


			}
			if (ImGui::CollapsingHeader("Geometry"))
			{
				if (activeobj->meshPointer->Meshes_Vec.size() != 0)
				{
					for (int i = 0; i < activeobj->meshPointer->Meshes_Vec.size(); ++i) {

						vertex += activeobj->meshPointer->Meshes_Vec[i]->num_vertex;
						index += activeobj->meshPointer->Meshes_Vec[i]->num_index;
						normal += activeobj->meshPointer->Meshes_Vec[i]->num_normals;
						normal_faces += activeobj->meshPointer->Meshes_Vec[i]->num_normals_faces;
						uvs += activeobj->meshPointer->Meshes_Vec[i]->num_uv;
						Triangles += activeobj->meshPointer->Meshes_Vec[i]->num_normals_faces;


					}

					ImGui::Text("Vertex Count:");
					ImGui::SameLine();
					ImGui::TextColored(IMGUI_YELLOW, "%i", vertex);

					ImGui::Text("Index Count:");
					ImGui::SameLine();
					ImGui::TextColored(IMGUI_YELLOW, "%i", index);

					ImGui::Text("UVs Count:");
					ImGui::SameLine();
					ImGui::TextColored(IMGUI_YELLOW, "%i", uvs);

					ImGui::Text("Normal Count:");
					ImGui::SameLine();
					ImGui::TextColored(IMGUI_YELLOW, "%i", normal);

					ImGui::Text("Normal face Count:");
					ImGui::SameLine();
					ImGui::TextColored(IMGUI_YELLOW, "%i", normal_faces);

					ImGui::Text("Triangles Faces Count:");
					ImGui::SameLine();
					ImGui::TextColored(IMGUI_YELLOW, "%i", Triangles);

					 Triangles = 0;
					 vertex = 0;
					 normal = 0;
					 normal_faces = 0;
					 index = 0;
					 uvs = 0;

				}
				if (activeobj->meshPointer->Primitives_Vec.size() != 0)
				{
					ImGui::Text("Primitive must be done:");
				}
			}
		}
		ImGui::End();
	}


}