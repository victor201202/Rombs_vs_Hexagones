#include "Plant.h"
#include <chrono>

Plant::Plant()
{
    scale_factor = 10;
    should_die = false;
    type = "none";
    spawn_time = std::chrono::high_resolution_clock::now();
    radius = 16;
}

float Plant::GetRadius()
{
    return radius;
}

float Plant::GetScale()
{
    if (scale_factor <= 0 || !should_die)
        return scale_factor;

    scale_factor -= 0.2f;
    return scale_factor;
}

void Plant::SetDeath(bool shoul_die)
{
    this->should_die = shoul_die;
}

bool Plant::GetDeath()
{
    return should_die;
}

void Plant::SetType(std::string type)
{
    this->type = type;
}

std::string Plant::GetType()
{
    return type;
}

void Plant::SetPos(glm::vec2 pos)
{
    this->projectile_pos = pos;
}

glm::vec2 Plant::GetPos()
{
    return projectile_pos;
}

void Plant::SetTime(std::chrono::steady_clock::time_point time)
{
    this->spawn_time = time;
}

std::chrono::steady_clock::time_point Plant::GetTime()
{
    return spawn_time;
}

void Plant::SetIndex(int index)
{
    this->grass_index = index;
}

int Plant::GetIndex()
{
    return grass_index;
}