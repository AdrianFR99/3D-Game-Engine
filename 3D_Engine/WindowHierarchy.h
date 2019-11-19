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
	/*void Hierarchy_Window(Gameobject* todisplay, int& node );*/
	void Hierarchy_Window();
	void RecursiveDraw(Gameobject* todisplay);
	Gameobject* getActiveGameobject();
	void DisplayItemWindow();
	void CleanActiveGameobject();
	void DragDrop();
	void Delete();
private:

	Gameobject* activeOBJ = nullptr;

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoFocusOnAppearing;
	ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow;


	Gameobject* to_destroy = nullptr;

	Gameobject* Pulled = nullptr;
	Gameobject* Droped = nullptr;

	bool Drag = false;
	bool DeleteGameObj = false;
	Gameobject* toDel = nullptr;
};

#endif //__WINDOWHIERARCHY_H__