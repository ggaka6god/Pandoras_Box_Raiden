#include "Application.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleInput.h"
#include "ModuleAudio_1.h"
#include "ModuleAudio_2.h"
#include "ModuleFadeToBlack.h"
ModuleMap1::ModuleMap1() : Module()
{
	
}
ModuleMap1::~ModuleMap1()
{
   
}

bool ModuleMap1::Init()
{
	xmap = -130;
	ymap = -12100;
	LOG("Loading background assets");
	ground = {xmap,ymap ,352*4 ,3266*4};
    Map1 = App->textures->Load("Tilemap1.png");
	return true;
}

update_status ModuleMap1::Update()
{
	App->render->Blit(Map1, xmap, ymap, &ground);
	if (App->input->keyboard[SDL_SCANCODE_SPACE])
	{
		App->fade->FadeToBlack(this, App->map_2, 2.0f);
		App->audio->Close();
		App->audio_2->Init();
		xmap = -130;
		ymap = -12100;
	}

	return UPDATE_CONTINUE;
}

bool ModuleMap1::CleanUp()
{
	return true;
}