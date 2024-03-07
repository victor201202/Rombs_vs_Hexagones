#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "transform2D.h"
#include "object2D.h"

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    srand(time(NULL));
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    square_size = 100;
    rotate_angle = -180.f;
    scale_factor = 1.f;
    translate_factor = 1.f;
    health = 3;
    no_stars = 3;
    star_spawn = std::chrono::high_resolution_clock::now();
    enemy_spawn_time = std::chrono::high_resolution_clock::now();
    grass_corner = { 90, 60 };
    //540, 590
    selector_corner = { 40, 590 };
    r_star_corner = { 18.88f, 10.16f };
    star_size = 7;
    hud_corner = { 700, 590 };
    no_resource = 9;
    drag_and_drop = false;
    lines.reserve(3);
    lines.resize(3);
    for (int i = 0; i < lines.size(); i++)
    {
        lines[i].plants.reserve(3);
        lines[i].plants.resize(3);
    }
    selector_blocks.resize(4);
    selector_blocks.reserve(4);
    for (int i = 0; i < selector_blocks.size(); i++)
    {
        selector_blocks[i].pos = glm::vec2(0.f, 0.f);
        selector_blocks[i].resources = 0;
    }

    grass_blocks.resize(9);
    grass_blocks.reserve(9);

    for (int i = 0; i < grass_blocks.size(); i++)
    {
        grass_blocks[i].pos = glm::vec2(0.f, 0.f);
        grass_blocks[i].available = true;
    }

    translateX = 0;
    translateY = 0;

    scaleX = 1;
    scaleY = 1;

    angularStep = 0;

    Mesh* square1 = object2D::CreateSquare("square1", corner, square_size, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, square_size, glm::vec3(0, 0, 0), false);
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, square_size, glm::vec3(1, 0, 0), true);
    AddMeshToList(square3);

    Mesh* rectangle1 = object2D::CreateRectangle("rectangle1", corner, 50, 340, glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle1);

    Mesh* rectangle2 = object2D::CreateRectangle("rectangle2", corner, 1280, 720, glm::vec3(105.f/255.f, 105.f / 255.f, 105.f / 255.f), true, -10);
    AddMeshToList(rectangle2);

    Mesh* resource_star = object2D::CreateFilledStar("r_star", corner, glm::vec3(192.f/255.f, 192.f/255.f, 192.f/255.f));
    AddMeshToList(resource_star);

    Mesh* collectable_star = object2D::CreateFilledStar("c_star", corner, glm::vec3(255.f / 255.f, 20.f / 255.f,147.f / 255.f), 4);
    AddMeshToList(collectable_star);

    Mesh* projectile1 = object2D::CreateFilledStar2("projectile1", corner, glm::vec3(255.f / 255.f, 69 / 255.f, 0.f / 255.f), 4);
    AddMeshToList(projectile1);

    Mesh* projectile2 = object2D::CreateFilledStar2("projectile2", corner, glm::vec3(0, 0, 1), 4);
    AddMeshToList(projectile2);

    Mesh* projectile3 = object2D::CreateFilledStar2("projectile3", corner, glm::vec3(1, 1, 0), 4);
    AddMeshToList(projectile3);

    Mesh* projectile4 = object2D::CreateFilledStar2("projectile4", corner, glm::vec3(0.5, 0, 1), 4);
    AddMeshToList(projectile4);

    Mesh* plant1 = object2D::CreatePlant("plant1", corner, glm::vec3(255.f / 255.f, 69 / 255.f, 0.f / 255.f));
    AddMeshToList(plant1);

    Mesh* plant2 = object2D::CreatePlant("plant2", corner, glm::vec3(0, 0, 1));
    AddMeshToList(plant2);

    Mesh* plant3 = object2D::CreatePlant("plant3", corner, glm::vec3(1, 1, 0));
    AddMeshToList(plant3);

    Mesh* plant4 = object2D::CreatePlant("plant4", corner, glm::vec3(0.5, 0, 1));
    AddMeshToList(plant4);

    Mesh* enemy1 = object2D::CreateEnemy("enemy1", corner, glm::vec3(255.f / 255.f, 69 / 255.f, 0.f / 255.f), 10);
    AddMeshToList(enemy1);

    Mesh* enemy2 = object2D::CreateEnemy("enemy2", corner, glm::vec3(0, 0, 1), 10);
    AddMeshToList(enemy2);

    Mesh* enemy3 = object2D::CreateEnemy("enemy3", corner, glm::vec3(1, 1, 0), 10);
    AddMeshToList(enemy3);

    Mesh* enemy4 = object2D::CreateEnemy("enemy4", corner, glm::vec3(0.5, 0, 1), 10);
    AddMeshToList(enemy4);
}

