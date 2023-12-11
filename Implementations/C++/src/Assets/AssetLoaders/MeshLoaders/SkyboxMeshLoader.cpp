#include "MeshLoaders.hpp"

#include <GL/glew.h>

static auto GenerateSkyboxMesh(VertexArrayHandle &vao, Size &length) -> void
{
    struct Vertex
    {
        float mX, mY, mZ;

        Vertex(float x, float y, float z)
            : mX(x), mY(y), mZ(z)
        {
        }
    };

    static const float SIZE = 10.0f;

    static const Vertex LTB{-SIZE, SIZE, -SIZE};
    static const Vertex LBB{-SIZE, -SIZE, -SIZE};
    static const Vertex RBB{SIZE, -SIZE, -SIZE};
    static const Vertex RTB{SIZE, SIZE, -SIZE};
    static const Vertex LBF{-SIZE, -SIZE, SIZE};
    static const Vertex LTF{-SIZE, SIZE, SIZE};
    static const Vertex RBF{SIZE, -SIZE, SIZE};
    static const Vertex RTF{SIZE, SIZE, SIZE};

    static const Vertex VERTICES[] = {
        LTB,
        LBB,
        RBB,
        RBB,
        RTB,
        LTB,

        LBF,
        LBB,
        LTB,
        LTB,
        LTF,
        LBF,

        RBB,
        RBF,
        RTF,
        RTF,
        RTB,
        RBB,

        LBF,
        LTF,
        RTF,
        RTF,
        RBF,
        LBF,

        LTB,
        RTB,
        RTF,
        RTF,
        LTF,
        LTB,

        LBB,
        LBF,
        RBB,
        RBB,
        LBF,
        RBF,
    };

    length = sizeof(VERTICES) / sizeof(Vertex);

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBufferObjectHandle positions_buffer;
    glGenBuffers(1, &positions_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, positions_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, mX));

    glBindVertexArray(0);
}

auto SkyboxMeshLoader::GenerateMesh() -> Ref<BasicMesh>
{
    VertexArrayHandle vao;
    Size length;
    GenerateSkyboxMesh(vao, length);
    return std::make_shared<BasicMesh>(vao, length);
}