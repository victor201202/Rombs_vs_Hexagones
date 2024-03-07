#pragma once

#include "components/simple_scene.h"
#include "Plant.h"
#include "Enemy.h"

#include <chrono>

typedef struct SelectorBlock
{
    std::string plant_name;
    glm::vec2 pos;
    int resources;

}selector_block_t;

typedef struct GrassBlock
{
    bool render_plant, available;
    std::string plant_name;
    glm::vec2 pos;
    Plant plant;
    int line;
    int column;
}grass_block_t;

typedef struct Collectable
{
    glm::vec2 pos;
    int width, height;

}collectable_t;

typedef struct Projectile2
{
    glm::vec2 pos;
    std::string type;
    bool should_render;
    float forward;
    float radius;
    float rotate;

    bool remove;

    Projectile2()
    {
        should_render = true;
        forward = 0.5f;
        radius = 33;
        remove = false;
        rotate = 360;
    }

    glm::vec2 getPos()
    {
        pos.x += 1.f;
        return pos;
    }

    float getRotate(float deltaTime)
    {
        rotate -= deltaTime * 0.1;
        if (rotate == 0)
            rotate = 360;

        return rotate;
    }

}projectile_t;

typedef struct Line
{
    std::vector<Plant> plants;
    std::vector<Enemy> enemies;
    std::vector<projectile_t> stars;
}line_t;

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderGrass();
        void ComputeHits();
        void ComputePlantCollision();
        void RenderSelector();
        void RenderHud();
        void SpawnEnemy();
        void RenderEnemies();
        void RenderProjectiles(float deltaTime);
        void ComputeAttacks();

    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // TODO(student): If you need any other class variables, define them here.
        float rotate_angle;
        float scale_factor;
        float translate_factor;

        float square_size;
        int health;
        glm::vec2 grass_corner;
        glm::vec2 selector_corner;
        glm::vec2 r_star_corner;
        float star_size;
        glm::vec2 hud_corner;
        int no_resource;
        bool drag_and_drop;
        int drag_resources;
        std::vector<selector_block_t> selector_blocks;
        std::vector<grass_block_t> grass_blocks;
        std::vector<collectable_t> stars;
        int no_stars;
        std::chrono::steady_clock::time_point star_spawn;
        std::chrono::steady_clock::time_point enemy_spawn_time;
        Enemy enemy;
        std::vector<line_t> lines;
    };
}   // namespace m1