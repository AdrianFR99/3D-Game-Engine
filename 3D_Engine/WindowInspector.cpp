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
				if (ImGui::DragFloat3("Position", (float*)&position, 0.1f))
					activeobj->transformPointer->SetPosition(position);
				

				rotation = activeobj->transformPointer->GetRotation();
				if (ImGui::DragFloat3("Rotation", (float*)&rotation, 0.1f))
					activeobj->transformPointer->SetRotation(rotation);
				
				
				
				scale = activeobj->transformPointer->GetScale();
				if (ImGui::DragFloat3("Scale", (float*)&scale, 0.1f))
					activeobj->transformPointer->SetScale(scale);
			

				ImGui::Spacing();
				ImGui::Separator();
				
			}
			
			if (ImGui::CollapsingHeader("Normals"))
			{
				if (ImGui::Checkbox("Draw Face Normals", &facenormals))
				{
					activeobj->meshPointer->NormalDisplay(facenormals, vertex_normals);

				}

				ImGui::SameLine();

				if (ImGui::Checkbox("Draw Vertex Normals", &vertex_normals))
				{
					activeobj->meshPointer->NormalDisplay(facenormals, vertex_normals);

				}

				ImGui::Spacing();
				ImGui::Separator();
				
			}
			if (ImGui::CollapsingHeader("Texture"))
			{

				ImGui::Text("Id: %i", activeobj->materialPointer->GetCurrentTextureID());

				ImGui::Text("Base File Location:");
				ImGui::SameLine();
				ImGui::TextColored(IMGUI_YELLOW, "%s", activeobj->materialPointer->Resource_Material->Comp_Material.path.data());
				
				ImGui::Spacing();

				ImGui::Text("Size:");
				ImGui::SameLine();

				bool found = false;
				int textureIndex = activeobj->materialPointer->GetCurrentTextureID();

				for (int i = 0; i < App->Textures->TextureIDs.size(); ++i)
				{
					if (App->Textures->TextureIDs[i]->id == textureIndex)
					{
						textureIndex = i;
						found = true;
						break;
					}
				}

				if (found)
				{
					std::string height = std::to_string(App->Textures->TextureIDs[textureIndex]->Height);
					std::string width = std::to_string(App->Textures->TextureIDs[textureIndex]->Width);
					ImGui::TextColored(IMGUI_YELLOW, "%s x %s", height.data(),width.data());

				}

				ImGui::Text("Preview:");
				ImGui::Image((ImTextureID)activeobj->materialPointer->GetCurrentTextureID(), ImVec2(150, 150));
				ImGui::Separator();


			}

			if (ImGui::CollapsingHeader("Material"))
			{
				if (ImGui::Checkbox("Active", &materialActive))
				{
					if(!materialActive)
						activeobj->materialPointer->Disable();
					else
						activeobj->materialPointer->Enable();
				} 

				ImGui::Spacing();

				ImGui::Separator();

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
			if (ImGui::CollapsingHeader("Mesh & Geometry"))
			{

				if (ImGui::Checkbox("Meshes Active", &meshActive))
				{
					if (!meshActive)
						activeobj->meshPointer->Disable();
					else
						activeobj->meshPointer->Enable();
				}
				ImGui::Spacing();

				ImGui::Separator();

				std::string display_name;
				std::string id;
				if ( activeobj->meshPointer->Meshes_Vec->Meshes_Vec!=nullptr) 
				{
					/*display_name = activeobj->nameGameObject;
					id = std::to_string(1);
					display_name.append(id);

					if (ImGui::Checkbox(display_name.data(), &activeobj->meshPointer->Meshes_Vec[i]->active))
					{
						
							
					}*/
				}

				ImGui::Spacing();

				ImGui::Separator();


				if (activeobj->meshPointer->Meshes_Vec->Meshes_Vec != nullptr)
				{
					

						vertex += activeobj->meshPointer->Meshes_Vec->Meshes_Vec->num_vertex;
						index += activeobj->meshPointer->Meshes_Vec->Meshes_Vec->num_index;
						normal += activeobj->meshPointer->Meshes_Vec->Meshes_Vec->num_normals;
						normal_faces += activeobj->meshPointer->Meshes_Vec->Meshes_Vec->num_normals_faces;
						uvs += activeobj->meshPointer->Meshes_Vec->Meshes_Vec->num_uv;
						Triangles += activeobj->meshPointer->Meshes_Vec->Meshes_Vec->num_normals_faces;


					

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
				if (activeobj->meshPointer->Meshes_Vec->Primitives_Vec != nullptr)
				{
					if (activeobj->meshPointer->Meshes_Vec->Primitives_Vec != nullptr) {

						vertex += activeobj->meshPointer->Meshes_Vec->Primitives_Vec->num_vertex;
						index += activeobj->meshPointer->Meshes_Vec->Primitives_Vec->num_index;
						//normal += activeobj->meshPointer->Primitives_Vec[i]->num_normals;
						//normal_faces += activeobj->meshPointer->Primitives_Vec[i]->num_normals_faces;
						//uvs += activeobj->meshPointer->Primitives_Vec[i]->num_uv;
						//Triangles += activeobj->meshPointer->Primitives_Vec[i]->num_normals_faces;


					}

					ImGui::Text("Vertex Count:");
					ImGui::SameLine();
					ImGui::TextColored(IMGUI_YELLOW, "%i", vertex);

					ImGui::Text("Index Count:");
					ImGui::SameLine();
					ImGui::TextColored(IMGUI_YELLOW, "%i", index);
/*
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
					ImGui::TextColored(IMGUI_YELLOW, "%i", Triangles);*/

					Triangles = 0;
					vertex = 0;
					normal = 0;
					normal_faces = 0;
					index = 0;
					uvs = 0;
				}
			}
		}
		ImGui::End();
	}


}