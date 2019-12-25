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
struct par_shapes_mesh_s;
typedef par_shapes_mesh_s par_shapes_mesh;


class Primitives
{
public:
	Primitives(Primitive_Type type);
	~Primitives();

		void SetPos(float3 pos);
		

		void SendToBuff();
		void Draw(Gameobject* tmp);
		void DrawNormals(float width,float lenght);
		void DefinePrimitive(Primitive_Type type);
	

		void CalculateDistance();
		bool CleanUp();


		void GenerateAABB();
		const AABB GetBBox() const;


		AABB bbox;


		par_shapes_mesh* CreateCube();
		
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

	//camera
	float maxX = 0.0f;
	float minX = -1.0f;
	float medX = 0.0f;
	float maxY = 0.0f;
	float minY = -1.0f;
	float medY = 0.0f;
	float maxZ = 0.0f;
	float minZ = -1.0f;
	float medZ = 0.0f;
	float basedistance = 0;
	float faraway = 0.0f;

	bool platonicSolid = false;

protected:
	Primitive_Type type;

};



#endif //__PRIMITIVE_H__
