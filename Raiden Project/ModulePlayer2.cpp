#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModuleMap1.h"
#include "ModuleMap2.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;

	InitialPos();

	// Idle animation
	idle.PushBack({ 3, 2, 22, 28 });

	// Idle animation 2
	idlep.PushBack({ 28, 2, 22, 29 });

	// Move right

	right.PushBack({ 53, 2, 19, 28 });
	right1.PushBack({ 97, 2, 14, 28 });

	// Move right 2

	rightp.PushBack({ 75, 2, 19, 29 });
	right1p.PushBack({ 114, 2, 14, 29 });

	// Move left

	left.PushBack({ 131, 2, 19, 28 });
	left1.PushBack({ 175, 2, 14, 28 });

	// Move left 2

	leftp.PushBack({ 153, 2, 19, 29 });
	left1p.PushBack({ 192, 2, 14, 29 });
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Init()
{
	LOG("Loading player");

	graphics = App->textures->Load("Assets/Player2.png");
	Player = App->collision->AddCollider({ 0, 0, player_w, player_h }, COLLIDER_PLAYER, this);
	Player->SetPos(82938, 2323);
	return true;
}


// Unload assets
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	if (allowtimep == true)
	{
		timep = SDL_GetTicks();
		allowtimep = false;
	}

	if (SDL_GetTicks() >= (timep + 10))
	{
		if (propeller == true)
		{
			propeller = false;
			allowtimep = true;
		}

		else if (propeller == false)
		{
			propeller = true;
			allowtimep = true;
		}
	}

	int speed = 10;

	if (propeller)
	{
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
		{
			if (allowtime == true)
			{
				time = SDL_GetTicks();
				allowtime = false;
			}

			if (current_animation != &left)
			{
				left.Reset();
				current_animation = &left;
			}

			if (current_animation != &left1 && SDL_GetTicks() >= (time + 300))
			{
				left1.Reset();
				current_animation = &left1;
			}

			if (App->map_1->IsEnabled() && position.x >= 20)
			{
				position.x -= speed;
			}

			if (App->map_2->IsEnabled() && position.x >= 20)
			{
				position.x -= speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
		{
			if (allowtime == true)
			{
				time = SDL_GetTicks();
				allowtime = false;
			}

			if (current_animation != &right)
			{
				right.Reset();
				current_animation = &right;
			}

			if (current_animation != &right1 && SDL_GetTicks() >= (time + 300))
			{
				right1.Reset();
				current_animation = &right1;
			}

			if (App->map_1->IsEnabled() && position.x <= 600)
			{
				position.x += speed;
			}

			if (App->map_2->IsEnabled() && position.x <= 600)
			{
				position.x += speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
		{
			position.y += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speed;

		}

		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_UP)
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &left)
			{
				left.Reset();
				current_animation = &left;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_UP)
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &right)
			{
				right.Reset();
				current_animation = &right;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_DOWN]
			&& App->input->keyboard[SDL_SCANCODE_UP])
		{
			current_animation = &idle;
		}
		if (App->input->keyboard[SDL_SCANCODE_RIGHT]
			&& App->input->keyboard[SDL_SCANCODE_LEFT])
		{
			current_animation = &idle;
		}

		if (
			App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE)
		{
			if (SDL_GetTicks() >= time + 100)
			{
				current_animation = &idle;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->laser, position.x + speed + 20, position.y, COLLIDER_PLAYER_SHOT);
		}

		// Draw everything --------------------------------------
		if (current_animation == &idle)
		{
			player_w = 22 * 3;
			player_h = 28 * 3;
		}
		else if (current_animation == &left || current_animation == &right)
		{
			player_w = 19 * 3;
			player_h = 28 * 3;
		}
		else if (current_animation == &left1 || current_animation == &right1)
		{
			player_w = 14 * 3;
			player_h = 28 * 3;
		}
	}

	else
	{
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
		{
			if (allowtime == true)
			{
				time = SDL_GetTicks();
				allowtime = false;
			}

			if (current_animation != &leftp)
			{
				leftp.Reset();
				current_animation = &leftp;
			}

			if (current_animation != &left1p && SDL_GetTicks() >= (time + 300))
			{
				left1p.Reset();
				current_animation = &left1p;
			}

			if (App->map_1->IsEnabled() && position.x >= 20)
			{
				position.x -= speed;
			}

			if (App->map_2->IsEnabled() && position.x >= 20)
			{
				position.x -= speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
		{
			if (allowtime == true)
			{
				time = SDL_GetTicks();
				allowtime = false;
			}

			if (current_animation != &rightp)
			{
				rightp.Reset();
				current_animation = &rightp;
			}

			if (current_animation != &right1p && SDL_GetTicks() >= (time + 300))
			{
				right1p.Reset();
				current_animation = &right1p;
			}

			if (App->map_1->IsEnabled() && position.x <= 600)
			{
				position.x += speed;
			}

			if (App->map_2->IsEnabled() && position.x <= 600)
			{
				position.x += speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
		{
			position.y += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speed;

		}

		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_UP)
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &leftp)
			{
				leftp.Reset();
				current_animation = &leftp;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_UP)
		{
			allowtime = true;
			time = SDL_GetTicks();
			if (current_animation != &rightp)
			{
				rightp.Reset();
				current_animation = &rightp;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_DOWN]
			&& App->input->keyboard[SDL_SCANCODE_UP])
		{
			current_animation = &idlep;
		}
		if (App->input->keyboard[SDL_SCANCODE_RIGHT]
			&& App->input->keyboard[SDL_SCANCODE_LEFT])
		{
			current_animation = &idlep;
		}

		if (
			App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE)
		{
			if (SDL_GetTicks() >= time + 100)
			{
				current_animation = &idlep;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->laser, position.x + speed + 20, position.y, COLLIDER_PLAYER_SHOT);
		}

		// Draw everything --------------------------------------
		if (current_animation == &idlep)
		{
			player_w = 22 * 3;
			player_h = 29 * 3;
		}
		else if (current_animation == &leftp || current_animation == &rightp)
		{
			player_w = 19 * 3;
			player_h = 29 * 3;
		}
		else if (current_animation == &left1p || current_animation == &right1p)
		{
			player_w = 14 * 3;
			player_h = 29 * 3;
		}
	}


	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), player_w, player_h);
	if (godmode == false && Player != nullptr)
	{
		Player->SetPos(position.x, position.y);
		Player->SetSize(player_w, player_h);
	}


	// Godmode
	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		if (godmode)
		{
			Player = App->collision->AddCollider({ 0, 0, player_w, player_h }, COLLIDER_PLAYER, this);

			godmode = false;
		}
		else if (Player != nullptr)
		{
			Player->SetPos(10000000, 10000000);
			Player = nullptr;
			godmode = true;
		}
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	if (Player != nullptr && Player == c1 && deadplayer == false)
	{
		Disable();
		Player->SetPos(10000000, 10000000);
		deadplayer = true;
	}
	
	if (Player != nullptr && Player == c1 && App->player->deadplayer && deadplayer)
	{
		godmode = true;
		App->enemies->Disable();
		App->collision->Disable();
		App->fade->FadeToBlack((Module*)App->map_1, (Module*)App->WelcomeScreen);
		App->player->deadplayer = false;
		deadplayer = false;
	}
}