#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__


#include "MathGeoLib/include/Math/float3.h"
#include "Globals.h"
#include "Gameobject.h"

enum class Primitive_Type
{
	CUBE,
	SPHERE,
	CYLINDER,
	CONE,
	DODECA,
	TETRA,
	OCTO,
	ICOSA,
	BOTTLE

};

typedef unsigned int GLuint;


class Primitives
{
public:
	Primitives(Primitive_Type type);
	~Primitives();

		void SetPos(float3 pos);
		void SetRot(float angle, const float3 &axis);
		void SetScale(float x,float y,float z);

		void SendToBuff();
		void Draw(Gameobject* tmp);
		void CreatePrimitive(Primitive_Type type);

		bool CleanUp();
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



#endif //__PRIMITIVE_H__
