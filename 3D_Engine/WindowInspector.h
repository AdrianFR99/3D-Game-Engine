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


	float NearPlane=0.1f;
	float FarPlane = 1000.0f;

	bool materialActive = true;
	bool diffuse = true;
	bool chekers = false;

	bool meshActive = true;
	bool vertex_normals = false;
	bool facenormals = false;

	int Triangles = 0;
	int vertex = 0;
	int normal = 0;
	int normal_faces = 0;
	int index = 0;
	int uvs = 0;

	

};

#endif //__WINDOWINSPECTOR_SETTINGS_H__