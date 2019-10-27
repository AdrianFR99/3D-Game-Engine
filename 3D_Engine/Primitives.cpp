#include "Application.h"
#include "Primitives.h"

#include "ParFiles/par_shapes.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include "AssetMesh.h"

#include "mmgr/mmgr.h"

Primitives::Primitives(Primitive_Type type)
{

	DefinePrimitive(type);
	SendToBuff();


}


Primitives::~Primitives()
{

}

bool Primitives::CleanUp() {


	glDeleteBuffers(1, (GLuint*)&VBO);
	glDeleteBuffers(1, (GLuint*)&IBO);
	glDeleteBuffers(1, (GLuint*)&UVC);

	delete[] vertices;
	vertices = nullptr;

	delete[] indices;
	indices = nullptr;

	if (!platonicSolid) {

		delete[] uv_coord;
		uv_coord = nullptr;

		delete[] normals;
		normals = nullptr;

	}
	return true;
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

void Primitives::Draw(Gameobject* tmp) {


	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	glBindTexture(GL_TEXTURE_2D, tmp->materialPointer->GetCurrentTextureID());
	glActiveTexture(GL_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, UVC);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);


	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	if (!platonicSolid) {
		DrawNormals(2.0f, 1.0f);
	}
}

void Primitives::DrawNormals(float width, float lenght) {


	glBegin(GL_LINES);
	glLineWidth(width);
	uint Normal_length = lenght;

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

	for (uint j = 0; j < num_vertex; ++j)
	{
		glVertex3f(vertices[j].x, vertices[j].y, vertices[j].z);
		glVertex3f(vertices[j].x + normals[j].x* Normal_length,
			vertices[j].y + normals[j].y* Normal_length,
			vertices[j].z + normals[j].z* Normal_length
		);

	}

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


	glEnd();

}



void Primitives::DefinePrimitive(Primitive_Type type) {

	par_shapes_mesh*Mesh=nullptr;
	par_shapes_mesh*Aux=nullptr;//used for those primitves which don't contain normals or UVs(platonic solids)

	switch(type)
	{

	case Primitive_Type::CUBE:
		/*platonicSolid = true;*/
		Mesh = CreateCube();

		break;
	case Primitive_Type::SPHERE:

		Mesh = par_shapes_create_parametric_sphere(20,20);

		break;

	case Primitive_Type::CYLINDER:

		Mesh = par_shapes_create_cylinder(10,8);

		break;

	case Primitive_Type::CONE:

		Mesh = par_shapes_create_cone(10, 8);

		break;


	case Primitive_Type::DODECA:

		platonicSolid = true;
		Mesh = par_shapes_create_dodecahedron();

		break;

	case Primitive_Type::TETRA:

		platonicSolid = true;
		Mesh = par_shapes_create_tetrahedron();

		break;

	case Primitive_Type::OCTO:

		platonicSolid = true;
		Mesh = par_shapes_create_octahedron();


		break;

	case Primitive_Type::ICOSA:

		platonicSolid = true;
		Mesh = par_shapes_create_icosahedron();

		break;

	case Primitive_Type::BOTTLE:

		Mesh = par_shapes_create_klein_bottle(10,8);

		break;

	}

	//Allocating memory-----------------------------------------------------------------

	num_vertex = Mesh->npoints * 3;
	vertices = new float3[num_vertex];

	num_index = Mesh->ntriangles * 3;
	indices = new uint[num_index];

	num_uv = Mesh->npoints * 2;
	uv_coord = new float[num_uv];

	num_normals = num_vertex;
	normals = new float3[num_vertex];

	//num_normals_faces = Aux->ntriangles;
	//normals_faces = new float3[num_normals_faces];
	//normals_faces_pos = new float3[num_normals_faces];

	//Assigning values

	//vertices-----------------------------------------------------------------

	for (uint i = 0; i < Mesh->npoints; ++i) {

		vertices[i].x = Mesh->points[i * 3];
		vertices[i].y = Mesh->points[(i * 3) + 1];
		vertices[i].z = Mesh->points[(i * 3) + 2];

	}

	//Indices-----------------------------------------------------------------

	for (uint i = 0; i < num_index; ++i)
	{
		indices[i] = Mesh->triangles[i];
	}

	//UVs-----------------------------------------------------------------

	for (uint i = 0; i < num_uv; ++i) {
			if (Mesh->tcoords != nullptr)
			uv_coord[i] = Mesh->tcoords[i];
			else
				uv_coord[i] = 0.0f;
	}


	CalculateDistance();
	//Normals-------------------------------------------------------------

	if (Mesh->normals != nullptr && !platonicSolid) {


		for (int i = 0; i < num_vertex;++i) {

			normals[i].x = Mesh->normals[i*3];
			normals[i].y = Mesh->normals[(i*3)+1];
			normals[i].z = Mesh->normals[(i*3)+2];

		}

	}

	par_shapes_free_mesh(Mesh);

}

