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
	uint UVC;//uv coord

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
	float3*normals_faces_pos = nullptr;

	//camera
	int maxX = 0;
	int minX = 0;
	int medX = 0;
	int maxY = 0;
	int minY = 0;
	int medY = 0;
	int maxZ = 0;
	int minZ = 0;
	int medZ = 0;
	float basedistance = 0;
	float faraway = 0.0f;

	uint num_uv = 0;
	float*uv_coord = nullptr;

public:
	 void DrawNormals (float width,uint lenght,float3 &colorNV, float3 &colorNF,float alpha, bool &faces, bool &vertex) ;
	float3 CenterTri(float3&vertex1,float3&vertex2,float3&vertex3);

	void CalculateDistance();
};

#endif // !__ASSETMESH_H__
