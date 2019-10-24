#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__


#include "MathGeoLib/include/Math/float3.h"
#include "Globals.h"


enum class Primitive_Type
{
	CUBE,
	SPHERE

};

typedef unsigned int GLuint;


class Primitives
{
public:
	Primitives();
	~Primitives();

		void SetPos(float3 pos);
		void SetRot(float angle, const float3 &axis);
		void SetScale(float x,float y,float z);


		virtual void SendToBuff();
		virtual	void Draw();
		virtual void SetVert_Ind(float3 size) {};

public:

	uint VBO=0;
	uint IBO=0;
	uint UVC=0;//uv coord

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

	uint num_uv = 0;
	float*uv_coord = nullptr;
	uint ID_Texture;


protected:
	Primitive_Type type;

};

class Cube : public Primitives
{
public:

	Cube(float sizeX, float sizeY, float sizeZ);

	void SetVert_Ind(float3 size) override;

	
public:

	uint num_faces = 6;
	
	//float ID_Mat[72]={
	//		//Front face
	//		1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1, 1,   // v0,v1,v2,v3 
	//		//Right face
	//		1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1,   // v0,v3,v4,v5
	//		//Top face
	//		1, 1, 1, 1, 1, -1, -1, 1, -1, -1, 1, 1,   // v0,v5,v6,v1 
	//		//Left face
	//		-1, 1, 1, -1, 1, -1, -1, -1, -1, -1, -1, 1,   // v1,v6,v7,v2 
	//		//Bottom face
	//		-1, -1, -1, 1, -1, -1, 1, -1, 1, -1, -1, 1,   // v7,v4,v3,v2 
	//		//Back face
	//		1, -1, -1, -1, -1, -1, -1, 1, -1, 1, 1, -1    // v4,v7,v6,v5 
	//};

	float3 size;


	
};

#endif //__PRIMITIVE_H__