std::string drag_plant;

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::SpawnEnemy()
{
    static float spawn_delay = 3 + rand() % 7;
    auto time_now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(time_now - enemy_spawn_time);

    if (duration.count() >= spawn_delay)
    {
        int line = 0 + rand() % 3;
        Enemy enemy;
        enemy.pos = { 1280, grass_corner.y + square_size * line + 20 * line + square_size / 2 };
        int type = 1 + rand() % 4;
        enemy.SetType(std::to_string(type));
        lines[line].enemies.push_back(enemy);
        enemy_spawn_time = std::chrono::high_resolution_clock::now();
        spawn_delay = 3 + rand() % 7;
    }
}

void Tema1::ComputeAttacks()
{
    static bool skip_plant = false;
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].plants.size(); j++)
        {
            if (lines[i].plants[j].GetType() != "none" && !lines[i].plants[j].GetDeath() && !grass_blocks[lines[i].plants[j].GetIndex()].plant.GetDeath())
            {
                skip_plant = false;
                for (int k = 0; k < lines[i].enemies.size(); k++)
                {
                    auto distance = glm::distance(lines[i].plants[j].GetPos(), lines[i].enemies[k].pos);
                    if (distance <= lines[i].enemies[k].radius + lines[i].plants[j].GetRadius())
                    {
                        lines[i].plants[j].SetDeath(true);
                        grass_blocks[lines[i].plants[j].GetIndex()].plant.SetDeath(true);
                    }
                    else
                    {
                        auto time_now = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::seconds>(time_now - lines[i].plants[j].GetTime());
                        if (lines[i].plants[j].GetType() == lines[i].enemies[k].GetType() && duration.count() >= 2 && !lines[i].enemies[k].should_die)
                        {
                            projectile_t star;
                            star.type = lines[i].plants[j].GetType();
                            star.pos = lines[i].plants[j].GetPos();
                            star.type = lines[i].plants[j].GetType();
                            lines[i].stars.push_back(star);
                            lines[i].plants[j].SetTime(std::chrono::high_resolution_clock::now());
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Tema1::RenderProjectiles(float deltaTime)
{
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].stars.size(); j++)
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(lines[i].stars[j].getPos().x, lines[i].stars[j].pos.y);
            modelMatrix *= transform2D::Rotate(lines[i].stars[j].getRotate(deltaTime));
            modelMatrix *= transform2D::Scale(20, 20);
            RenderMesh2D(meshes["projectile" + lines[i].stars[j].type], shaders["VertexColor"], modelMatrix);
        }
    }
}

void Tema1::RenderEnemies()
{
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].enemies.size(); j++)
        {
            if (!lines[i].enemies[j].should_die)
            {
                float forward = lines[i].enemies[j].GetForward();
                lines[i].enemies[j].pos = { lines[i].enemies[j].pos.x - forward, lines[i].enemies[j].pos.y };
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(lines[i].enemies[j].pos.x, lines[i].enemies[j].pos.y);
                modelMatrix *= transform2D::Scale(13, 13);
                modelMatrix *= transform2D::Rotate(8);
                RenderMesh2D(meshes["enemy" + lines[i].enemies[j].GetType()], shaders["VertexColor"], modelMatrix);
            }
            else
            {
                float scale = lines[i].enemies[j].GetScale();

                if (scale > 0.f)
                {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(lines[i].enemies[j].pos.x, lines[i].enemies[j].pos.y);
                    modelMatrix *= transform2D::Scale(scale, scale);
                    modelMatrix *= transform2D::Rotate(8);
                    RenderMesh2D(meshes["enemy" + lines[i].enemies[j].GetType()], shaders["VertexColor"], modelMatrix);
                }
                else
                {
                    lines[i].enemies.erase(lines[i].enemies.begin() + j);
                    continue;
                }
            }

            if (!lines[i].enemies[j].should_die)
            {
                glm::vec2 rectangle = { 15, grass_corner.y + square_size * i + 20 * i + square_size / 2};
                auto distance = glm::distance(rectangle, lines[i].enemies[j].pos);
                if (distance <= lines[i].enemies[j].radius + 25)
                {
                    lines[i].enemies[j].should_die = true;
                    if (health > 0)
                        health--;
                }
            }
        }
    }
    
}

