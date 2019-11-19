#pragma once

// Warning disabled ---
#pragma warning( disable : 4577 ) // Warning that exceptions are disabled
#pragma warning( disable : 4530 )

#include <windows.h>
#include <stdio.h>



#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define HAVE_M_PI

#define ALIGN_CLASS_TO_16 \
    void* operator new(size_t i) { return _aligned_malloc(i,16); }\
    void operator delete(void* p) { _aligned_free(p);}

#define RELEASE(x) \
    { \
    if (x != nullptr) \
      delete x; \
	x = nullptr; \
	} \

#define RELEASE_ARRAY(x) \
    { \
    if (x != nullptr) \
      delete[] x; \
	x = nullptr; \
	} \


typedef unsigned int uint;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "Gears Engine"
#define ASSETS_FOLDER "/Assets/"

//define Colors
#define RED Color(1.0f, 0.0f, 0.0f)
#define GREEN Color(0.0f, 1.0f, 0.0f)
#define BLUE Color(0.0f, 0.0f, 1.0f)
#define BLACK  Color(0.0f, 0.0f, 0.0f)
#define WHITE  Color(1.0f, 1.0f, 1.0f)
#define ORANGE Color(0.75f, 0.25f, 0.0f)
#define GREY Color(0.84f, 0.84f, 0.84f)
#define BROWN Color(0.45f, 0.29f, 0.7f)
#define PINK Color(0.8f, 0.59f, 0.8f)
