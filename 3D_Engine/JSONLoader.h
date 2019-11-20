#ifndef __JSONLoader_H__
#define __JSONLoader_H__

#include "Globals.h"
#include "json/json.hpp"


// for convenience
//using json = nlohmann::json;
//this does not work, using the whole namespace

class JSON_Doc
{
public:
	JSON_Doc(nlohmann::json* Doc, const char* path);
	JSON_Doc(JSON_Doc& doc);
	~JSON_Doc();

	std::string GetPath();
	//void Save();
	//void CleanUp();


private:
	nlohmann::json* Doc = nullptr;
	std::string		 path;
};

class JSONLoader
{
public:

	JSONLoader() {}
	~JSONLoader() {}

	bool Load(const char* FiletoLoad);
	bool Save(const char* data, nlohmann::json doc);

	bool done = false;

	nlohmann::json getFile();

	JSON_Doc * CreateJSON(std::string path);

	nlohmann::json file;

private:
	std::list<JSON_Doc*> jsons_list;
};

#endif