void Tema1::RenderSelector()
{
    for (int i = 0; i < 4; i++)
    {
        float start_x = selector_corner.x + square_size * i + 40 * i;
        float start_y = selector_corner.y;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(start_x, start_y);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(start_x + 15, start_y + 10);
        modelMatrix *= transform2D::Scale(10, 10);
        modelMatrix *= transform2D::Translate(2, 4);
        RenderMesh2D(meshes[std::string("plant" + std::to_string(i + 1))], shaders["VertexColor"], modelMatrix);

        selector_blocks[i].pos = glm::vec2(start_x, start_y);
        selector_blocks[i].plant_name = std::string("plant" + std::to_string(i + 1));

        switch (i) 
        {
            case 0:
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(start_x, start_y - square_size / 3);
                modelMatrix *= transform2D::Scale(square_size/(star_size * 3), square_size / (star_size * 3));
                modelMatrix *= transform2D::Translate(-r_star_corner.x, -r_star_corner.y);
                RenderMesh2D(meshes["r_star"], shaders["VertexColor"], modelMatrix);
                selector_blocks[i].resources = 1;
                break;
            case 1:
                for (int j = 0; j < 2; j++)
                {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(start_x + j * (square_size / 3), start_y - square_size / 3);
                    modelMatrix *= transform2D::Scale(square_size / (star_size * 3), square_size / (star_size * 3));
                    modelMatrix *= transform2D::Translate(-r_star_corner.x, -r_star_corner.y);
                    RenderMesh2D(meshes["r_star"], shaders["VertexColor"], modelMatrix);
                    selector_blocks[i].resources = 2;
                }
                break;
            case 2:
                for (int j = 0; j < 2; j++)
                {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(start_x + j * (square_size / 3), start_y - square_size / 3);
                    modelMatrix *= transform2D::Scale(square_size / (star_size * 3), square_size / (star_size * 3));
                    modelMatrix *= transform2D::Translate(-r_star_corner.x, -r_star_corner.y);
                    RenderMesh2D(meshes["r_star"], shaders["VertexColor"], modelMatrix);
                    selector_blocks[i].resources = 2;
                }
                break;
            case 3:
                for (int j = 0; j < 3; j++)
                {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(start_x + j * (square_size / 3), start_y - square_size / 3);
                    modelMatrix *= transform2D::Scale(square_size / (star_size * 3), square_size / (star_size * 3));
                    modelMatrix *= transform2D::Translate(-r_star_corner.x, -r_star_corner.y);
                    RenderMesh2D(meshes["r_star"], shaders["VertexColor"], modelMatrix);
                    selector_blocks[i].resources = 3;
                }
                break;
        }
    }
}

void Tema1::ComputeHits()
{
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].stars.size(); j++)
        {
            for (int k = 0; k < lines[i].enemies.size(); k++)
            {
                if (lines[i].stars[j].type == lines[i].enemies[k].GetType())
                {
                    auto distance = glm::distance(lines[i].stars[j].pos, lines[i].enemies[k].pos);
                    if (distance <= lines[i].enemies[k].radius + lines[i].stars[j].radius)
                    {
                        lines[i].enemies[k].take_damage();
                        lines[i].stars[j].remove = true;
                    }
                }
            }
        }
    }

    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].stars.size(); j++)
        {
            if(lines[i].stars[j].remove)
                lines[i].stars.erase(lines[i].stars.begin() + j);
        }
    }
}

void Tema1::RenderGrass()
{
    int index = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            float start_x = grass_corner.x + square_size * i + 20 * i;
            float start_y = grass_corner.y + square_size * j + 20 * j;
            grass_blocks[index].pos = glm::vec2(start_x, start_y);
            grass_blocks[index].line = j;
            grass_blocks[index].column = i;

            if (grass_blocks[index].render_plant)
            {
                float scale = grass_blocks[index].plant.GetScale();
                if (scale <= 0)
                {
                    grass_blocks[index].render_plant = false;
                    grass_blocks[index].available = true;
                }
                else
                {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(start_x + square_size / 2 - 2 * scale, start_y + square_size / 2);
                    modelMatrix *= transform2D::Scale(scale, scale);
                    RenderMesh2D(meshes[grass_blocks[index].plant_name], shaders["VertexColor"], modelMatrix);
                }
            }

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(start_x, start_y);
            RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
            index++;
        }
    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(15, 60);
    RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderHud()
{
    for (int i = 0; i < health; i++)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(hud_corner.x + square_size * i +  i * 15, hud_corner.y);
        RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < no_resource; i++)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(hud_corner.x + i * (square_size / 3), hud_corner.y - square_size / 3);
        modelMatrix *= transform2D::Scale(square_size / (star_size * 3), square_size / (star_size * 3));
        modelMatrix *= transform2D::Translate(-r_star_corner.x, -r_star_corner.y);
        RenderMesh2D(meshes["r_star"], shaders["VertexColor"], modelMatrix);
    }
}



