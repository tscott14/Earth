#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <glm/glm.hpp>

class Skybox
{
private:
    glm::vec3 mRotation{};

public:
    Skybox(const glm::vec3 rotation = glm::vec3(0, 0, 0))
        : mRotation(rotation)
    {
    }

    auto Rotate(float rx, float ry, float rz) -> const glm::vec3 &;
    auto GenerateModelMatrix() -> glm::mat4;
};

#endif