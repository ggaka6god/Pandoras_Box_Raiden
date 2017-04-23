#include "Enemy.h"
#pragma once
class Enemy_Bonus_Ship : public Enemy
{
private:
	Animation flydown;
	Animation flysides;
	Animation stop;
	Animation propeller;
	Animation none;
	Animation charge;
	iPoint original_pos;
	iPoint original_pos1;
	iPoint original_pos2;
	Path movement;
	bool side = false;
	bool movingsidetoside = false;
	bool shooting = false;
	int shoot_time = 0;
public:
	Enemy_Bonus_Ship(int x, int y, int path);
	void MoveShoot();
};

