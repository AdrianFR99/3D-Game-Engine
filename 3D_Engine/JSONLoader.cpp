#include "JSONLoader.h"
#include <fstream>
#include <iomanip>


// for convenience
//using json = nlohmann::json;

bool JSONLoader::Load(const char * FiletoLoad)
{
	bool ret = false;


	//open a incoming stream of data
	std::ifstream incomingStream;
	incomingStream.open(FiletoLoad);
	if (!incomingStream.is_open())
	{
		assert(incomingStream.is_open());

	}
	
	


	//using a json doc name file in .h
	//file

	//parse dta in document
	file = nlohmann::json::parse(incomingStream);

	if (FiletoLoad == nullptr || incomingStream.is_open())
	{
		LOG("Json File load error");
	
		ret = false;
	}
	

	
	//close stream of data
	incomingStream.close();


	return ret;
}

bool JSONLoader::Save(const char * data, nlohmann::json doc)
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

nlohmann::json JSONLoader::getFile()
{
	return file;
}

std::string JSONLoader::Serialize(nlohmann::json jsonfile)
{
	std::string data;
	data = jsonfile.dump(4);

	return data;
}
