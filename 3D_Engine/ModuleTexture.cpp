#include "Application.h"
#include "ModuleTexture.h"
#include "ResourceManager.h"

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

bool ModuleTexture::findTextureinList(std::string path, int& index, std::string& reference_name)
{
	bool ret = false;

	for (int i = 0; i < TextureIDs.size(); ++i) {

		//if it pins the texture path in the Vector it does not loads it again
		if (TextureIDs[i]->path.compare(path) == 0)
		{
			ret = true;
			index = TextureIDs[i]->id;
			reference_name = TextureIDs[i]->ResourceID;
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

bool ModuleTexture::LoadID(const char * filepath, std::vector<Resource*>& resources,ResourceTexture& rtex)
{
	bool ret = false;

	// Load texture
	if (ilLoad(IL_TYPE_UNKNOWN, filepath))
	{
		// Get file name
		std::string file_name = App->FileSystem->GetFileNameFromFilePath(filepath);

		// Create texture
		/*rtex = (ResourceTexture*)App->RS->CreateNewResource(Resource::ResourceType::RT_TEXTURE, "");*/

		// Get texture info
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);

		// Rotate if origin is upper left
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
			//rtex->SetFlipped(true);
		}

		// Convert image to rgb and a byte chain
		ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

		// Save data
		rtex.SetData(ilGetData(), ilGetInteger(IL_IMAGE_SIZE_OF_DATA), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_FORMAT),
			GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);

		// Set name
		rtex.SetFileName(file_name.c_str());

		// Export it to Library
		//App->resource_manager->SaveResourceIntoFile(rtex);

		ilDeleteImages(1, &ImageInfo.Id);

		//resources.push_back(rtex);

		ret = true;
	}
	else
	{
		LOG("Cannot load image %s. Error: %s", filepath, iluErrorString(ilGetError()));
	}

	return ret;
}

uint ModuleTexture::CreateTexture(const char*path, ResourceTexture& tmp2) {

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
		CurrentTex->ResourceID = tmp2.GetUniqueId();
		TextureIDs.push_back(CurrentTex);

		std::string filename = path;
		std::size_t found = filename.find_last_of("/\\");
		filename = filename.substr(0, found + 1);
		
		tmp2.Comp_Material.path = filename;
		tmp2.DiffuseID = texID;
		tmp2.currentID = texID;
		tmp2.CheckeredID = ChekeredID;


	}



	ilDeleteImages(1, (const ILuint*)&ImageID);

	return texID;

}

uint ModuleTexture::CreateTextureFromFile(const char* path, uint &width, uint &height, uint LibUID) const
{
	// --- In this function we use devil to load an image using the path given, extract pixel data and then create texture using CreateTextureFromImage ---

	uint TextureID = 0;

	if (path == nullptr)
	{
		LOG("|[error]: Error at loading texture from path. ERROR: Path %s was nullptr", path);
		return TextureID;
	}

	std::string final_path = path;

	// --- Generate the image name (ID for buffer) ---
	uint ImageName = 0;
	ilGenImages(1, (ILuint*)&ImageName);

	// --- Bind the image ---
	ilBindImage(ImageName);

	bool load_existing = false;
	std::string name = TEXTURES_FOLDER;
	name.append(std::to_string(LibUID));
	name.append(".dds");

	// --- Look for meta, if found load image from library ---
	if (App->RS->IsFileImported(path))
	{
		std::string uid = App->RS->GetUIDFromMeta(path);

		std::string lib_Tex = TEXTURES_FOLDER;
		lib_Tex.append(uid);
		lib_Tex.append(".dds");
		final_path = lib_Tex;

		load_existing = true;
	}
	else if (final_path.find("Library") != std::string::npos)
		load_existing = true;
	else
	{
		std::string libuid = std::to_string(LibUID);
		App->RS->CreateMetaFromUID(libuid, path);
	}

	// --- Load the image into binded buffer and create texture from its pixel data ---
	if (ilLoadImage(final_path.data()))
		CreateTextureFromImage(TextureID, width, height, name.data(), load_existing);
	else
		LOG("|[error]: DevIL could not load the image. ERROR: %s", iluErrorString(ilGetError()));

	// --- Release Image data (we have already extracted the necessary information) ---
	ilDeleteImages(1, (const ILuint*)&ImageName);

	// --- Returning the Texture ID so a mesh can use it, note that this variable is filled by CreateTextureFromPixels ---

	return TextureID;
}

inline void ModuleTexture::CreateTextureFromImage(uint &TextureID, uint &width, uint &height, const char* path, bool load_existing) const
{
	// --- Attention!! If the image is flipped, we flip it back --- 
	ILinfo imageInfo;
	iluGetImageInfo(&imageInfo);

	width = imageInfo.Width;
	height = imageInfo.Height;

	if (imageInfo.Origin == IL_ORIGIN_UPPER_LEFT && !load_existing)
		iluFlipImage();

	// --- Convert the image into a suitable format to work with ---
	if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
	{
		// --- Create the texture ---
		//

		//
		//TextureID = CreateTextureFromPixels(ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_FORMAT), ilGetData());

		if (!load_existing)
		{
			// --- Save to Lib ---
			ILuint size;
			ILubyte *data;
			ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);// To pick a specific DXT compression use
			size = ilSaveL(IL_DDS, NULL, 0); // Get the size of the data buffer

			if (size > 0) {
				data = new ILubyte[size]; // allocate data buffer

				if (ilSaveL(IL_DDS, data, size) > 0) // Save to buffer with the ilSaveIL function
					App->FileSystem->Save(path, data, size);

				delete[] data;
			}

		}
	}
	else
		LOG("|[error]: Image conversion failed. ERROR: %s", iluErrorString(ilGetError()));
}

uint ModuleTexture::CreateTextureFromPixels(int internalFormat, uint width, uint height, uint format, const void* pixels, bool CheckersTexture) const
{
	uint TextureID = 0;

	// --- Generate the texture ID ---
	glGenTextures(1, (GLuint*)&TextureID);
	// --- Bind the texture so we can work with it---
	glBindTexture(GL_TEXTURE_2D, TextureID);

	/*SetTextureParameters(CheckersTexture);*/

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	if (!CheckersTexture)
	{
		// --- Generate Mipmap of the recently created texture (Note that we are using it in texture size reduction only)---
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// --- Unbind texture ---
	glBindTexture(GL_TEXTURE_2D, 0);

	LOG("Loaded Texture: ID: %i , Width: %i , Height: %i ", TextureID, width, height);

	// --- Returning id so a mesh can use it (and destroy buffer when done) ---

	return TextureID;
}