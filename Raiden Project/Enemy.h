#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Path.h"
struct SDL_Texture;
struct Collider;

class Enemy : public Path
{
protected:
	Animation* animation = nullptr;
	Animation* animation1 = nullptr;
	Animation* animation2 = nullptr;
	Animation* animation3 = nullptr;
	Collider* collider = nullptr;

public:
	iPoint position;
	iPoint position1;
	iPoint position2;
	iPoint position3;
	bool ishit;
	fPoint distance;
	iPoint distance1;
	iPoint distance2;
	int hp;
	Uint32 bombhittime; //time between allowed bomb hits
	bool allowbombtime = true; //allows timer
	bool bombimmunity = false;
	int hitbybomb = 0;
	uint points;
	int h;
	int w;
	int h1;
	int w1;
	int h2;
	int w2;
	int h3;
	int w3;
	int spritesheet;
	int animations; // How much animations does the enemy have
	bool bonusplane = false; // Bollean to detect if the enemy is a bonus plane and adapt the hitbox and drop a powerup
	bool medalbox = false; //Boolean to detect if the enemy rewards a medal when killed
	bool powerupbox = false;
	bool lightshooter = false;
	bool mediumshooter = false; // Bollean to detect if the enemy is a medium plane and adapt the hitbox
	int left_right_mod = 0; // Integer to modify the position of the enemy
	bool tank = false; //Boolean to detect if the enemy is  a tank

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void MoveShoot() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider); 
};

#endif // __ENEMY_H__