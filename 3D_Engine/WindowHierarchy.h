#ifndef __WINDOWHIERARCHY_H__
#define __WINDOWHIERARCHY_H__


#include "WindowUI.h"
#include "imgui/imgui.h"
#include "glew/include/glew.h"
//#include "ModuleRenderer3D.h"
#include <vector>
#include "Gameobject.h"

#include <string>

class Module;

class WindowHierarchy :public WindowUI
{
public:

	WindowHierarchy(char*title);
	~WindowHierarchy();

public:

	bool Display() override;
	void Hierarchy_Window();
	Gameobject* getActiveGameobject();

	void CleanActiveGameobject();
private:

	Gameobject* activeOBJ = nullptr;
	bool selected = false;
};

#endif //__WINDOWHIERARCHY_H__