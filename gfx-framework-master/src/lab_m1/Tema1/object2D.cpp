#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill,
    float z)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, z), color),
        VertexFormat(corner + glm::vec3(length, length, z), color),
        VertexFormat(corner + glm::vec3(0, length, z), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateFilledStar(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    glm::vec3 color,
    float z
    )
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //A 0
        VertexFormat((corner + glm::vec3(21.42f,16.86f, z)), color),
        //H 1
        VertexFormat((corner + glm::vec3(22.28f,14.40f, z)), color),
        //G 2
        VertexFormat((corner + glm::vec3(20.49f,14.40f, z)), color),
        //D 3
        VertexFormat((corner + glm::vec3(18.06f, 14.44f, z)), color),
        //C 4
        VertexFormat((corner + glm::vec3(25.06f, 14.44f, z)), color),
        //F 5
        VertexFormat((corner + glm::vec3(21.42f,11.86f, z)), color),
        //J 6
        VertexFormat((corner + glm::vec3(22.82f,12.85f, z)), color),
        //E 7
        VertexFormat((corner + glm::vec3(23.78f,10.12f, z)), color),
        //B 8
        VertexFormat((corner + glm::vec3(18.88f,10.16f, z)), color),
        //I 9
        VertexFormat((corner + glm::vec3(19.95f,13.f, z)), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 
        0, 1, 2,
        1, 4, 6,
        6, 7, 5,
        5, 8, 9,
        9, 3, 2,
        3, 4, 5
    };

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateFilledStar2(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    glm::vec3 color,
    float z
)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //A 0
        VertexFormat((glm::vec3(0, 1.6f, z)), color),
        //B 1
        VertexFormat((glm::vec3(0.48f,0.42f, z)), color),
        //C 2
        VertexFormat((glm::vec3(-0.48f,0.42f, z)), color),
        //D 3
        VertexFormat((glm::vec3(-1.68f, 0.44f, z)), color),
        //E 4
        VertexFormat((glm::vec3(1.68f, 0.44f, z)), color),
        //F 5
        VertexFormat((glm::vec3(0.f,-0.4f, z)), color),
        //G 6
        VertexFormat((glm::vec3(0.60f,0.f, z)), color),
        //H 7
        VertexFormat((glm::vec3(1.28f, -1.28f, z)), color),
        //F 8
        VertexFormat((glm::vec3(-1.28f, -1.28f, z)), color),
        //I 9
        VertexFormat((glm::vec3(-0.56f,-0.08f, z)), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 2,
        1, 4, 6,
        6, 7, 5,
        5, 8, 9,
        9, 3, 2,
        3, 4, 5
    };

    square->InitFromData(vertices, indices);
    return square;
}


Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    glm::vec3 color,
    bool fill,
    float z)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, z), color),
        VertexFormat(corner + glm::vec3(width, height, z), color),
        VertexFormat(corner + glm::vec3(0, height, z), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreatePlant(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //A 0
        VertexFormat(corner + glm::vec3(0, 4, 1), color),
        //B 1
        VertexFormat(corner + glm::vec3(-2, 0, 1), color),
        //C 2
        VertexFormat(corner + glm::vec3(2, 0, 1), color),
        //D 3
        VertexFormat(corner + glm::vec3(0, -4, 1), color),
        //E 4
        VertexFormat(corner + glm::vec3(0, 1, 1), color),
        //F 5
        VertexFormat(corner + glm::vec3(6, 1, 1), color),
        //G 6
        VertexFormat(corner + glm::vec3(6, -1, 1), color),
        //H 7
        VertexFormat(corner + glm::vec3(0, -1, 1), color)

    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 2,
        1, 2, 3,
        4, 5, 6,
        6, 7, 4
    };

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateEnemy(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    glm::vec3 color, float z)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //A 0
        VertexFormat(corner + glm::vec3(-2, 3, z), color),
        //B 1
        VertexFormat(corner + glm::vec3(2, 3, z), color),
        //C 2
        VertexFormat(corner + glm::vec3(3, 0, z), color),
        //D 3
        VertexFormat(corner + glm::vec3(2, -3, z), color),
        //E 4
        VertexFormat(corner + glm::vec3(-2, -3, z), color),
        //F 5
        VertexFormat(corner + glm::vec3(-3, 0, z), color),
        //M 6
        VertexFormat(corner + glm::vec3(0, 0, z), color),
        //H 7
        VertexFormat(corner + glm::vec3(1, 2, z + 1), glm::vec3(0.4, 0.4, 0)),
        //I 8
        VertexFormat(corner + glm::vec3(2, 0, z + 1), glm::vec3(0.4, 0.4, 0)),
        //J 9
        VertexFormat(corner + glm::vec3(1, -2, z + 1), glm::vec3(0.4, 0.4, 0)),
        //K 10
        VertexFormat(corner + glm::vec3(-1, -2, z + 1), glm::vec3(0.4, 0.4, 0)),
        //L 11
        VertexFormat(corner + glm::vec3(-2, 0, z + 1), glm::vec3(0.4, 0.4, 0)),
        //G 12
        VertexFormat(corner + glm::vec3(-1, 2, z + 1), glm::vec3(0.4, 0.4, 0)),
        //N 13
        VertexFormat(corner + glm::vec3(0, 0, z + 1), glm::vec3(0.4, 0.4, 0))
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 6,
        1, 6, 2,
        6, 2, 3,
        6, 3, 4,
        6, 4, 5,
        6, 5, 0,
        6, 7, 4,

        7, 8, 13,
        8, 9, 13,
        9, 10, 13,
        13, 10, 11,
        11, 12, 13,
        13, 12, 7,
        13, 7, 12
    };

    square->InitFromData(vertices, indices);
    return square;
}