void Tema1::Update(float deltaTimeSeconds)
{
    if (drag_and_drop)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(window->GetCursorPosition().x, window->GetResolution().y -  window->GetCursorPosition().y);
        modelMatrix *= transform2D::Scale(10, 10);
        RenderMesh2D(meshes[drag_plant], shaders["VertexColor"], modelMatrix);
    }

    if (stars.size() == 0)
    {
        auto time_now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(time_now - star_spawn);
        if (duration.count() >= 8)
        {
            no_stars = 3;
            star_spawn = std::chrono::high_resolution_clock::now();
            collectable_t star;
            for (int i = 0; i < no_stars; i++)
            {
                star.width = (int)r_star_corner.x * 10;
                star.height = (int)r_star_corner.y * 10;
                star.pos.x = rand() % (window->GetResolution().x - star.width);
                star.pos.y = rand() % (window->GetResolution().y - star.height);
                stars.push_back(star);
            }
        }
    }
    else
    {
        for (int i = 0; i < no_stars; i++)
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(stars[i].pos.x, stars[i].pos.y);
            modelMatrix *= transform2D::Scale(10, 10);
            modelMatrix *= transform2D::Translate(-r_star_corner.x , -r_star_corner.y);
            RenderMesh2D(meshes["c_star"], shaders["VertexColor"], modelMatrix);
        }
    }

    RenderGrass();
    RenderSelector();
    RenderHud();

    if (health > 0)
    {
        SpawnEnemy();
        RenderEnemies();
        ComputeAttacks();
        RenderProjectiles(deltaTimeSeconds);
        ComputeHits();

    }
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["rectangle2"], shaders["VertexColor"], modelMatrix);
}

bool InsideSquare(glm::vec2& point, glm::vec2 corner, int length)
{
    return (point.x >= corner.x && point.x <= corner.x + length && point.y >= corner.y && point.y <= corner.y + length);
}

bool InsideRectangle(glm::vec2& point, glm::vec2 corner, int width, int height)
{
    return (point.x >= corner.x && point.x <= corner.x + width && point.y >= corner.y && point.y <= corner.y + height);
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    /*if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
    {
        drag_and_drop = true;
    }*/
}


void Tema1::OnKeyPress(int key, int mods)
{
    
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1)
    {
        for (int i = 0; i < stars.size(); i++)
        {
            if (InsideRectangle(glm::vec2(mouseX, window->GetResolution().y - mouseY), stars[i].pos, stars[i].width, stars[i].height) && no_resource < 10)
            {
                no_stars--;
                stars.erase(stars.begin() + i);
                no_resource++;
            }
        }

        for(int i = 0; i < selector_blocks.size(); i++)
            if (InsideSquare(glm::vec2(mouseX, window->GetResolution().y - mouseY), selector_blocks[i].pos, square_size))
            {
                drag_and_drop = true;
                drag_plant = selector_blocks[i].plant_name;
                drag_resources = selector_blocks[i].resources;
            }
    }

    if (button == 2)
    {
        for (int i = 0; i < grass_blocks.size(); i++)
            if (InsideSquare(glm::vec2(mouseX, window->GetResolution().y - mouseY), grass_blocks[i].pos, square_size) && !grass_blocks[i].available)
            {
                grass_blocks[i].plant.SetDeath(true);
                //lines[i].plants[j].SetDeath(true);
                //grass_blocks[lines[i].plants[j].GetIndex()].plant.SetDeath(true);
            }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (button == 1 && drag_and_drop)
    {
        drag_and_drop = false;
        for (int i = 0; i < grass_blocks.size(); i++)
            if (InsideSquare(glm::vec2(mouseX, window->GetResolution().y - mouseY), grass_blocks[i].pos, square_size) && grass_blocks[i].available && no_resource >= drag_resources)
            {
                grass_blocks[i].available = false;
                grass_blocks[i].render_plant = true;
                grass_blocks[i].plant_name = drag_plant;
                grass_blocks[i].plant = Plant();
                grass_blocks[i].plant.SetType(drag_plant.substr(drag_plant.size() - 1));
                grass_blocks[i].plant.SetPos(glm::vec2(grass_corner.x + square_size * (grass_blocks[i].column + 1) + 20 * grass_blocks[i].column, grass_corner.y + square_size * (grass_blocks[i].line )+ 20 * grass_blocks[i].line + square_size/ 2));
                grass_blocks[i].plant.SetIndex(i);
                no_resource -= drag_resources;
                lines[grass_blocks[i].line].plants[grass_blocks[i].column] = grass_blocks[i].plant;
            }
    }
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
