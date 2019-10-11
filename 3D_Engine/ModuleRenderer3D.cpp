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
	//	glCullFace(GL_FRONT_AND_BACK);
		
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return ret;
}



bool ModuleRenderer3D::Start() {


	//GLubyte indices[36]={

	//	0,1,2, 2,3,0,
	//	0,3,4, 3,7,4,
	//	3,2,7, 2,6,7,
	//	6,4,7, 4,6,5,
	//	1,0,4, 5,1,4,
	//	1,5,2, 2,5,6,
	//};

	//
	//float vertices[24] = {

	//	0.f,1.f,0.f,//0
	//	0.f,0.f,0.f,//1
	//	0.f,0.f,1.f,//2
	//	0.f, 1.f, 1.f,//3
	//	1.f,1.f,0.f,//4
	//	1.f,0.f,0.f,//5
	//	1.f,0.f,1.f,//6
	//	1.f, 1.f, 1.f,//7
	//};



	/*
	glGenBuffers(1, (GLuint*) &(ID_Vertices));
	glBindBuffer(GL_ARRAY_BUFFER,ID_Vertices);
	glBufferData(GL_ARRAY_BUFFER,sizeof(uint)*num_Vertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);


	glGenBuffers(1, (GLuint*) &(ID_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*num_indices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);*/


	
	return true;

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
	

	glBegin(GL_LINES);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

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
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnd();
	
	glLineWidth(1.0f);







	


	



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

void ModuleRenderer3D::changeLight(bool value)
{
	if (value)
	{
		lights[0].Active(true);
	}
	else
	{
		lights[0].Active(false);
	}
}
