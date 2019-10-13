#ifndef __WindowUI_SETTINGS_H__
#define __WindowUI_SETTINGS_H__

#define LOG_FPS_SIZE 100
#define LOG_MEM_SIZE_PLOT 50
#define TO_MOVE_VEC_DATA 15

#include "WindowUI.h"
#include "imgui/imgui.h"
#include "glew/include/glew.h"

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
	void Config_Window_Buttons();

	//FPS
	void FPS_vec_Alloc(float FPS, float ms);


	//About
	void  DrawAbout( bool* openWindowAbout, int* current_tab);
private:
	std::vector<float> FPS_LOG;
	std::vector<float> MS_LOG;

	// --- Win Flags ---
	bool fullscreen = false;
	bool resizable = false;
	bool borderless = false;
	bool fullscreen_desktop = false;
	bool depth_test = false;
	bool face_cull = true;
	bool lighting = true;
	bool wireframe = false;

	bool specular = false;
	bool diffuse = false;
	bool ambient = false;
	bool emission = false;
	bool ambient_and_diffuse = true;
	bool color_material = true;
	bool texture_2d = false;
	


};

#endif //__WindowUI_SETTINGS_H__