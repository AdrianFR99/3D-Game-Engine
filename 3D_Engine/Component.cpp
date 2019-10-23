#include "Component.h"

Component::Component(CompType intype, Gameobject * owner){
	type = intype;
	belongsTo = owner;
}

Component::~Component()
{
}

void Component::Enable()
{
}

void Component::Disable()
{
}

