#include "Application.h"
#include "ModuleTexture.h"

#include "DevIL/include/il.h"
#include "DevIL/include/ilu.h"
#include "DevIL/include/ilut.h"

#pragma comment (lib, "DevIL/libx86/DevIL.lib")
#pragma comment (lib, "DevIL/libx86/ILU.lib")
#pragma comment (lib, "DevIL/libx86/ILUT.lib")

#include "mmgr/mmgr.h"


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


	IDChecker = CreateCheckeredTex();

	return true;
}
bool ModuleTexture::CleanUp() {

	if (IDChecker > 0)
		glDeleteTextures(1, (GLuint*)&IDChecker);

	return true;


	return true;
}
uint ModuleTexture::CreateCheckeredTex() {

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

	return ToTexBuffer(1,GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,checkImage);
}
uint ModuleTexture::ToTexBuffer(uint size, int format, int width, int height,const void* Texture) {
	
	uint ID = 0;
	// Affect the operation of subsequent glReadPixels as well as the unpacking of texture patterns
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Generate the texture ID 
	glGenTextures(size, (GLuint*)&ID);
	glBindTexture(GL_TEXTURE_2D, ID);	//Binding texture
	
	//wrapping and filtering
	SetTextureOptions(GL_REPEAT, GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, Texture);

	glBindTexture(GL_TEXTURE_2D, 0);//unbind buff texture

	return ID;
}

void ModuleTexture::SetTextureOptions(int ClampOptions, int FilterMag, int FilterMin) {

	// Set texture loading options(clamping)
	//GL_CLAMP_TO_BORDER //GL_CLAMP //GL_REPEAT //GL_MIRRORED_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ClampOptions);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ClampOptions);
	
	//GL_NEAREST// GL_LINEAR//GL_LINEAR_MIPMAP_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMag);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMin);


}
uint ModuleTexture::CreateTexture(const char*path) {

	uint texID = 0;
	if (path == nullptr)
	{
		LOG("Error loading texture from path. ERROR: Path %s was nullptr", path);
		return texID;
	}

	uint ImageID = 0;
	ilGenImages(1, (ILuint*)&ImageID);
	ilBindImage(ImageID);

	//Loading image
	if (ilLoadImage(path))
	{
		ILinfo imageInfo;
		iluGetImageInfo(&imageInfo);
	
		if (imageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
			iluFlipImage();
		
		if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
		{
			texID = ToTexBuffer(1,ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),ilGetData());
		}
	
	}
	
	ilDeleteImages(1, (const ILuint*)&ImageID);

	

	return texID;

}