#ifndef __WindowUI_SETTINGS_H__
#define __WindowUI_SETTINGS_H__


#include "WindowUI.h"


class WindowUI_Settings:public WindowUI
{
public:

	WindowUI_Settings(char*title);
	~WindowUI_Settings();



	

public:
	//config Window
	void Config_Window();
	void Config_Window_App();
	void Config_Window_Window();
	void Config_Window_FileSystem();
	void Config_Window_Input();
	void Config_Window_Hardware();






};

#endif