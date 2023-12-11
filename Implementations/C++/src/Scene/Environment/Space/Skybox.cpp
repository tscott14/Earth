#include "Skybox.hpp"

auto Skybox::Rotate(float rx, float ry, float rz) -> const glm::vec3 &
{
    mRotation.x += rx;
    mRotation.y += ry;
    mRotation.z += rz;
    return mRotation;
}

auto Skybox::GenerateModelMatrix() -> glm::mat4
{
    return glm::mat4(1.0f);
}