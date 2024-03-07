#pragma once
#include "transform2D.h"
#include "object2D.h"
#include <chrono>

class Plant
{
public:
	float GetScale();
	void SetDeath(bool should_die);
	bool GetDeath();
	void SetType(std::string type);
	std::string GetType();
	void SetPos(glm::vec2 pos);
	glm::vec2 GetPos();
	void SetTime(std::chrono::steady_clock::time_point time);
	std::chrono::steady_clock::time_point GetTime();
	float GetRadius();
	int GetIndex();
	void SetIndex(int index);
	Plant();
private:
	float radius;
	bool should_die;
	float scale_factor;
	int grass_index;
	std::string type;
	glm::vec2 projectile_pos;
	std::chrono::steady_clock::time_point spawn_time;
};

