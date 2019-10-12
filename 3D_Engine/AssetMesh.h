#pragma once
#include "ModuleAssets.h"


struct aiMesh;

struct Vertex_Data
{
	GLfloat Pos[3];
	GLfloat Normal[3];
	GLfloat TexCoord[2];
	GLubyte Color[4];
};

class AssetMesh :public Asset
{
public:
	AssetMesh();
	~AssetMesh();

	void importMesh(aiMesh* Mesh);
	void ToBuffer();

public:

	uint* buffer;
	uint VAO;

	uint num_index = 0;
	uint* indices = nullptr;
	
	uint num_vertex = 0;
	Vertex_Data* vertices = nullptr;



	Asset_Type Type;
};

