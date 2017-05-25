#include "Enemy_Grey_Tank.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include <Math.h>
#include "ModuleEnemies.h"
#define PI 3.14159265

Enemy_Grey_Tank::Enemy_Grey_Tank(int x, int y, int path) : Enemy(x, y)
{
	hp = 3;
	points = 130;

	spritesheet = 2;
	animations = 2;
	// Tank animations
	downup.PushBack({ 3, 186, 31, 29 }); // done
	hitdownup.PushBack({ 4, 95, 31, 29 });

	downdiagonalright.PushBack({ 37,	186, 31, 29 }); // done
	hitdowndiagonalright.PushBack({ 38, 95,31,29 });

	neutraldiagonalright.PushBack({ 71, 186,31, 29 }); //in proces
	hitneutraldiagonalright.PushBack({ 72, 95, 31, 29 });

	updiagonalright.PushBack({ 105, 186, 31, 29 }); // Not in usage 
	hitupdiagonalright.PushBack({ 106, 95, 31, 29 });

	leftright.PushBack({ 139 , 186, 31, 29 }); // done
	hitleftright.PushBack({ 140 , 95, 31, 29 });

	downdiagonalleft.PushBack({ 173, 186, 31, 29 }); // done
	hitdowndiagonalleft.PushBack({ 174, 95, 31, 29 });

	neutraldiagonalleft.PushBack({ 207, 186, 31, 29 }); // done
	hitneutraldiagonalleft.PushBack({ 208, 95, 31, 29 });

	updiagonalleft.PushBack({ 241, 186, 31, 29 }); // Not in usage
	hitupdiagonalleft.PushBack({ 242, 95, 31, 29 });

	//Turret animations
	noturret.PushBack({ 1, 1, 1, 1 });

	s.PushBack({ 3, 226, 38, 34 });
	hits.PushBack({ 4, 135, 38, 34 });

	se1.PushBack({ 44, 226, 38, 34 });
	hitse1.PushBack({ 45, 135, 38, 34 });

	se2.PushBack({ 85, 226, 38, 34 });
	hitse2.PushBack({ 86, 135, 38, 34 });

	se3.PushBack({ 126, 226, 38, 34 });
	hitse3.PushBack({ 127, 135, 38, 34 });

	e.PushBack({ 167, 226, 38, 34 });
	hite.PushBack({ 168, 135, 38, 34 });

	ne1.PushBack({ 208, 226, 38, 34 });
	hitne1.PushBack({ 209, 135, 38, 34 });

	ne2.PushBack({ 249, 226, 38, 34 });
	hitne2.PushBack({ 250, 135, 38, 34 });

	ne3.PushBack({ 290, 226, 38, 34 });
	hitne3.PushBack({ 291, 135, 38, 34 });

	n.PushBack({ 331, 226, 38, 34 });
	hitn.PushBack({ 332, 135, 38, 34 });

	nw1.PushBack({ 372, 226, 38, 34 });
	hitnw1.PushBack({ 373, 135, 38, 34 });

	nw2.PushBack({ 413, 226, 38, 34 });
	hitnw2.PushBack({ 414, 135, 38, 34 });

	nw3.PushBack({ 454, 226, 38, 34 });
	hitnw3.PushBack({ 455, 135, 38, 34 });

	w11.PushBack({ 495, 226, 38, 34 });
	hitw11.PushBack({ 496, 135, 38, 34 });

	sw1.PushBack({ 536, 226, 38, 34 });
	hitsw1.PushBack({ 537, 135, 38, 34 });

	sw2.PushBack({ 577, 226, 38, 34 });
	hitsw2.PushBack({ 578, 135, 38, 34 });

	sw3.PushBack({ 618, 226, 38, 34 });
	hitsw3.PushBack({ 619, 135, 38, 34 });


	original_pos.x = x;
	original_pos.y = -100;

	//Paths (there should be more than one path and an integer to select what path to use
	/*Instructions for pathing the enemies:
	0.0, 4.0 = down
	0.0, 0.0 = up
	-0.5, 1.0 = left
	2.0, 1.0 = right
	-0.5, 1.5 = down diagonal left
	0.5, 0.0 = up diagonal right
	-0.5,0.0 = MAS PUTAS DIAGONALES 1
	0.5, 1.0 = MAS PUTAS DIAGONALES 2
	-0.5, 0.0 = up diagonal left
	0.5, 2.0 =  down diagonal right
	1.0, 0.0 = Neutral diagonal up right
	-1.0, 2.0 =Neutral diagonal down left
	-1.0, 0.0 = Neutral diagonal up left
	1.0, 2.0 = Neutral diagonal down right
	*/
	if (path == 0)
	{
		movement.PushBack({ 2.0f, 1.0f }, 300);
		movement.PushBack({ 0.0f, 1.0f }, 1000);
	}

	if (path == 1)
	{
		movement.PushBack({ 0.0f, 4.0f }, 300);
	}

	if (path == 2)
	{
		movement.PushBack({ 2.0f, 1.5f }, 300);
	}

	greytank = true;
	collider = App->collision->AddCollider({ 0, 0, 31 * 3 - 5, 29 * 3 }, COLLIDER_TYPE::COLLIDER_TANK, (Module*)App->enemies);
	animation = &updiagonalleft;
}


