#include "DebugDraw.h"


DebugDraw::DebugDraw()
{
}


DebugDraw::~DebugDraw()
{
}

  
void DebugDraw::DebugDrawBox(const float3* corners, Color color, bool lines, const float& linesWidth)
{
	GLint previous[2];
	if (lines)
	{
		glGetIntegerv(GL_POLYGON_MODE, previous);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	glColor3f(color.r, color.g, color.b);

	glLineWidth(linesWidth);

	glBegin(GL_QUADS);

	AssignCornersCube(corners);

	glEnd();

	if (lines)
		glPolygonMode(GL_FRONT_AND_BACK, previous[0]);

	glLineWidth(1.0f);

	glColor3f(255, 255, 255);
}

void DebugDraw::DebugDrawFrustum(const Frustum*frustum, Color color, bool lines, const float& linesWidth) {

	float3 Corners[8];
	frustum->GetCornerPoints(Corners);

	DebugDrawBox(Corners,color,lines,linesWidth);


}


void DebugDraw::AssignCornersCube(const float3*corners) {

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