#ifndef __WindowUI_SETTINGS_H__
#define __WindowUI_SETTINGS_H__

#define LOG_FPS_SIZE 100

#include "WindowUI.h"
#include "imgui/imgui.h"

#include <vector>
#include <string>

class Module;

class WindowUI_Settings:public WindowUI
{
public:

	WindowUI_Settings(char*title);
	~WindowUI_Settings();

public:

	bool Display() override;

	//config Window
	void Config_Window();
	void Config_Window_App();
	void Config_Window_Window();
	void Config_Window_FileSystem();
	void Config_Window_Input();
	void Config_Window_Hardware();


	//FPS
	void FPS_vec_Alloc(float FPS, float ms);

private:
	std::vector<float> FPS_LOG;
	std::vector<float> MS_LOG;

};

#endif //__WindowUI_SETTINGS_H__