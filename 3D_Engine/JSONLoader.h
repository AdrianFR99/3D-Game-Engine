#ifndef __JSONLoader_H__
#define __JSONLoader_H__

#include "Globals.h"
#include "json/json.hpp"


// for convenience
//using json = nlohmann::json;
//this does not work, using the whole namespace

class JSONLoader
{
public:

	JSONLoader() {}
	~JSONLoader() {}

	bool Load(const char* FiletoLoad);
	bool Save(const char* data, nlohmann::json doc);

	bool done = false;

	nlohmann::json getFile();

	nlohmann::json file;

	std::string Serialize(nlohmann::json jsonfile);

private:
	
};

#endif