void Enemy_Grey_Tank::MoveShoot()
{
	// Calculation between tank and player and movement of the tank

	position = original_pos + movement.GetCurrentPosition();

	position.x += left_right_mod;

	if (sqrtf((distance.y = App->player->position.y - position.y)*(distance.y = App->player->position.y - position.y) + (distance.x = App->player->position.x - position.x)* (distance.x = App->player->position.x - position.x))
		< sqrtf((distance.y = App->player2->position.y - position.y)*(distance.y = App->player2->position.y - position.y) + (distance.x = App->player2->position.x - position.x)* (distance.x = App->player2->position.x - position.x)))
	{
		distance.y = App->player->position.y - position.y;
		distance.x = App->player->position.x - position.x;
	}

	else
	{
		distance.y = App->player2->position.y - position.y;
		distance.x = App->player2->position.x - position.x;
	}

	// Animation of the tank	

	w = 31 * 3;
	h = 29 * 3;


	// Down and up
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f) //Up
	{
		animation = &downup;
		if (ishit == true)
		{
			animation = &hitdownup;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2 - 5;
	}

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 4.0f)// Down
	{
		animation = &downup;
		if (ishit == true)
		{
			animation = &hitdownup;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2 - 5;
	}
	// Left and right
	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f) //Left
	{
		animation = &leftright;
		if (ishit == true)
		{
			animation = &hitleftright;
			ishit = false;
		}
		h = 35 * 3;
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}


	if (movement.steps[movement.GetCurrentStep()].speed.x == 2.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f) //Right
	{
		animation = &leftright;
		if (ishit == true)
		{
			animation = &hitleftright;
			ishit = false;
		}
		h = 35 * 3;
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	//ALERTA CHAPUZA: PARA QUE LOS TANQUES SE PAREN HABR� QUE HACER BOOLS PARA QUE ENTREN EN EL IF DE SU ANIMACI�N SI EST�N PARADOS Y LA ULTIMA ANIMACI�N QUE SE HA HECHO ES ESA. ESTO ES PROVISIONAL Y PACHANGUERO.
	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.0f) //Right
	{
		animation = &leftright;
		if (ishit == true)
		{
			animation = &hitleftright;
			ishit = false;
		}
		h = 35 * 3;
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	// Down diagonal left and up diagonal right
	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 1.5f) // Down diagonal left
	{
		animation = &downdiagonalleft;
		if (ishit == true)
		{
			animation = &hitdowndiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}

	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f) //Up diagonal right
	{
		animation = &downdiagonalleft;
		if (ishit == true)
		{
			animation = &hitdowndiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}


	//MAS PUTAS DIAGONALes
	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f) //MAS PUTAS DIAGONALES 1
	{
		animation = &updiagonalright;
		if (ishit == true)
		{
			animation = &hitdowndiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}

	if (movement.steps[movement.GetCurrentStep()].speed.x == 2.0f && movement.steps[movement.GetCurrentStep()].speed.y == 1.5f) //MAS PUTAS DIAGONALES 2
	{
		animation = &updiagonalright;
		if (ishit == true)
		{
			animation = &hitdowndiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}


	//Down diagonal right and up diagonal left
	if (movement.steps[movement.GetCurrentStep()].speed.x == -0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f) //up diagonal left
	{
		animation = &downdiagonalright;
		if (ishit == true)
		{
			animation = &hitdowndiagonalright;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}


	if (movement.steps[movement.GetCurrentStep()].speed.x == 0.5f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f) //Down diagonal right
	{
		animation = &downdiagonalright;
		if (ishit == true)
		{
			animation = &hitdowndiagonalright;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}

	// Neutral diagonal up right and neutral diagonal down left
	if (movement.steps[movement.GetCurrentStep()].speed.x == 1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f) //neutral diagonal up right
	{
		animation = &neutraldiagonalleft;
		if (ishit == true)
		{
			animation = &hitneutraldiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f) //neutral diagonal down left
	{
		animation = &neutraldiagonalleft;
		if (ishit == true)
		{
			animation = &hitneutraldiagonalleft;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}



	// Neutral diagonal down left and neutral diagonal up right
	if (movement.steps[movement.GetCurrentStep()].speed.x == -1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 0.0f) // Neutral diagonal down left
	{
		animation = &neutraldiagonalright;
		if (ishit == true)
		{
			animation = &hitneutraldiagonalright;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}
	if (movement.steps[movement.GetCurrentStep()].speed.x == 1.0f && movement.steps[movement.GetCurrentStep()].speed.y == 2.0f) //neutral diagonal up right
	{
		animation = &neutraldiagonalright;
		if (ishit == true)
		{
			animation = &hitneutraldiagonalright;
			ishit = false;
		}
		position1.x = position.x + w / 2;
		position1.y = position.y + h / 2;
	}

	if (hp < 2)
	{
		turretalive = false;
		animation1 = &noturret;
	}

	if (turretalive == true)
	{

		//Animation of the turret
		param = (fabs(distance.y) / (fabs(distance.x) + 0.1));
		angle = atan(param) * 180 / PI;

		// South-East position
		if (distance.y > 0 && distance.x > 0)
		{
			se = true;
		}
		else
		{
			se = false;
		}

		// South-West position
		if (distance.y > 0 && distance.x < 0)
		{
			sw = true;
		}
		else
		{
			sw = false;
		}

		// North-East position
		if (distance.y < 0 && distance.x > 0)
		{
			ne = true;
		}
		else
		{
			ne = false;
		}

		// North-West position
		if (distance.y < 0 && distance.x < 0)
		{
			nw = true;
		}
		else
		{
			nw = false;
		}

		// Applying animation

		w1 = 38 * 3;
		h1 = 34 * 3;
		position1.x -= 19 * 3;
		position1.y -= 17 * 3;

		// South to East
		if (se && angle >= 72 && angle <= 90) // Good
		{
			animation1 = &s;
			if (ishit2 == true)
			{
				animation1 = &hits;
				ishit2 = false;
			}
		}
		if (se && angle >= 54 && angle <= 72) //Good
		{
			animation1 = &se1;
			if (ishit2 == true)
			{
				animation1 = &hitse1;
				ishit2 = false;
			}
		}
		if (se && angle >= 36 && angle <= 54) // Good
		{
			animation1 = &se2;
			if (ishit2 == true)
			{
				animation1 = &hitse2;
				ishit2 = false;
			}
		}

		if (se && angle >= 18 && angle <= 36) //Good
		{
			animation1 = &se3;
			if (ishit2 == true)
			{
				animation1 = &hitse3;
				ishit2 = false;
			}
		}

		if (se && angle >= 0 && angle <= 18) // Good
		{
			animation1 = &e;
			if (ishit2 == true)
			{
				animation1 = &hite;
				ishit2 = false;
			}
		}

		// East to North
		if (ne && angle >= 0 && angle <= 18) //Good
		{
			animation1 = &e;
			if (ishit2 == true)
			{
				animation1 = &hite;
				ishit2 = false;
			}
		}
		if (ne && angle >= 18 && angle <= 36) // Good
		{
			animation1 = &ne1;
			if (ishit2 == true)
			{
				animation1 = &hitne1;
				ishit2 = false;
			}
		}
		if (ne && angle >= 36 && angle <= 54) //Good
		{
			animation1 = &ne2;
			if (ishit2 == true)
			{
				animation1 = &hitne2;
				ishit2 = false;
			}
		}
		if (ne && angle >= 54 && angle <= 72) //Good
		{
			animation1 = &ne3;
			if (ishit2 == true)
			{
				animation1 = &hitne3;
				ishit2 = false;
			}
		}
		if (ne && angle >= 72 && angle <= 90) //Good
		{
			animation1 = &n;
			if (ishit2 == true)
			{
				animation1 = &hitn;
				ishit2 = false;
			}
		}

		// North to West
		if (nw && angle >= 72 && angle <= 90) //Good
		{
			animation1 = &n;
			if (ishit2 == true)
			{
				animation1 = &hitn;
				ishit2 = false;
			}
		}
		if (nw && angle >= 54 && angle <= 72) // Good
		{
			animation1 = &nw1;
			if (ishit2 == true)
			{
				animation1 = &hitnw1;
				ishit2 = false;
			}
		}
		if (nw && angle >= 36 && angle <= 54) //Good
		{
			animation1 = &nw2;
			if (ishit2 == true)
			{
				animation1 = &hitnw2;
				ishit2 = false;
			}
		}
		if (nw && angle >= 18 && angle <= 36) //Good
		{
			animation1 = &nw3;
			if (ishit2 == true)
			{
				animation1 = &hitnw3;
				ishit2 = false;
			}
		}
		if (nw && angle >= 0 && angle <= 18) // Good
		{
			animation1 = &w11;
			if (ishit2 == true)
			{
				animation1 = &hitw11;
				ishit2 = false;
			}
		}

		// West to South
		if (sw && angle >= 0 && angle <= 18) //Good
		{
			animation1 = &w11;
			if (ishit2 == true)
			{
				animation1 = &hitw11;
				ishit2 = false;
			}
		}
		if (sw && angle >= 18 && angle <= 36) // Good
		{
			animation1 = &sw1;
			if (ishit2 == true)
			{
				animation1 = &hitsw1;
				ishit2 = false;
			}
		}
		if (sw && angle >= 36 && angle <= 54) //Good
		{
			animation1 = &sw2;
			if (ishit2 == true)
			{
				animation1 = &hitsw2;
				ishit2 = false;
			}
		}

		if (sw && angle >= 54 && angle <= 72) //Good
		{
			animation1 = &sw3;
			if (ishit2 == true)
			{
				animation1 = &hitsw3;
				ishit2 = false;
			}
		}
		if (sw && angle >= 72 && angle <= 90) //Good
		{
			animation1 = &s;
			if (ishit2 == true)
			{
				animation1 = &hits;
				ishit2 = false;
			}
		}



		distance.x = fabs(distance.x);
		distance.y = fabs(distance.y);
		// Shooting
		time_controll++;
		if (time_controll % 100 == 0)

		{

			distance.x *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));
			distance.y *= (10 / sqrtf(distance.x*distance.x + distance.y*distance.y));

			if (sqrtf(distance.x*distance.x + distance.y*distance.y) < 500 && position.y <= 760)
			{
				if (App->player->position.y < (position.y))
				{
					distance.y *= -1;
				}
				if (App->player->position.x < (position.x))
				{
					distance.x *= -1;
				}
				App->particles->AddParticle(App->particles->enemyshot, position.x + w / 2, position.y + h / 2, COLLIDER_ENEMY_SHOT, 0, distance.x, distance.y);
			}
		}
	}
}