#include "Application.h"
#include "ModuleTexture.h"

#include "DevIL/include/il.h"
#include "DevIL/include/ilu.h"
#include "DevIL/include/ilut.h"

#pragma comment (lib, "DevIL/libx86/DevIL.lib")
#pragma comment (lib, "DevIL/libx86/ILU.lib")
#pragma comment (lib, "DevIL/libx86/ILUT.lib")

#include "mmgr/mmgr.h"

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

ModuleTexture::ModuleTexture(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}


ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Init() {

	bool ret = true;

	// Check versions
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION ||
		iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION ||
		ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		LOG("DevIL version is different...exiting!");
		ret = false;
	}
	LOG("Initializing DevIL");
	// --- Initializing DevIL

	ilInit();// Initialize IL
	iluInit();// Initialize ILU
	ilutInit();// Initialize ILUT with OpenGL support.
	ilutRenderer(ILUT_OPENGL);

	return ret;
}

bool ModuleTexture::Start() {




	return true;
}
bool ModuleTexture::CleanUp() {




	return true;
}
void ModuleTexture::CreateCheckeredTex() {

	GLubyte checkImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

}
void ModuleTexture::ToTexBuffer() {
	





}