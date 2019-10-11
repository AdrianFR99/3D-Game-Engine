#include "AssetMesh.h"


#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

AssetMesh::AssetMesh():Asset(type=Asset_Type::MESH)
{



}

AssetMesh::~AssetMesh()
{
}

void AssetMesh::importMesh(aiMesh Mesh) {

	


}

void AssetMesh::ToBuffer() {

	
	
	glGenBuffers(2, buffer);// Gen VBO,IBP

	// Vertex Buffer Object
	assert(vertices != nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);// VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * num_vertex, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Index Buffer Object
	assert(indices != nullptr);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);// IBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * num_index, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	// Vertex Array Object

	glGenVertexArrays(1,&VAO);// Gen VAO
	glBindVertexArray(VAO);// VAO
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);// VBO 
	
	// Send Vertex struct info
	//Pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex,Pos)));
	glEnableVertexAttribArray(0);
	//Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex,Normal)));
	glEnableVertexAttribArray(1);
	//Color
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)(offsetof(Vertex,Color)));
	glEnableVertexAttribArray(2);
	//Tex coords
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex,TexCoord)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}