#ifndef GENERAL_MATH_HPP
#define GENERAL_MATH_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gm
{
    auto Rotate(float rx, float ry, float rz) -> glm::mat4;
    auto Rotate(const glm::vec3 &rv) -> glm::mat4;
}

#endif