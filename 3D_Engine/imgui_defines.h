#pragma once
#include "imgui/imgui.h"
//#include "imgui/imgui_internal.h"


// Set of Colors for quick access

#define IMGUI_BLACK ImVec4(0,0,0,1)
#define IMGUI_NAVY_BLUE  ImVec4(0,0,128,1)
#define IMGUI_BLUE ImVec4(0,0,255,1)
#define IMGUI_GREEN ImVec4(0,128,0,1)
#define IMGUI_TEAL_GREEN ImVec4(0,128,128,1)
#define IMGUI_LIME_GREEN ImVec4(0,255,0,1)
#define IMGUI_AQUAMARINE ImVec4(0,255,255,1)
#define IMGUI_MAROON ImVec4(128,0,0,1)
#define IMGUI_PURPLE ImVec4(128,0,128,1)
#define IMGUI_OLIVE ImVec4(128,128,0,1)
#define IMGUI_GREY ImVec4(128,128,128,1)
#define IMGUI_SILVER ImVec4(192,192,192,1)
#define IMGUI_RED ImVec4(255,0,0,1)
#define IMGUI_FUCHISIA ImVec4(255,0,255,1)
#define IMGUI_WHITE ImVec4(255,255,255,1)
#define IMGUI_YELLOW ImVec4(255,255,0,1)

//#define IMGUI_LIGHT_GREY ImVec4(0.8f,0.8f,0.8f,1.f)
//#define IMGUI_GREY ImVec4(0.6f,0.6f,0.6f,1.f)
//#define IMGUI_BLUE ImVec4(0.2f,0.2f,1.f,1.f)
//#define IMGUI_GREEN ImVec4(0.f,1.f,0.f,1.f)
//#define IMGUI_YELLOW ImVec4(1.f,1.f,0.f,1.f)
//#define IMGUI_RED ImVec4(1.f,0.f,0.f,1.f)
//#define IMGUI_WHITE ImVec4(1.f,1.f,1.f,1.f)



//for quick and easy use
//input the name and just wriete the text

#define LINE_PRINT (name) \
	ImGui::Text(name); \
	ImGui::SameLine();


#define IMGUI_PRINT(field, format, ...) \
	ImGui::Text(field); \
	ImGui::SameLine(); \
	ImGui::TextColored(IMGUI_YELLOW, format, __VA_ARGS__)



