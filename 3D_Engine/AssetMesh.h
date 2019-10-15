#ifndef __ASSETMESH_H__
#define __ASSETMESH_H__


#include "ModuleAssets.h"

#include "MathGeoLib/include/Math/float3.h"

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
	uint NBO;
	//indices
	uint num_index = 0;
	uint* indices = nullptr;
	
	//vertices
	uint num_vertex = 0;
	float3* vertices = nullptr;

	//Normal
	uint num_normals = 0;
	uint num_normals_faces = 0;
	float3*normals = nullptr;
	float3*normals_faces = nullptr;


};

#endif // !__ASSETMESH_H__