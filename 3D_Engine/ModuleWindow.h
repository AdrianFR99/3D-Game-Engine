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

	bool Init(nlohmann::json config);
	bool CleanUp();
	void Load(nlohmann::json& file);
	void Save(nlohmann::json& file);
	void ReloadFromConfig();
	void SetTitle( char* title);

	const uint GetDisplayRefRate() const;

	//Brightness
	void SetBrightness(float value);
	float GetWinBrightness() const;

	//win size
//change
	void changeWinWidth(uint width);
	void changeWinHeight(uint height);
	void changeWinSize();
	void changeWin(uint w, uint h);
	void changeFullscreen(bool value);
	void changeFullscreenDestop(bool value);
	void changeResize(bool value);
	void changeBordeless(bool value);
//getters
	uint getWinWidth();
	uint getWinHeight();
	void getExtremeSizes(uint &minW, uint &minH, uint &maxW, uint &maxH);
	uint getRefreshrate();
//info getters
	bool isFullscreen();
	bool isBorderless();
	bool isResize();
	bool isFullscreenDesktop();
	
public:
	//The window we'll be rendering to
	SDL_Window* window;
	//The surface contained by the window
	SDL_Surface* screen_surface;


	//Window sizes
	uint Screen_Width = 0;
	uint Screen_Height = 0;
	uint RefreshRate = 0;
	uint disp_Width = 0;
	uint disp_Height = 0;

	// --- Win Flags ---
	bool fullscreen = false;
	bool resizable = false;
	bool borderless = false;
	bool fullscreen_desktop = false;
};

#endif // __ModuleWindow_H__