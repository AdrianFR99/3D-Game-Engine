
#include "AssetMesh.h"

#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ComponentMesh.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#include "Application.h"
//#include "ModuleCamera3D.h"

#include "mmgr/mmgr.h"


AssetMesh::AssetMesh(){}

AssetMesh::~AssetMesh(){}

//NO DELETE

void AssetMesh::importMesh(aiMesh* Mesh) {

	LOG("Importing Mesh");


	App->GearConsole.AddLog(" Importing Mesh ");

	

	//vertices
	num_vertex = Mesh->mNumVertices;
	vertices = new float3[num_vertex];
	memcpy(vertices, Mesh->mVertices, sizeof(float3)*num_vertex);
	CalculateDistance();

	App->GearConsole.AddLog(" the Number of Vertices is %i ", num_vertex);

	//Indices
	num_index = Mesh->mNumFaces*3;
	indices = new uint[num_index];

	App->GearConsole.AddLog(" The number of inices is %i", num_index);

	App->GearConsole.AddLog(" The number of Triangles is %i",Mesh->mNumFaces);

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

		num_normals = num_vertex;
		normals = new float3[num_vertex];
		memcpy(normals, Mesh->mNormals, sizeof(float3)*num_vertex);
		num_normals_faces = Mesh->mNumFaces;
		normals_faces = new float3[num_normals_faces];
		normals_faces_pos = new float3[num_normals_faces];

		int iterator=0;
		for (int i = 0; i < num_index;i+=3) {



				float3 vert1 = vertices[indices[i + 2]];
				float3 vert2 = vertices[indices[i + 1]];
				float3 vert3 = vertices[indices[i]];

				float3 vector1 = vert2 - vert1;
				float3 vector2 = vert3 - vert1;

				normals_faces[iterator] = Cross(vector1, vector2);
				normals_faces_pos[iterator]=CenterTri(vert1,vert2,vert3);

				++iterator;


		}
	}

	if (Mesh->HasTextureCoords(0)) {

		num_uv = Mesh->mNumVertices * 2;//x and y
		uv_coord = new float[num_uv];

		for (int i = 0; i < num_vertex;++i) {

			uv_coord[i * 2] = Mesh->mTextureCoords[0][i].x;
			uv_coord[(i * 2)+1] = Mesh->mTextureCoords[0][i].y;

		}

		//num_uv = Mesh->mNumVertices;//x and y
		//uv_coord = new float3[num_uv];
		//memcpy(uv_coord, Mesh->mTextureCoords[0], sizeof(float) * num_uv);
	}


	App->GearConsole.AddLog(" The number of Vertex vertices is %i",num_normals);

	App->GearConsole.AddLog(" The number of Face normals is %i ",num_normals_faces);

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

	if (num_uv != 0)
	{
		assert(uv_coord!=nullptr);

		glGenBuffers(1, (GLuint*)&UVC);
		glBindBuffer(GL_ARRAY_BUFFER,UVC);
		glBufferData(GL_ARRAY_BUFFER,sizeof(float)*num_uv*3,uv_coord,GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


	}
}


void AssetMesh::DrawNormals (float width, uint lenght, float3 &colorNV, float3 &colorNF,float alpha, bool &faces, bool &vertex) {


	glBegin(GL_LINES);
	glLineWidth(width);
	uint Normal_length = lenght;


	if (vertex)
	{
	glColor4f(colorNV.x, colorNV.y, colorNV.z,alpha);
		for (uint j = 0; j < num_vertex; ++j)
		{
			glVertex3f(vertices[j].x, vertices[j].y, vertices[j].z);
			glVertex3f(vertices[j].x + normals[j].x* Normal_length,
				vertices[j].y + normals[j].y* Normal_length,
				vertices[j].z + normals[j].z* Normal_length
			);
		}


	}

	if (faces)
	{
			glColor4f(colorNF.x, colorNF.y, colorNF.z, alpha);
		for (uint j = 0; j < num_normals_faces; ++j)
		{
			glVertex3f(normals_faces_pos[j].x, normals_faces_pos[j].y, normals_faces_pos[j].z);
			float3 Aux = normals_faces[j].Normalized();
			glVertex3f(normals_faces_pos[j].x + Aux.x* Normal_length,
				normals_faces_pos[j].y + Aux.y* Normal_length,
				normals_faces_pos[j].z + Aux.z* Normal_length
			);

		}


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

//function to triangulate the position of the camera depending on the size of the meshes
void AssetMesh::CalculateDistance() {

	/*for (int i = 0; i < num_vertex; ++i)
	{
		if (vertices[i].x > maxX)
		{
			maxX = vertices[i].x;
		}
		if (vertices[i].x < minX)
		{
			minX = vertices[i].x;
		}

		if (vertices[i].y > maxY)
		{
			maxY = vertices[i].y;
		}
		if (vertices[i].y < minY)
		{
			minY = vertices[i].y;
		}

		if (vertices[i].z > maxZ)
		{
			maxZ = vertices[i].z;
		}
		if (vertices[i].z < minZ)
		{
			minZ = vertices[i].z;
		}
	}

	medX = (int)(maxX + minX)*0.5;

	medY = (int)(maxY + minY)*0.5;

	medZ = (int)(maxZ + minZ)*0.5;

	vec3 baseMax;
	baseMax.x = maxX;
	baseMax.y = maxY;
	baseMax.z = maxZ;

	vec3 baseMin;
	baseMin.x = minX;
	baseMin.y = minY;
	baseMin.z = minZ;

	float TriagulateBaseDistance = (float)length(baseMax - baseMin);

	if (TriagulateBaseDistance < 0)
		TriagulateBaseDistance = -(TriagulateBaseDistance);
	else
		TriagulateBaseDistance = TriagulateBaseDistance;



	faraway = (sqrt(3)*0.5)* TriagulateBaseDistance;

	if (faraway > App->camera->premadeDist)
		App->camera->premadeDist = faraway;

	App->camera->Reference.x = medX;

	App->camera->Reference.y = medY;

	App->camera->Reference.z = medZ;*/

}
