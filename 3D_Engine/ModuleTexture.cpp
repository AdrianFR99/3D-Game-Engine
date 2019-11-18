#include "Application.h"
#include "ModuleTexture.h"

#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "DevIL/include/il.h"
#include "DevIL/include/ilu.h"
#include "DevIL/include/ilut.h"

#include "Assimp/include/material.h"

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


//Called to init variables
void ModuleTexture::Load(nlohmann::json& file)
{
	LOG("Load variables from Json to module Texture");
	App->GearConsole.AddLog(" Load Config varibales for texture ");

	std::string tmp = file["Modules"]["Texture"]["Location"];
	TexturePath = tmp;


}

// Called to save variables
void ModuleTexture::Save(nlohmann::json& file)
{
	LOG("Save variables from Module Textue to Config");
	App->GearConsole.AddLog(" Save variables from Module Texture to Config ");


}

// Called to load variables
void ModuleTexture::ReloadFromConfig()
{
	LOG("Load variables from Config");
	App->GearConsole.AddLog(" Load variables from Config to Texture");

}

bool ModuleTexture::findTextureinList(std::string path, int& index)
{
	bool ret = false;

	for (int i = 0; i < TextureIDs.size(); ++i) {

		//if it pins the texture path in the Vector it does not loads it again
		if (TextureIDs[i]->path.compare(path) == 0)
		{
			ret = true;
			index = TextureIDs[i]->id;
			break;
		}

	}


	return ret;
}


bool ModuleTexture::Init(nlohmann::json config) {

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

	ChekeredID = CreateCheckeredTex();

	return true;
}

bool ModuleTexture::CleanUp() {

	if (ChekeredID > 0)
		glDeleteTextures(1, (GLuint*)&ChekeredID);

	for (int i = 0; i < TextureIDs.size();++i) {

		delete TextureIDs[i];
		TextureIDs[i] = nullptr;


	}

	return true;
}

uint ModuleTexture::CreateCheckeredTex() {

	App->GearConsole.AddLog(" Create checkered texture");

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

	uint id;
	// Affect the operation of subsequent glReadPixels as well as the unpacking of texture patterns
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Generate the texture ID
	glGenTextures(size, (GLuint*)&id);
	glBindTexture(GL_TEXTURE_2D, id);	//Binding texture


	//wrapping and filtering
	SetTextureOptions(GL_REPEAT, GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, Texture);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);//unbind buff texture




	return id;
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
		ResourceTexture* tmp2 = (ResourceTexture*)App->RS->CreateNewResource(RT_TEXTURE, "");


		App->GearConsole.AddLog(" Loading texture from %s ", path);

		ILinfo imageInfo;
		iluGetImageInfo(&imageInfo);

		if (imageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
			iluFlipImage();

		if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
		{
			texID = ToTexBuffer(1,ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),ilGetData());
		}
		
			

		CurrentTex = new Texture;
		CurrentTex->id = texID;
		CurrentTex->path = path;
		CurrentTex->Height = imageInfo.Height;
		CurrentTex->Width = imageInfo.Width;
		TextureIDs.push_back(CurrentTex);

		std::string filename = path;
		std::size_t found = filename.find_last_of("/\\");
		filename = filename.substr(0, found + 1);
		
		//may have prible duplicating textures
		tmp2->CreateMaterial(filename);

	}



	ilDeleteImages(1, (const ILuint*)&ImageID);

	return texID;

}

