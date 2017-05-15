#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleShadows.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleStageClear1.h"

ModuleShadows::ModuleShadows()
{
	for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
		active[i] = nullptr;
}

ModuleShadows::~ModuleShadows()
{}

// Load assets
bool ModuleShadows::Init()
{
	LOG("Loading shadows");

	return true;
}

// Unload assets
bool ModuleShadows::CleanUp()
{
	LOG("Unloading shadows");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleShadows::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
	{
		Shadow* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
			continue;
		}

		if (regulator % 2 == 1)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), p->size.x, p->size.y);
		}

		regulator++;
	}

	return UPDATE_CONTINUE;
}


void ModuleShadows::AddShadow(const Shadow& shadow, float x, float y, float distancex, float distancey)
{
	for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
	{
		if (active[i] == nullptr)
		{
			Shadow* p = new Shadow(shadow);
			p->born = 0;
			p->position.x = x;
			p->position.y = y;
			p->distance.x = distancex;
			p->distance.y = distancey;
			p->size = shadow.size;

			active[i] = p;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

void ModuleShadows::MoveShadowsRight(bool right)
{
	if (right == true)
	{
		for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
		{
			if (active[i] != nullptr)
			{
				active[i]->position.x += App->map_1->xscrollspeed;
			}
		}
	}

	if (right == false)
	{
		for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
		{
			if (active[i] != nullptr)
			{
				active[i]->position.x -= App->map_1->xscrollspeed;
			}
		}
	}
}
void ModuleShadows::EraseShadows()
{
	for (uint i = 0; i < MAX_ACTIVE_SHADOWS; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

}

Shadow::Shadow()
{
	position.SetToZero();
}

Shadow::Shadow(const Shadow& p) :
	anim(p.anim), position(p.position), born(p.born)
{}

Shadow::~Shadow()
{}

bool Shadow::Update()
{

	bool ret = true;

	if (anim.Finished())
		ret = false;

	return ret;
}
