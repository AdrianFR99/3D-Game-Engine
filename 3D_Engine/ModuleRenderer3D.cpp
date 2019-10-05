#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"



#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include "imgui/imgui.h"

//#include <gl/GL.h>
//#include <gl/GLU.h>


#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment(lib, "glew/libx86/glew32.lib")

ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());


		// Initialize glew
		GLenum error = glewInit();

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		 error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	
//Lines Immediated mode--------------------------------------------

	glBegin(GL_LINES);

	for (float x = 0.0; x<100; x ++)
	{
		glVertex3f(x, 0.0f, 0.0f);
		glVertex3f(x, 0.0f, 100.0f);
	}
	for (float y = 0.0; y < 100; y++)
	{
		glVertex3f(0.0, 0.0f, y);
		glVertex3f(100.0f, 0.0f, y);

	}

	glEnd();
	
	glLineWidth(1.0f);

//---------------------------------------------------------------------


//Triangles Immediated mode---------------------------------------------

	//glBegin(GL_TRIANGLES);

	//glVertex3f(4, 4, 0.0);
	//glVertex3f(-4, 4, 0.0);
	//glVertex3f(-4, -4, 0.0);


	//glEnd();

//--------------------------------------------------------------------

//Quads Immediated mode-----------------------------------------------

//glBegin(GL_QUADS);
//
//  glVertex3f(4,4,0.0);//top left
//	glVertex3f(-4,4,0.0);//top right
//	glVertex3f(-4,-4,0.0);//bottom right
//	glVertex3f(4,-4,0.0);//bottom left
//
//glEnd();

//--------------------------------------------------------------------


//cube Immediated mode-----------------------------------------------

//glBegin(GL_TRIANGLES);
//
////front face
//
//glVertex3f(-4.0, 4.0, 4.0);//top left
//glVertex3f(-4.0, 4.0, -4.0);//top right
//glVertex3f(-4.0, -4.0, -4.0);//bottom left
//
//glVertex3f(-4.0, -4.0, -4.0);//bottom left
//glVertex3f(-4.0, -4.0, 4.0);//bottom right
//glVertex3f(-4.0, 4.0, 4.0);//top left
//
//
////Left face
//
//glVertex3f(-4.0, 4.0, -4.0);//top left
//glVertex3f(4.0, 4.0, -4.0);//top right
//glVertex3f(4.0, -4.0, -4.0);//bottom left
//
//glVertex3f(4.0, -4.0, -4.0);//bottom left
//glVertex3f(-4.0, -4.0, -4.0);//bottom right
//glVertex3f(-4.0, 4.0, -4.0);//top left
//
////back face
//
//glVertex3f(4.0, 4.0, -4.0);//top left
//glVertex3f(4.0, 4.0, 4.0);//top right
//glVertex3f(4.0, -4.0, 4.0);//bottom left
//
//glVertex3f(4.0, -4.0, 4.0);//bottom left
//glVertex3f(4.0, -4.0, -4.0);//bottom right
//glVertex3f(4.0, 4.0, -4.0);//top left
//
//
////right face
//
//glVertex3f(4.0, -4.0, 4.0);//top left
//glVertex3f(4.0, 4.0, 4.0);//top right
//glVertex3f(-4.0, 4.0, 4.0);//bottom left
//
//glVertex3f(-4.0, -4.0, 4.0);//bottom left
//glVertex3f(4.0, -4.0, 4.0);//bottom right
//glVertex3f(-4.0, 4.0, 4.0);//top left
//
////up face
//
////glVertex3f(-4.0, 4.0, -4.0);//bottom left
////glVertex3f(4.0, 4.0, 4.0);//top right
////glVertex3f(4.0, 4.0, -4.0);//top left
//
//
////glVertex3f();
////glVertex3f();
////glVertex3f();
//
////down face
//
////glVertex3f();
////glVertex3f();
////glVertex3f();
//
////glVertex3f();
////glVertex3f();
////glVertex3f();
//
//
//
//glEnd();

//--------------------------------------------------------------------



//Drawing a quad with array vertices (with out creating buffers)----------


	//float vertices[]{

	//	4,4,0.0, //top left
	//	-4,4,0.0,//top right
	//	-4,-4,0.0,//bottom right
	//	4,-4,0.0 //bottom left
	//};

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3,GL_FLOAT,0,vertices);
	//glDrawArrays(GL_QUADS,0,4);

	//glDisableClientState(GL_VERTEX_ARRAY);

	
//-------------------------------------------
	

//buffers example-----------------------------------------------------------


	float vertices[]{

		4,4,0.0, //top left
		-4,4,0.0,//top right
		-4,-4,0.0,//bottom right
		4,-4,0.0 //bottom left
	};

unsigned int VBO=0;

glGenBuffers(1,(GLuint*)&VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  //GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
																			//GL_DYNAMIC_DRAW: the data is likely to change a lot.
																			//GL_STREAM_DRAW : the data will change every time it is drawn.
glEnableClientState(GL_VERTEX_ARRAY);

glVertexPointer(3,GL_FLOAT,0,NULL);
glDrawArrays(GL_QUADS,0,4);

glDisableClientState(GL_VERTEX_ARRAY);



//delete [] vertices;   //create a GLfloat vertices=new GLfloat[sizeX] and then delete it
//
glDeleteBuffers(1, &VBO); //i don't know if it's ok delet it here

//------------------------------------------------------------------------


	//WireFrame
	/*glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);*/

	//Filled
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	App->UI_Layer->Draw();
	SDL_GL_SwapWindow(App->window->window);



	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
