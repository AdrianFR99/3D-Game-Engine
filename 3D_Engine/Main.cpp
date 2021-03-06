#include <stdlib.h>
#include "Application.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#include "Brofiler/Brofiler.h"
#pragma comment(lib, "Brofiler/ProfilerCore32.lib")


enum main_states
{

	MAIN_CREATION,
	MAIN_AWAKE,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = NULL;

int main(int argc, char ** argv)
{
	
	

	LOG("Starting Engine '%s'...", TITLE);
	

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	


	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG("-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_AWAKE;

			App->GearConsole.AddLog(" Gear Engine: ON  ");

			App->GearConsole.AddLog(" Brofiler integrated succesfully in main ");
			break;

		case MAIN_AWAKE :

			LOG("-------------- Application awake --------------");
			if (App->Awake() == false)
			{
				LOG("Application AWAKE exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_START;
				LOG("-------------- Application AWAKE --------------");
			}
		
			break;

		case MAIN_START:

			LOG("-------------- Application Init --------------");
			if (App->Init() == false)
			{
				LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			BROFILER_FRAME("MAIN update");

			BROFILER_CATEGORY("Update", Profiler::Color::AntiqueWhite);

			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	
	delete App;
	LOG("Exiting game '%s'...\n", TITLE);
	return main_return;
}