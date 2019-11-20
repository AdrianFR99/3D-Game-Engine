#include "DebugDraw.h"




  
void DebugDrawBox(const float3* corners, Color color, const float& linesWidth)
{
	GLint mode[2];

	
	glGetIntegerv(GL_POLYGON_MODE, mode);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	

	glColor3f(color.r, color.g, color.b);
	glLineWidth(linesWidth);
	glBegin(GL_QUADS);

	AssignCornersCube(corners);


	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK,mode[0]);
	glLineWidth(1.0f);
	glColor3f(255, 255, 255);
}

void DebugDrawFrustum(const Frustum*frustum, Color color, const float& linesWidth) {

	float3 Corners[8];
	frustum->GetCornerPoints(Corners);

	DebugDrawBox(Corners,color,linesWidth);


}


void AssignCornersCube(const float3*corners) {

	glVertex3fv((GLfloat*)&corners[1]); //VertexPos(-sx, -sy, sz);
	glVertex3fv((GLfloat*)&corners[5]); //VertexPos( sx, -sy, sz);
	glVertex3fv((GLfloat*)&corners[7]); //VertexPos( sx,  sy, sz);
	glVertex3fv((GLfloat*)&corners[3]); //VertexPos(-sx,  sy, sz);
											
	glVertex3fv((GLfloat*)&corners[4]); //VertexPos( sx, -sy, -sz);
	glVertex3fv((GLfloat*)&corners[0]); //VertexPos(-sx, -sy, -sz);
	glVertex3fv((GLfloat*)&corners[2]); //VertexPos(-sx,  sy, -sz);
	glVertex3fv((GLfloat*)&corners[6]); //VertexPos( sx,  sy, -sz);
												
	glVertex3fv((GLfloat*)&corners[5]); //VertexPos(sx, -sy,  sz);
	glVertex3fv((GLfloat*)&corners[4]); //VertexPos(sx, -sy, -sz);
	glVertex3fv((GLfloat*)&corners[6]); //VertexPos(sx,  sy, -sz);
	glVertex3fv((GLfloat*)&corners[7]); //VertexPos(sx,  sy,  sz);
												
	glVertex3fv((GLfloat*)&corners[0]); //VertexPos(-sx, -sy, -sz);
	glVertex3fv((GLfloat*)&corners[1]); //VertexPos(-sx, -sy,  sz);
	glVertex3fv((GLfloat*)&corners[3]); //VertexPos(-sx,  sy,  sz);
	glVertex3fv((GLfloat*)&corners[2]); //VertexPos(-sx,  sy, -sz);
												
	glVertex3fv((GLfloat*)&corners[3]); //VertexPos(-sx, sy,  sz);
	glVertex3fv((GLfloat*)&corners[7]); //VertexPos( sx, sy,  sz);
	glVertex3fv((GLfloat*)&corners[6]); //VertexPos( sx, sy, -sz);
	glVertex3fv((GLfloat*)&corners[2]); //VertexPos(-sx, sy, -sz);

	glVertex3fv((GLfloat*)&corners[0]); //VertexPos(-sx, -sy, -sz);
	glVertex3fv((GLfloat*)&corners[4]); //VertexPos( sx, -sy, -sz);
	glVertex3fv((GLfloat*)&corners[5]); //VertexPos( sx, -sy,  sz);
	glVertex3fv((GLfloat*)&corners[1]); //VertexPos(-sx, -sy,  sz);

}