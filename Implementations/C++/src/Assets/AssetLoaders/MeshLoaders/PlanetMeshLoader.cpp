#include "MeshLoaders.hpp"

#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Utilities/GeneralMath.hpp"

#define FACE_SIDE_LENGTH 32
#define VERT_SIDE_LENGTH (FACE_SIDE_LENGTH + 1)

struct VertexData
{
    glm::vec3 mPositions{};
    glm::vec2 mTextureCoords{};
};

struct PlanetFace
{
    Indice i00, i01, i02, i03;

    PlanetFace() = default;
    PlanetFace(Indice p0, Indice p1, Indice p2, Indice p3)
        : i00(p0), i01(p1), i02(p2), i03(p3)
    {
    }
};

struct PlanetFaceVertices
{
    std::array<std::array<VertexData, VERT_SIDE_LENGTH>, VERT_SIDE_LENGTH> mData;
};

struct PlanetFaceIndicies
{
    std::array<std::array<PlanetFace, FACE_SIDE_LENGTH>, FACE_SIDE_LENGTH> mData;
};

struct PlanetVertices
{
    std::array<PlanetFaceVertices, 6> mData;
};

struct PlanetFaces
{
    std::array<PlanetFaceIndicies, 6> mData;
};

class MeshBuilder
{
private:
    Scoped<PlanetVertices> mVerticies{};
    Scoped<PlanetFaces> mFaces{};

    auto GenerateVertexPositions() -> void;
    auto GenerateVertexIndicies() -> void;
    auto GeneratePlanetVAO(VertexArrayHandle &vao, Size &length) const -> void;

public:
    MeshBuilder()
        : mVerticies(std::make_unique<PlanetVertices>()),
          mFaces(std::make_unique<PlanetFaces>())
    {
    }

    auto GeneratePlanetMesh(VertexArrayHandle &vao, Size &length) -> void;
};

static auto GenerateFaceBuffer(PlanetFaceVertices &verticies) -> void
{
    static const auto D_THETA = 90.0f / (VERT_SIDE_LENGTH - 1);
    static const auto OFFSET = 45.0f;
    for (Size v = 0; v < VERT_SIDE_LENGTH; v++)
    {
        const auto vTheta = v * D_THETA - OFFSET;
        const auto vcos = (float)cos(glm::radians(vTheta));
        const auto vsin = (float)sin(glm::radians(vTheta));
        for (Size u = 0; u < VERT_SIDE_LENGTH; u++)
        {
            static const float rVERT_SIDE_LENGTH_M1 = 1.0f / (VERT_SIDE_LENGTH - 1);
            const auto uTheta = u * D_THETA - OFFSET;
            const auto ucos = (float)cos(glm::radians(uTheta));
            const auto usin = (float)sin(glm::radians(uTheta));
            verticies.mData[v][u].mPositions = glm::vec3(usin / ucos, vsin / vcos, 1);
            verticies.mData[v][u].mTextureCoords = glm::vec2(u * rVERT_SIDE_LENGTH_M1, v * rVERT_SIDE_LENGTH_M1);
        }
    }
}

auto MeshBuilder::GenerateVertexPositions() -> void
{
    static const std::array<glm::mat4, 6> TRANSFORM_LOOKUPS = {
        gm::Rotate(0, -90, 0),
        gm::Rotate(0, 90, 0),
        gm::Rotate(90, 0, 0),
        gm::Rotate(-90, 0, 0),
        gm::Rotate(0, 0, 0),
        gm::Rotate(0, 180, 0),
    };

    PlanetFaceVertices buffer;
    GenerateFaceBuffer(buffer);

    for (auto f = 0; f < 6; f++)
    {
        const glm::mat4 transform = TRANSFORM_LOOKUPS[f];
        auto &verticies = mVerticies->mData[f];
        for (auto v = 0ull; v < (Size)verticies.mData.size(); v++)
            for (auto u = 0ull; u < (Size)verticies.mData[v].size(); u++)
            {
                const auto &point = buffer.mData[v][u];
                const auto trans = transform * glm::vec4(point.mPositions, 1);
                verticies.mData[v][u].mPositions = glm::vec3(trans.x, trans.y, trans.z);
                verticies.mData[v][u].mTextureCoords = point.mTextureCoords;
            }
    }
}

auto MeshBuilder::GenerateVertexIndicies() -> void
{
    static const auto STRIDE = VERT_SIDE_LENGTH * VERT_SIDE_LENGTH;

    for (auto f = 0; f < 6; f++)
    {
        auto &faces = mFaces->mData[f];
        for (auto v = 0ull; v < (Size)faces.mData.size(); v++)
        {
            for (auto u = 0ull; u < (Size)faces.mData[v].size(); u++)
            {
                const auto index = v * VERT_SIDE_LENGTH + u;
                const auto offset = STRIDE * f;

                const auto p0 = (Indice)(offset + index);
                const auto p1 = (Indice)(offset + index + 1);
                const auto p2 = (Indice)(offset + index + VERT_SIDE_LENGTH + 1);
                const auto p3 = (Indice)(offset + index + VERT_SIDE_LENGTH);

                //faces[v][u] = {p0, p3, p1, p1, p3, p2};
                faces.mData[v][u] = PlanetFace(p0, p1, p2, p3);
            }
        }
    }
}

auto MeshBuilder::GeneratePlanetVAO(VertexArrayHandle &vao, Size &length) const -> void
{
    const auto verticies = mVerticies->mData.data();
    const auto faces = mFaces->mData.data();

    length = sizeof(PlanetFaces) / sizeof(Indice);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBufferObjectHandle vertexPositionBuffer;
    glGenBuffers(1, &vertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(PlanetVertices),
                 verticies,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void *)offsetof(VertexData, mPositions));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void *)offsetof(VertexData, mTextureCoords));

    VertexBufferObjectHandle vertexIndiciesBuffer;
    glGenBuffers(1, &vertexIndiciesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndiciesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(PlanetFaces),
                 faces,
                 GL_STATIC_DRAW);

    glBindVertexArray(0);
}

auto MeshBuilder::GeneratePlanetMesh(VertexArrayHandle &vao, Size &length) -> void
{
    GenerateVertexPositions();
    GenerateVertexIndicies();
    GeneratePlanetVAO(vao, length);
}

auto PlanetMeshLoader::GenerateMesh() -> Ref<BasicMesh>
{
    VertexArrayHandle vao;
    Size length;
    MeshBuilder builder;
    builder.GeneratePlanetMesh(vao, length);
    return std::make_shared<BasicMesh>(vao, length);
}