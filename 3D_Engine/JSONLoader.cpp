#include "JSONLoader.h"
#include <assert.h>
#include <fstream>

// for convenience
using json = nlohmann::json;

bool JSONLoader::Load(const char * FiletoLoad)
{
	//open a incoming stream of data
	std::ifstream incomingStream;
	incomingStream.open(FiletoLoad);

	//create a json doc
	json doc;

	//parse dta in document
	doc = json::parse(FiletoLoad);

	if (FiletoLoad == nullptr || incomingStream.is_open())
	{
		LOG("Json File load error");
		return false;
	}
	
	//clos stream of data
	incomingStream.close();
	file = doc;

	return true;
}

bool JSONLoader::Save(const char * data, json doc)
{
	//save to json file

	//open an output stream of data
	std::ofstream outStream;

	//Where to output
	outStream.open(data);

	//insert data
	outStream << std::setw(4) << doc << std::endl;

	//close stream
	outStream.close();


	return false;
}

json JSONLoader::getFile()
{
	return file;
}