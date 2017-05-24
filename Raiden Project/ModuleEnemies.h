#pragma once
#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"


#define MAX_ENEMIES 10000

enum ENEMY_TYPES
{
	NO_TYPE,
    LIGHT_SHOOTER,
	BONUS_SHIP,
	BOSS_MAIN,
	TANK,
	GREY_TANK,
	MEDIUM_SHOOTER,
	KAMIKAZE,
	SHIP_TANK,
	SHIP,
	LONG_MEGATANK,
	MEGATANK,
	BOX_MEDAL,
	BOX_POWERUP,
	LIGHT_KAMIKAZE,
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	int _path;// integer to define which path the enemy follows
	
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	Uint32 time = 0;
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void EraseEnemies();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddEnemy(int path, ENEMY_TYPES type, int x, int y);
	void MoveEnemiesRight(bool); // The bool is used to know if the enemies should be moved to the right (true) or to the left (false)

	

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
	SDL_Texture* sprites2;
	SDL_Texture* sprites3;
	SDL_Texture* sprites4;
	SDL_Texture* sprites5;
	SDL_Texture* sprites6;
	SDL_Texture* sprites7;
	SDL_Texture* sprites8;
	SDL_Texture* sprites9;
	SDL_Texture* sprites10;
	SDL_Texture* sprites11;

	
};

#endif // __ModuleEnemies_H__