#ifndef __MODULEFILESYSTEM_H__
#define __MODULEFILESYSTEM_H__

#include "Module.h"
#include <vector>
#include "JSONLoader.h"

struct SDL_RWops;
int close_sdl_rwops(SDL_RWops *rw);

struct aiFileIO;


class ModuleFileSystem : public Module
{
public:

	ModuleFileSystem(Application* app, bool start_enabled = true, const char* game_path = nullptr);
	
	// Destructor
	~ModuleFileSystem();

	// Called before render is available
	bool Init(nlohmann::json config) override;

	// Called before quitting
	bool CleanUp() override;

	// Utility functions
	bool AddPath(const char* path_or_zip);
	bool Exists(const char* file) const;
	bool IsDirectory(const char* file) const;
	void CreateDirectory(const char* directory);
	void DiscoverFiles(const char* directory, std::vector<std::string>& file_list, std::vector<std::string>& dir_list) const;
	bool CopyFromOutsideFS(const char* full_path, const char* destination);
	bool Copy(const char* source, const char* destination);
	void SplitFilePath(const char* full_path, std::string* path, std::string* file = nullptr, std::string* extension = nullptr) const;
	void NormalizePath(char* full_path) const;
	void NormalizePath(std::string& full_path) const;

	// Open for Read/Write
	unsigned int Load(const char* path, const char* file, char** buffer) const;
	unsigned int Load(const char* file, char** buffer) const;
	SDL_RWops* Load(const char* file) const;
	void* BassLoad(const char* file) const;

	// IO interfaces for other libs to handle files via PHYSfs
	aiFileIO* GetAssimpIO();
	
	unsigned int Save(const char* file, const void* buffer, unsigned int size, bool append = false) const;
	//bool SaveUnique(std::string& output, const void* buffer, uint size, const char* path, const char* prefix, const char* extension);
	bool Remove(const char* file);

	const char* GetBasePath() const;
	const char* GetWritePath() const;
	const char* GetReadPaths() const;

	std::string GetFileExtension(const char * file_name);


	void FileCopyPaste(const char * filepath, const char * new_path);

	bool TextCmp(const char * text1, const char * text2);

	std::string ToLowerCase(std::string str);

	//std::string GetLibraryMeshPath();
	//std::string GetAssetsPath();
	//std::string GetLibraryTexturePath();

	std::string GetFileNameFromFilePath(const char * file_path);

	std::string GetPathFromFilePath(const char * file_path);

private:

	void CreateAssimpIO();
	
private:

	aiFileIO * AssimpIO = nullptr;
	
};

#endif // __MODULEFILESYSTEM_H__
