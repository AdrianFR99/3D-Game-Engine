#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "glmath.h"

#include "ParFiles/par_shapes.h"

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

		void SetPos(vec3 pos);
		void SetRot(float angle, const vec3 &axis);
		void SetScale(float x,float y,float z);


		void SendToBuff();
		void Draw();

		void DestroyBuff();


public:

	par_shapes_mesh* mesh =nullptr;
	GLuint	bufferID[2];

protected:
	Primitive_Type type;

};

class Cube : public Primitives
{
public:
	Cube();
	Cube(float sizeX, float sizeY, float sizeZ);
	
public:
	vec3 size;
};

#endif //__PRIMITIVE_H__
