
#include "AssetMesh.h"

#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"




AssetMesh::AssetMesh():Asset(Asset_Type::MESH){}

AssetMesh::~AssetMesh(){}

void AssetMesh::importMesh(aiMesh* Mesh) {
	
	LOG("Importing Mesh");

	//Filling struct Vertex Data
	num_vertex = Mesh->mNumVertices;
	vertices = new Vertex_Data[num_vertex];
	//position
	for (int i = 0; i < num_vertex;++i) {

		vertices[i].Pos[0] = (GLfloat)Mesh->mVertices[i].x;
		vertices[i].Pos[1] = (GLfloat)Mesh->mVertices[i].y;
		vertices[i].Pos[2] = (GLfloat)Mesh->mVertices[i].z;
	}
	//Normals
	if (Mesh->HasNormals())
		for (int i = 0; i < num_vertex;++i){
			//	memcpy(Normals, mesh->mNormals, sizeof(float3)*mesh->mNumVertices);
			vertices[i].Normal[0] = (GLfloat)Mesh->mNormals[i].x;
			vertices[i].Normal[1] = (GLfloat)Mesh->mNormals[i].y;
			vertices[i].Normal[2] = (GLfloat)Mesh->mNormals[i].z;
		}
	//Color
	for (int i = 0; i < num_vertex;++i) {
		if (Mesh->HasVertexColors(i)) {
			vertices[i].Color[0] = (GLubyte)Mesh->mColors[i]->r;
			vertices[i].Color[1] = (GLubyte)Mesh->mColors[i]->g;
			vertices[i].Color[2] = (GLubyte)Mesh->mColors[i]->b;
			vertices[i].Color[3] = (GLubyte)Mesh->mColors[i]->a;
		}
	}
	//TexCoord
	for (int i = 0; i < num_vertex; ++i)
	{
		if (Mesh->HasTextureCoords(i))
		{
			vertices[i].TexCoord[0] = (GLfloat)Mesh->mTextureCoords[i]->x;
			vertices[i].TexCoord[1] = (GLfloat)Mesh->mTextureCoords[i]->y;
		}
	}

	//Index

	num_index = Mesh->mNumFaces*3;
	indices = new uint[num_index];

	if (Mesh->HasFaces()) {

		for (int i = 0; i < num_index;++i) {
			
			indices[i*3] = Mesh->mFaces[i].mIndices[0];
			indices[i*3+1] = Mesh->mFaces[i].mIndices[1];
			indices[i*3+2] = Mesh->mFaces[i].mIndices[2];



		}


	}


	ToBuffer();

}

void AssetMesh::ToBuffer() {

	
	
	glGenBuffers(2, buffer);// Gen VBO,IBP

	// Vertex Buffer Object
	assert(vertices != nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);// VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_Data) * num_vertex, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Index Buffer Object
	assert(indices != nullptr);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);// IBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * num_index, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	// Vertex Array Object

	glGenVertexArrays(1,&VAO);// Gen VAO
	glBindVertexArray(VAO);// VAO
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);// VBO 
	
	/* Send Vertex struct info
	Pos*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_Data), (void*)(offsetof(Vertex_Data,Pos)));
	glEnableVertexAttribArray(0);
	//Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_Data), (void*)(offsetof(Vertex_Data,Normal)));
	glEnableVertexAttribArray(1);
	//Color
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex_Data), (void*)(offsetof(Vertex_Data,Color)));
	glEnableVertexAttribArray(2);
	//Tex coords
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_Data), (void*)(offsetof(Vertex_Data,TexCoord)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}