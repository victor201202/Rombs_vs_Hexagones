#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false, float z = 0.f);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = false, float z = 0.f);
    Mesh* CreateFilledStar(const std::string& name, glm::vec3 leftBottomCorner, glm::vec3 color, float z = 0.f);
    Mesh* CreateFilledStar2(const std::string& name, glm::vec3 leftBottomCorner, glm::vec3 color, float z = 0.f);
    Mesh* CreatePlant(const std::string& name, glm::vec3 leftBottomCorner, glm::vec3 color);
    Mesh* CreateEnemy(const std::string& name, glm::vec3 leftBottomCorner, glm::vec3 color, float z = 0);
}
