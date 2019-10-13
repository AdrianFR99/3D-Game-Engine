
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
	vertices = new float[num_vertex*3];
	memcpy(vertices,Mesh->mVertices,sizeof(float)*num_vertex*3);

	//Indeces
	num_index = Mesh->mNumFaces*3;
	indices = new uint[num_index];

	if (Mesh->HasFaces()) {
		// Assume each face is a triangle
		for (uint i = 0; i < Mesh->mNumFaces; ++i)
		{
			if (Mesh->mFaces[i].mNumIndices == 3)
			{
				memcpy(&indices[i * 3], Mesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}

		}

	}
	
	


	////Normals
	//if (Mesh->HasNormals())
	//	for (int i = 0; i < num_vertex;++i){
	//		//	memcpy(Normals, mesh->mNormals, sizeof(float3)*mesh->mNumVertices);
	//		vertices[i].Normal[0] = (GLfloat)Mesh->mNormals[i].x;
	//		vertices[i].Normal[1] = (GLfloat)Mesh->mNormals[i].y;
	//		vertices[i].Normal[2] = (GLfloat)Mesh->mNormals[i].z;
	//	}
	////Color
	//for (int i = 0; i < num_vertex;++i) {
	//	if (Mesh->HasVertexColors(i)) {
	//		vertices[i].Color[0] = (GLubyte)Mesh->mColors[i]->r;
	//		vertices[i].Color[1] = (GLubyte)Mesh->mColors[i]->g;
	//		vertices[i].Color[2] = (GLubyte)Mesh->mColors[i]->b;
	//		vertices[i].Color[3] = (GLubyte)Mesh->mColors[i]->a;
	//	}
	//}
	//TexCoord





	ToBuffer();

}

void AssetMesh::ToBuffer() {

	
	
	glGenBuffers(1,&VBO);// Gen VBO,IBP

	// Vertex Buffer Object
	assert(vertices != nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER,VBO);// VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertex*3, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Index Buffer Object
	assert(indices != nullptr);
	glGenBuffers(1, &IBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);// IBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_index*3, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	

}