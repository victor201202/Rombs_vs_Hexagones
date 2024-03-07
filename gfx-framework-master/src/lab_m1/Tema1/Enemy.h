#pragma once

#include "components/simple_scene.h"

class Enemy
{
private:
	int health;
	float scale_factor;
	float forward;
	std::string type;
public:
	bool should_die;
	glm::vec2 pos;
	float radius;
	Enemy();
	void take_damage();
	float GetScale();
	float GetForward();
	void SetType(std::string type);
	std::string GetType();
};

