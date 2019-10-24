#include "Application.h"
#include "Primitives.h"
#include "ParFiles/par_shapes.h"

#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include "AssetMesh.h"

#include "mmgr/mmgr.h"

Primitives::Primitives(Primitive_Type type)
{

	CreatePrimitive(type);

	SendToBuff();
	
	App->Assets->Primitives_Vec.push_back(this);
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

	glGenBuffers(1, &UVC);
	assert(uv_coord != nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, UVC);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_uv, uv_coord, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Primitives::Draw() {


	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, App->Textures->CheckeredID);
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

void Primitives::CreatePrimitive(Primitive_Type type) {

	par_shapes_mesh*Mesh;

	switch(type)
	{

	case Primitive_Type::CUBE:

		Mesh = par_shapes_create_cube();
		

		break;
	case Primitive_Type::SPHERE:

		Mesh = par_shapes_create_subdivided_sphere(2);

		break;

	case Primitive_Type::CYLINDER:

		Mesh = par_shapes_create_cylinder(10,8);

		break;

	case Primitive_Type::CONE:

		Mesh = par_shapes_create_cone(10, 8);

		break;


	case Primitive_Type::DODECA:

		Mesh = par_shapes_create_dodecahedron();
		
		break;

	case Primitive_Type::TETRA:

		Mesh = par_shapes_create_tetrahedron();

		break;

	case Primitive_Type::OCTO:

		Mesh = par_shapes_create_octahedron();
		
		break;

	case Primitive_Type::ICOSA:

		Mesh = par_shapes_create_icosahedron();
		
		break;

	case Primitive_Type::BOTTLE:

		Mesh = par_shapes_create_klein_bottle(10,8);

		break;

	}
	
	num_vertex = Mesh->npoints * 3;
	vertices = new float3[num_vertex];

	num_index = Mesh->ntriangles * 3;
	indices = new uint[num_index];

	num_uv = Mesh->npoints*2;
	uv_coord = new float[num_uv];


	num_normals = num_vertex;

	for (uint i = 0; i < Mesh->npoints; ++i) {

		vertices[i].x = Mesh->points[i * 3];
		vertices[i].y = Mesh->points[(i * 3) + 1];
		vertices[i].z = Mesh->points[(i * 3) + 2];

	}

	for (uint i = 0; i < num_index; ++i)
	{
		indices[i] = Mesh->triangles[i];
	}

	for (uint i = 0; i < num_uv; ++i) {
			if (Mesh->tcoords != nullptr)
			uv_coord[i] = Mesh->tcoords[i];
			else
				uv_coord[i] = 0.0f;
	}

	if (Mesh->normals!=nullptr) {

		for (uint i = 0; i < num_normals; ++i) {

			normals[i].x = Mesh->normals[i * 3];
			normals[i].y = Mesh->normals[(i * 3) + 1];
			normals[i].z = Mesh->normals[(i * 3) + 2];
		}

	}



	par_shapes_free_mesh(Mesh);

}




void Primitives::toAssetMesh() {

	AssetMesh*NewMesh = new AssetMesh;


}