#include "Primitives.h"

#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"

Primitives::Primitives()
{
}


Primitives::~Primitives()
{
	


}

void Primitives::DestroyBuff() {

	
	glDeleteBuffers(2, bufferID);

}

void Primitives::SetPos(vec3 pos) {

	par_shapes_translate(mesh, pos.x, pos.y, pos.z);

}

void Primitives::SetRot(float angle, const vec3 &axis) {

	float Aux[] = {axis.x,axis.y,axis.z};

	par_shapes_rotate(mesh,angle,Aux);


}

void Primitives::SetScale(float x, float y, float z) {


	par_shapes_scale(mesh, x, y, z);

}

void Primitives::SendToBuff() {

	
	glGenBuffers(2, bufferID);


	glBindBuffer(GL_ARRAY_BUFFER, bufferID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->npoints * 3, mesh->points, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PAR_SHAPES_T) * mesh->ntriangles * 3, mesh->triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	par_shapes_free_mesh(mesh);
}

void Primitives::Draw() {


	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, bufferID[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID[1]);
	glDrawElements(GL_TRIANGLES, mesh->ntriangles * 3, GL_UNSIGNED_SHORT, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);

}


// CUBE ============================================
Cube::Cube() : Primitives(), size(1.0f, 1.0f, 1.0f)
{
	type = Primitive_Type::CUBE;
	mesh = par_shapes_create_cube();
	par_shapes_scale(mesh, size.x, size.y,size.z);
	par_shapes_translate(mesh,0,0,0);
	
}

Cube::Cube(float sizeX, float sizeY, float sizeZ) : Primitives(), size(sizeX, sizeY, sizeZ)
{
	type = Primitive_Type::CUBE;
	mesh = par_shapes_create_cube();
	par_shapes_scale(mesh, sizeX, sizeY, sizeZ);
	par_shapes_translate(mesh, 0, 0, 0);

}
