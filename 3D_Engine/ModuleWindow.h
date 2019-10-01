#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle( char* title);

	const uint GetDisplayRefRate() const;
	
public:
	//The window we'll be rendering to
	SDL_Window* window;
	//The surface contained by the window
	SDL_Surface* screen_surface;


	//Window sizes
	uint Screen_Width = 1280;
	uint Screen_Height = 1024;
	uint RefreshRate = 0;
};

#endif // __ModuleWindow_H__