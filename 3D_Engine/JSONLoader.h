#ifndef __JSONLoader_H__
#define __JSONLoader_H__

#include "Globals.h"
#include "json/json.hpp"
#include <fstream>
#include <iomanip>

// for convenience
using json = nlohmann::json;

class JSONLoader
{
public:

	JSONLoader() {}
	~JSONLoader() {}

	bool Load(const char* FiletoLoad);
	bool Save(const char* data, json doc);

	bool done = false;

	json getFile();

	json file;
};

#endif
