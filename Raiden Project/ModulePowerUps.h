#pragma once
#ifndef __ModulePowerUps_H__
#define __ModulePowerUps_H__

#include "Module.h"
#include "ModuleTextures.h"


#define MAX_POWERUPS 50

enum class POWERUP_TYPES
{
	NO_TYPE,
	REDUP,
	BLUEUP,
	MEDAL,
};

class PowerUp;

struct PowerUpInfo
{
	POWERUP_TYPES type = POWERUP_TYPES::NO_TYPE;
	int x, y;
};

class ModulePowerUps : public Module
{
public:

	ModulePowerUps();
	~ModulePowerUps();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void ErasePowerUps();
	bool AddPowerUp(POWERUP_TYPES type, int x, int y);
	void MovePowerUpsRight(bool); // The bool is used to know if the powerups should be moved to the right (true) or to the left (false)

private:

	void SpawnPowerUp(const PowerUpInfo& info);

private:

	PowerUpInfo queue[MAX_POWERUPS];
	PowerUp* powerups[MAX_POWERUPS];
	SDL_Texture* sprites;
};

#endif // __ModulePowerUps_H__