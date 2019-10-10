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

		void DestroyPrim();


public:

	par_shapes_mesh* mesh =nullptr;
	GLuint	bufferID[2];

protected:
	Primitive_Type type;

};
#endif //__PRIMITIVE_H__
