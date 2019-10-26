#ifndef __WINDOWINSPECTOR_SETTINGS_H__
#define __WINDOWINSPECTOR_SETTINGS_H__


#include "WindowUI.h"
#include "imgui/imgui.h"
#include "Gameobject.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

#include <vector>
#include <string>

class Module;

class WindowInspector :public WindowUI
{
public:

	WindowInspector(char*title);
	~WindowInspector();

public:


	bool Display() override;
	void Inspector_Window();

	Gameobject* activeobj;
	float3 position;
	float3 rotation;
	float3 scale;

};

#endif //__WINDOWINSPECTOR_SETTINGS_H__