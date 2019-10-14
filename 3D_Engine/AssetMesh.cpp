
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
		memcpy(normals, Mesh->mNormals,sizeof(float3)*num_vertex);
		

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_index*3, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glGenBuffers(1, &NBO);// Gen VBO,IBP

	// Vertex Buffer Object
	assert(normals != nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, NBO);// NBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * num_vertex, normals, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);



}