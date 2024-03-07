#include "Enemy.h"

Enemy::Enemy()
{
	health = 2;
	radius = 39;
	should_die = false;
	scale_factor = 13;
	forward = 0.5f;
}

float Enemy::GetScale()
{
	if (scale_factor <= 0 || !should_die)
		return scale_factor;

	scale_factor -= 0.2f;
	return scale_factor;
}

float Enemy::GetForward()
{
	return forward;
}

void Enemy::take_damage()
{
	if (health > 0)
		health--;
	else
		should_die = true;
}

void Enemy::SetType(std::string type)
{
	this->type = type;
}

std::string Enemy::GetType()
{
	return type;
}

