#ifndef __WINDOWINSPECTOR_SETTINGS_H__
#define __WINDOWINSPECTOR_SETTINGS_H__


#include "WindowUI.h"
#include "imgui/imgui.h"


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


};

#endif //__WINDOWINSPECTOR_SETTINGS_H__