//function to triangulate the position of the camera depending on the size of the meshes
void Primitives::CalculateDistance() {

	for (int i = 0; i < num_vertex-2; ++i)
	{
		if (vertices[i].x > maxX)
		{
			maxX = vertices[i].x;
		}
		/*if (vertices[i].x < minX)
		{
			minX = vertices[i].x;
		}*/

		if (vertices[i].y > maxY)
		{
			maxY = vertices[i].y;
		}
		/*if (vertices[i].y < minY)
		{
			minY = ceil(vertices[i].y);
		}*/

		if (vertices[i].z > maxZ)
		{
			maxZ = vertices[i].z;
		}
		/*if (vertices[i].z < minZ)
		{
			minZ = vertices[i].z;
		}*/
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

	App->camera->Reference.z = medZ;

}

void Primitives::DeletePrimitive(Gameobject * ToDelete)
{
	if (ToDelete->meshPointer->Primitives_Vec.size() > 0) {
		for (int i = 0; i < ToDelete->meshPointer->Primitives_Vec.size(); ++i) {
			ToDelete->meshPointer->Primitives_Vec[i]->CleanUp();


			if (ToDelete->meshPointer->Primitives_Vec[i] != nullptr) {
				delete ToDelete->meshPointer->Primitives_Vec[i]; \
					ToDelete->meshPointer->Primitives_Vec[i] = nullptr;
			}

		}

	}
}


par_shapes_mesh* Primitives::CreateCube() {

	//Creating Faces
	par_shapes_mesh* Face_Front = par_shapes_create_plane(1, 1);
	par_shapes_mesh* Face_Top = par_shapes_create_plane(1, 1);
	par_shapes_mesh* Face_Bottom = par_shapes_create_plane(1, 1);
	par_shapes_mesh* Face_Back = par_shapes_create_plane(1, 1);
	par_shapes_mesh* Face_Left = par_shapes_create_plane(1, 1);
	par_shapes_mesh* Face_Right = par_shapes_create_plane(1, 1);


	//Positioning Faces
	par_shapes_translate(Face_Front, -0.5f, -0.5f, 0.5f);

	par_shapes_rotate(Face_Top, -float(PAR_PI*0.5), (float*)&float3(1.0f,0.0f,0.0f));
	par_shapes_translate(Face_Top, -0.5f, 0.5f, 0.5f);

	par_shapes_rotate(Face_Bottom, float(PAR_PI*0.5), (float*)&float3(1.0f, 0.0f, 0.0f));
	par_shapes_translate(Face_Bottom, -0.5f, -0.5f, -0.5f);

	par_shapes_rotate(Face_Back, float(PAR_PI), (float*)&float3(1.0f, 0.0f, 0.0f));
	par_shapes_translate(Face_Back, -0.5f, 0.5f, -0.5f);

	par_shapes_rotate(Face_Left, float(-PAR_PI * 0.5), (float*)&float3(0.0f, 1.0f,0.0f));
	par_shapes_translate(Face_Left, -0.5f, -0.5f, -0.5f);

	par_shapes_rotate(Face_Right, float(PAR_PI*0.5), (float*)&float3(0.0f, 1.0f,0.0f));
	par_shapes_translate(Face_Right, 0.5f, -0.5f, 0.5f);


	//Merging faces
	par_shapes_merge_and_free(Face_Front,Face_Top);
	par_shapes_merge_and_free(Face_Front,Face_Bottom);
	par_shapes_merge_and_free(Face_Front,Face_Back);
	par_shapes_merge_and_free(Face_Front,Face_Left);
	par_shapes_merge_and_free(Face_Front,Face_Right);

	return Face_Front;
}
