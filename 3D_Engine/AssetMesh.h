#ifndef __ASSETMESH_H__
#define __ASSETMESH_H__


#include "ModuleAssets.h"


struct aiMesh;
typedef float GLfloat;
typedef unsigned char GLubyte;


struct Vertex_Data
{
	GLfloat Pos[3];
	GLfloat Normal[3];
	GLubyte Color[4];
	GLfloat TexCoord[2];
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
	

};

#endif // !__ASSETMESH_H__