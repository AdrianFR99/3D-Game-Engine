#include "Gameobject.h"


Gameobject::Gameobject(int id)
{
	ID = id;
}

Gameobject::~Gameobject()
{

}

void Gameobject::Update()
{
	//nothing
}

void Gameobject::Enable()
{
	active = true;
}

void Gameobject::Disable()
{
	active = false;
}

void Gameobject::Cleanup()
{
	//pointers must be set to null ptr;
}
