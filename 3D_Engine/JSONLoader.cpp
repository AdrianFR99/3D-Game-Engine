#include "JSONLoader.h"
#include <fstream>
#include <iomanip>


// for convenience
//using json = nlohmann::json;

bool JSONLoader::Load(const char * FiletoLoad)
{

	//open a incoming stream of data
	std::ifstream incomingStream;
	incomingStream.open(FiletoLoad);
	assert(incomingStream.is_open());


	//using a json doc name file in .h
	//file

	//parse dta in document
	file = nlohmann::json::parse(incomingStream);

	if (FiletoLoad == nullptr || incomingStream.is_open())
	{
		LOG("Json File load error");
	
		return false;
	}
	

	
	//close stream of data
	incomingStream.close();


	return true;
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

JSON_Doc::JSON_Doc(nlohmann::json* Doc2, const char* _path)
{
	Doc = Doc2;
	path = _path;
}

JSON_Doc::JSON_Doc(JSON_Doc & doc2)
{
	Doc = doc2.Doc;
	path = doc2.path;
}

JSON_Doc::~JSON_Doc()
{
}

std::string JSON_Doc::GetPath()
{
	return path.data();
}
