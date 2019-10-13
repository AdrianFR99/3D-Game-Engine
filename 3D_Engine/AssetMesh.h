#ifndef __ASSETMESH_H__
#define __ASSETMESH_H__


#include "ModuleAssets.h"


struct aiMesh;
typedef float GLfloat;
typedef unsigned char GLubyte;


class AssetMesh 
{
public:
	AssetMesh();
	~AssetMesh();

	void importMesh(aiMesh* Mesh);
	void ToBuffer();

public:

	//buffer
	uint VBO;
	uint IBO;
	uint VAO;

	//indices
	uint num_index = 0;
	uint* indices = nullptr;
	
	//vertices
	uint num_vertex = 0;
	float* vertices = nullptr;
	
	/*uint num_UVs = 0;
	float*UVs = nullptr;*/

};

#endif // !__ASSETMESH_H__