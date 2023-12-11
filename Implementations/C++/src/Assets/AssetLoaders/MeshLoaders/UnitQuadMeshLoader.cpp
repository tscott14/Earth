#include "MeshLoaders.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

static auto GenerateUnitQuadMesh(VertexArrayHandle &vao, Size &length) -> void
{
    struct Vertex
    {
        glm::vec3 mPosition;
        glm::vec2 mTexCoords;
    };

    static const Vertex VERTICES[] = {
        Vertex{glm::vec3(-1, 1, 0), glm::vec2(0, 0)},
        Vertex{glm::vec3(-1, -1, 0), glm::vec2(0, 1)},
        Vertex{glm::vec3(1, 1, 0), glm::vec2(1, 0)},

        Vertex{glm::vec3(1, 1, 0), glm::vec2(1, 0)},
        Vertex{glm::vec3(-1, -1, 0), glm::vec2(0, 1)},
        Vertex{glm::vec3(1, -1, 0), glm::vec2(1, 1)}};

    length = sizeof(VERTICES) / sizeof(Vertex);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBufferObjectHandle vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)12);

    glBindVertexArray(0);
}

auto UnitQuadMeshLoader::GenerateMesh() -> Ref<BasicMesh>
{
    VertexArrayHandle vao;
    Size length;
    GenerateUnitQuadMesh(vao, length);
    return std::make_shared<BasicMesh>(vao, length);
}