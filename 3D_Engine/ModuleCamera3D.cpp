#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "Maths.h"


ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 5.0f, 10.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;
	
	Move(vec3(10.0f, 0.0f, 0.0f));
	LookAt(vec3(0.0f, 0.0f, 0.0f));
	App->GearConsole.AddLog(" Set 3D camera in position");

	return ret;
}

// Called to init variables
void ModuleCamera3D::Load(nlohmann::json& file)
{
	LOG("Load variables from Json to module Camera3D");
	App->GearConsole.AddLog(" Load Config variables for Camera ");

	premadeDist = file["Modules"]["Camera"]["PremadeDistance"];
	mouse_sensitivity = file["Modules"]["Camera"]["Mouse_sensitivity"];
	wheel_speed = file["Modules"]["Camera"]["Wheel_speed"];
	camera_speed = file["Modules"]["Camera"]["Camera_speed"];


}

// Called to save variables
void ModuleCamera3D::Save(nlohmann::json& file)
{
	LOG("Save variables from Module Camera to Config");
	App->GearConsole.AddLog(" Save variables from Module Camera to Config ");

	file["Modules"]["Camera"]["PremadeDistance"] = premadeDist;
	file["Modules"]["Camera"]["Mouse_sensitivity"] = mouse_sensitivity;
	file["Modules"]["Camera"]["Wheel_speed"] = wheel_speed;
	file["Modules"]["Camera"]["Camera_speed"] = camera_speed;

}


// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	vec3 newPos(0,0,0);
	float cam_speed = camera_speed * dt;

	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		cam_speed = camera_speed * 2 * dt;

	/*if(App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed;
	if(App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos.y -= speed;
*/

	// Mouse motion ----------------

	// while Right click freely look arrpund and be able to move with wasd keys
	if(App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{

		// WASP movement
			if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * cam_speed;
			if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * cam_speed;
			if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * cam_speed;
			if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * cam_speed;

			Position += newPos;
			Reference += newPos;
		// end of wasp move

		// mouse position and free look

		RotateYourself(App->input->GetMouseXMotion(), App->input->GetMouseYMotion());

		
		float Sensitivity = 0.25f;

		Position -= Reference;

		Position = Reference + Z * length(Position);
	}

	//mouse wheel

	newPos -= Z * App->input->GetMouseZ()*wheel_speed;
	Position += newPos;

	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {

		//rotate around the object
		Orbit(vec3(0, 0, 0), App->input->GetMouseXMotion(), App->input->GetMouseYMotion());

		
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_UP)
	{
		Reference= vec3(0, 0, 0);
		Position = Reference + Z * premadeDist;
	}

	// Recalculate matrix -------------
	CalculateViewMatrix();



	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{

	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f,
		X.y, Y.y, Z.y, 0.0f,
		X.z, Y.z, Z.z, 0.0f,
		-dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}

// Called for rotating in a point
void ModuleCamera3D::Rotate(const const vec3 &ReferencetoRot)
{
	Reference = ReferencetoRot;

	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();

}

//similar to rotate, to orbit
void ModuleCamera3D::Orbit(const vec3& orbit_center, const float& motion_x, const float& motion_y)
{
	Reference = orbit_center;

	int dx = -motion_x;
	int dy = -motion_y;

	Position -= Reference;

	if (dx != 0)
	{
		float DeltaX = (float)dx;

		// Rotate arround the y axis
		X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
	}

	if (dy != 0)
	{
		float DeltaY = (float)dy;

		// Rotate arround the X direction
		Y = rotate(Y, DeltaY, X);
		Z = rotate(Z, DeltaY, X);
	}

	Position = Reference + Z * length(Position);
}

void ModuleCamera3D::RotateYourself(const float& motion_x, const float& motion_y)
{
	Reference = Position;

	int dx = -motion_x;
	int dy = -motion_y;

	Position -= Reference;

	if (dx != 0)
	{
		float DeltaX = (float)dx * mouse_sensitivity;

		X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
	}

	if (dy != 0)
	{
		float DeltaY = (float)dy * mouse_sensitivity;

		Y = rotate(Y, DeltaY, X);
		Z = rotate(Z, DeltaY, X);
	}

	Position = Reference + Z * length(Position);
}
