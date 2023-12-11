#include "GeneralMath.hpp"

namespace gm
{
    auto Rotate(float rx, float ry, float rz) -> glm::mat4
    {
        const glm::mat4 x = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1, 0, 0));
        const glm::mat4 y = glm::rotate(glm::mat4(1.0f), glm::radians(ry), glm::vec3(0, 1, 0));
        const glm::mat4 z = glm::rotate(glm::mat4(1.0f), glm::radians(rz), glm::vec3(0, 0, 1));
        return x * z * y;
    }

    auto Rotate(const glm::vec3 &rot) -> glm::mat4
    {
        return Rotate(rot.x, rot.y, rot.z);
    }
}