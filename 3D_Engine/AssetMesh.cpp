
#include "AssetMesh.h"

#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"




AssetMesh::AssetMesh(){}

AssetMesh::~AssetMesh(){}

void AssetMesh::importMesh(aiMesh* Mesh) {
	
	LOG("Importing Mesh");

	//vertices
	num_vertex = Mesh->mNumVertices;
	vertices = new float3[num_vertex];
	memcpy(vertices,Mesh->mVertices,sizeof(float3)*num_vertex);

	//Indices
	num_index = Mesh->mNumFaces*3;
	indices = new uint[num_index];

	if (Mesh->HasFaces()) {
		//each face is a triangle
		for (uint i = 0; i < Mesh->mNumFaces; ++i)
		{
			if (Mesh->mFaces[i].mNumIndices == 3)
			{
				memcpy(&indices[i * 3], Mesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}
	}
	if (Mesh->HasNormals())
	{

		
		normals = new float3[num_vertex];
		memcpy(normals, Mesh->mNormals, sizeof(float3)*num_vertex);
		num_normals_faces = Mesh->mNumFaces;
		normals_faces = new float3[num_normals_faces];
		normals_faces_pos = new float3[num_normals_faces];

		int iterator=0;
		for (int i = 0; i < num_vertex;i+=3) {

			if (i % 3 == 0 && i!=0) {
				
				float3 vert1 = vertices[i + 2];
				float3 vert2 = vertices[i + 1];
				float3 vert3 = vertices[i];
			
				float3 vector1 = vert2 - vert1;
				float3 vector2 = vert3 - vert1;
				
				normals_faces[iterator] = Cross(vector1, vector2);
				normals_faces_pos[iterator]=CenterTri(vert1,vert2,vert3);

				++iterator;
			}

		}
	}

	ToBuffer();

}

void AssetMesh::ToBuffer() {

	
	
	glGenBuffers(1,&VBO);// Gen VBO,IBP

	// Vertex Buffer Object
	assert(vertices != nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER,VBO);// VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * num_vertex, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Index Buffer Object
	assert(indices != nullptr);
	glGenBuffers(1, &IBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);// IBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_index, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//glGenBuffers(1, &NBO);// Gen NBO

	//// Vertex Buffer Object
	//assert(normals != nullptr);

	//glBindBuffer(GL_ARRAY_BUFFER, NBO);// NBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * num_vertex, normals, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


	//glGenBuffers(1, &NFBO);// Gen NFBO

	//// Vertex Buffer Object
	//assert(normals != nullptr);

	//glBindBuffer(GL_ARRAY_BUFFER, NBO);// NBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * num_normals_faces, normals_faces, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void AssetMesh::DrawNormals(float width, uint lenght, float3 &colorNV, float3 &colorNF,float alpha) {

	
	glBegin(GL_LINES);
	glLineWidth(width);
	uint Normal_length = lenght;
	
	glColor4f(colorNV.x, colorNV.y, colorNV.z,alpha);

	for (uint j = 0; j < num_vertex; ++j)
	{
		glVertex3f(vertices[j].x, vertices[j].y, vertices[j].z);
		glVertex3f(vertices[j].x + normals[j].x* Normal_length,
					vertices[j].y + normals[j].y* Normal_length,
					vertices[j].z + normals[j].z* Normal_length
		);
	}

	glColor4f(colorNF.x, colorNF.y, colorNF.z, alpha);


	for (uint j = 0; j < num_normals_faces; ++j)
	{
		glVertex3f(normals_faces_pos[j].x, normals_faces_pos[j].y,normals_faces_pos[j].z);
		float3 Aux=normals_faces[j].Normalized();
		glVertex3f(normals_faces_pos[j].x + Aux.x* Normal_length,
				normals_faces_pos[j].y + Aux.y* Normal_length,
				normals_faces_pos[j].z + Aux.z* Normal_length
		);

	}

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnd();

}
float3 AssetMesh::CenterTri(float3&vertex1, float3&vertex2, float3&vertex3) {

	float3 Aux;

	Aux.x=  (vertex1.x + vertex2.x + vertex3.x)/3;
	Aux.y = (vertex1.y + vertex2.y + vertex3.y)/3;
	Aux.z = (vertex1.z + vertex2.z + vertex3.z)/3;

	return Aux;
}