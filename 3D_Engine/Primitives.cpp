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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertex, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IBO);
	assert(indices != nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) *num_index,indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &UVC);
	assert(uv_coord != nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, UVC);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_uv, uv_coord, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Primitives::Draw() {


	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, ID_Texture);
	glActiveTexture(GL_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, UVC);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);


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

	num_vertex = 72; //4*3*6//four vertices per face,six faces,3D space
	num_index = 36; //6*2*3 //six faces, two triangles per face//3D space
	num_uv = num_vertex * 2 / 3;//3D space->2D space

	SetVert_Ind(size);

	ID_Texture = App->Textures->CheckeredID;

	SendToBuff();

	App->Assets->Primitives_Vec.push_back(this);
		
}

void Cube::SetVert_Ind(float3 size) {

	float size_X = size.x * 0.5f;
	float size_Y = size.y * 0.5f;
	float size_Z = size.z * 0.5f;

	vertices = new float[num_vertex] {

			//Front face
			size_X, size_Y, size_Z, -size_X, size_Y, size_Z, -size_X, -size_Y, size_Z, size_X, -size_Y, size_Z,   // v0,v1,v2,v3 
			//Right face
			size_X, size_Y, size_Z, size_X, -size_Y, size_Z, size_X, -size_Y, -size_Z, size_X, size_Y, -size_Z,   // v0,v3,v4,v5
			//Top face
			size_X, size_Y, size_Z, size_X, size_Y, -size_Z, -size_X, size_Y, -size_Z, -size_X, size_Y, size_Z,   // v0,v5,v6,v1 
			//Left face
			-size_X, size_Y, size_Z, -size_X, size_Y, -size_Z, -size_X, -size_Y, -size_Z, -size_X, -size_Y, size_Z,   // v1,v6,v7,v2 
			//Bottom face
			-size_X, -size_Y, -size_Z, size_X, -size_Y, -size_Z, size_X, -size_Y, size_Z, -size_X, -size_Y, size_Z,   // v7,v4,v3,v2 
			//Back face
			size_X, -size_Y, -size_Z, -size_X, -size_Y, -size_Z, -size_X, size_Y, -size_Z, size_X, size_Y, -size_Z    // v4,v7,v6,v5 

	};

	indices = new uint[num_index]{

		//Front face
		0, 1, 2,   2, 3, 0,    // v0-v1-v2, v2-v3-v0 
		//Right face
		4, 5, 6,   6, 7, 4,    // v0-v3-v4, v4-v5-v0 
		//Top face
		8, 9,10,  10,11, 8,    // v0-v5-v6, v6-v1-v0 
		//Left face
		12,13,14,  14,15,12,    // v1-v6-v7, v7-v2-v1
		//Bottom face
		16,17,18,  18,19,16,    // v7-v4-v3, v3-v2-v7
		//Back face
		20,21,22,  22,23,20     // v4-v7-v6, v6-v5-v4						


	};

	uv_coord = new float[num_uv] {

			//Front face
			1, 0, 0, 0, 0, 1, 1, 1,   // v0,v1,v2,v3 
			//Right face
			0, 0, 0, 1, 1, 1, 1, 0,   // v0,v3,v4,v5 
			//Top face
			1, 1, 1, 0, 0, 0, 0, 1,   // v0,v5,v6,v1 
			//Left face
			1, 0, 0, 0, 0, 1, 1, 1,   // v1,v6,v7,v2 
			//Bottom face
			0, 1, 1, 1, 1, 0, 0, 0,   // v7,v4,v3,v2 
			//Back face
			0, 1, 1, 1, 1, 0, 0, 0    // v4,v7,v6,v5 
	};


}