#pragma once
#include "Enemy.h"

class Box_Medal : public Enemy
{
private:
	Animation idle;

	fPoint original_pos;
	fPoint distance;
	Path movement;

public:
	Box_Medal(int x, int y, int path);
	void MoveShoot();
};

