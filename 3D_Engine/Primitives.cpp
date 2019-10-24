#include "Application.h"
#include "Primitives.h"
#include "ParFiles/par_shapes.h"

#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"


#include "mmgr/mmgr.h"

Primitives::Primitives()
{
	
}


Primitives::~Primitives()
{

	glDeleteBuffers(1, (GLuint*)&VBO);
	glDeleteBuffers(1, (GLuint*)&IBO);
	glDeleteBuffers(1, (GLuint*)&UVC);
	
	delete[] vertices;
	vertices = nullptr;

	delete[] indices;
	indices = nullptr;

	delete[] uv_coord;
	uv_coord = nullptr;

	

}


void Primitives::SetPos(float3 pos) {

	/*par_shapes_translate(mesh, pos.x, pos.y, pos.z);*/

}

void Primitives::SetRot(float angle, const float3 &axis) {

	//float Aux[] = {axis.x,axis.y,axis.z};

	//par_shapes_rotate(mesh,angle,Aux);


}

void Primitives::SetScale(float x, float y, float z) {


	/*par_shapes_scale(mesh, x, y, z);*/

}

void Primitives::SendToBuff() {

	glGenBuffers(1,&VBO);
	assert(vertices != nullptr);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * num_vertex, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IBO);
	assert(indices != nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) *num_index,indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glGenBuffers(1, &UVC);
	//assert(uv_coord != nullptr);

	//glBindBuffer(GL_ARRAY_BUFFER, UVC);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_uv, uv_coord, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Primitives::Draw() {


	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);

	/*glBindTexture(GL_TEXTURE_2D, App->Textures->CheckeredID);
	glActiveTexture(GL_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, UVC);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);*/


	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glVertexPointer(3, GL_FLOAT, 0, NULL); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL); 

	
	glDisable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
}


// Cube

Cube::Cube(float sizeX, float sizeY, float sizeZ) : Primitives(), size(float3(sizeX, sizeY, sizeZ))
{
	type = Primitive_Type::CUBE;
	
	

	//num_vertex = 72; //4*3*6//four vertices per face,six faces,3D space
	//num_index = 36; //6*2*3 //six faces, two triangles per face//3D space
	//num_uv = num_vertex * 2 / 3;//3D space->2D space

	SetVert_Ind(size);

	SendToBuff();

	App->Assets->Primitives_Vec.push_back(this);
		
}

void Cube::SetVert_Ind(float3 size) {

	par_shapes_mesh*Mesh = par_shapes_create_cube();

	num_vertex = Mesh->npoints*3;
	vertices = new float3[num_vertex];


	num_uv = num_uv;
	uv_coord = new float[num_uv];

	for (uint i = 0; i < Mesh->npoints;++i) {

		vertices[i].x = Mesh->points[i*3];
		vertices[i].y = Mesh->points[(i*3)+1];
		vertices[i].z = Mesh->points[(i*3)+2];
	}
	
	num_index = Mesh->ntriangles * 3;
	indices = new uint[num_index];

	for (uint i = 0; i < Mesh->ntriangles * 3; i++)
	{
		indices[i]=Mesh->triangles[i];
	}

	
	par_shapes_free_mesh(Mesh);

}