#ifndef __DEBUGDRAW_H__
#define __DEBUGDRAW_H__

#include "Color.h"

#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"

#include "MathGeoLib/include/MathGeoLib.h"
#include "MathGeoLib/include/MathBuildConfig.h"



class DebugDraw
{
public:
	DebugDraw();
	~DebugDraw();


public:

	//draw
	void DebugDrawBox(const float3* corners, Color color, const float& linesWidth);
	void DebugDrawFrustum(const Frustum*frustum,Color color, const float& linesWidth);


	//aux
	void AssignCornersCube(const float3*corners);
};

#endif //__DEBUGDRAW_H__