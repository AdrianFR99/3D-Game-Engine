#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Using SDL_Display funtions ->getting displaying data
		
		SDL_DisplayMode Display;
		//SDL_GetCurrentDisplayMode() -> return the previous native display mode
		//SDL_GetDesktopDisplayMode() -> In that case this function will return the current display mode
		if (SDL_GetDesktopDisplayMode(0, &Display) != 0) {

			LOG("SDL_GetDesktopDisplayMode Error: %s", SDL_GetError());

		}
		else
			RefreshRate = Display.refresh_rate;

		//Create window
		Screen_Width = uint(Display.w*0.75f);
		Screen_Height = uint(Display.h *0.75f);

		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen_Width, Screen_Height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetTitle( char* title)
{
	SDL_SetWindowTitle(window, title);
}

const uint ModuleWindow::GetDisplayRefRate() const {

	return RefreshRate;
}

float ModuleWindow::GetWinBrightness() const
{
	return SDL_GetWindowBrightness(window);
}

void ModuleWindow::SetBrightness(float value)
{
	if (value >= 0.0f && value <= 1.0f)
	{
		SDL_SetWindowBrightness(window, value);
	}
	else
	{		
		CAP(value);
		if (SDL_SetWindowBrightness(window, value) != 0)
			LOG("Could not change window brightness: %s\n", SDL_GetError());
	}
	
}

void ModuleWindow::changeWinWidth(uint width)
{
	Screen_Width=width;
	changeWinSize();
}

void ModuleWindow::changeWinHeight(uint height)
{
	Screen_Height = height;
	changeWinSize();
}

void ModuleWindow::changeWinSize()
{
	SDL_SetWindowSize(window, Screen_Width, Screen_Height);
	App->renderer3D->OnResize(Screen_Width, Screen_Height);
}

void ModuleWindow::changeWin(uint w, uint h)
{
	changeWinWidth(w);
	changeWinHeight(h);
	changeWinSize();
}

void ModuleWindow::changeFullscreen(bool value)
{
	if (value == true && value != fullscreen)
	{
		if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) != 0)
			LOG("Could not switch to Fullscreen: %s\n", SDL_GetError());
		fullscreen = true;
	}
	else
	{
		if (SDL_SetWindowFullscreen(window, 0 ) != 0)
			LOG("Could not switch to windowed: %s\n", SDL_GetError());
		fullscreen = false;
	}
}

void ModuleWindow::changeFullscreenDestop(bool value)
{
	if (value == true && value != fullscreen)
	{
		if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
			LOG("Could not switch to fullscreen desktop: %s\n", SDL_GetError());
		fullscreen_desktop = true;
	}
	else
	{
		if (SDL_SetWindowFullscreen(window, 0) != 0)
			LOG("Could not switch to windowed: %s\n", SDL_GetError());
		fullscreen_desktop = false;
	}

}

void ModuleWindow::changeResize(bool value)
{


	if (value == true)
	{
		resizable = value;
		SDL_SetWindowResizable(window, SDL_TRUE);
	}
	else
	{
		resizable = value;
		SDL_SetWindowResizable(window, SDL_FALSE);
	}

}

void ModuleWindow::changeBordeless(bool value)
{
	if (value == true)
	{
		borderless = value;
		SDL_SetWindowBordered(window, SDL_FALSE);
	}
	else
	{
		borderless = value;
		SDL_SetWindowBordered(window, SDL_TRUE);
	}

}

uint ModuleWindow::getWinWidth()
{
	return Screen_Width;
}

uint ModuleWindow::getWinHeight()
{
	return Screen_Width;
}

void ModuleWindow::getExtremeSizes(uint & minW, uint &minH, uint &maxW, uint &maxH)
{
	minW = disp_Width;
	minH = disp_Height;
	maxW = Screen_Width;
	maxH = Screen_Width;

	SDL_DisplayMode dm;
	if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
	{
		LOG("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
	}
	else
	{
		maxW = dm.w;
		maxH = dm.h;
	}
}

uint ModuleWindow::getRefreshrate()
{
	SDL_DisplayMode Displayinfo;
	if (SDL_GetDesktopDisplayMode(0, &Displayinfo) != 0)
	{
		LOG("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
	}
	
	return Displayinfo.refresh_rate;
}

bool ModuleWindow::isFullscreen()
{
	return fullscreen;
}

bool ModuleWindow::isBorderless()
{
	return borderless;
}

bool ModuleWindow::isResize()
{
	return resizable;
}

bool ModuleWindow::isFullscreenDesktop()
{
	return fullscreen_desktop;
}
