#include "Gameobject.h"

void Gameobject::Update()
{

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
