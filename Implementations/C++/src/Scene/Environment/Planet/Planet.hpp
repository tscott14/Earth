#ifndef PLANET_HPP
#define PLANET_HPP

#include <glm/glm.hpp>
#include "PDH.hpp"


class Planet
{
private:
    glm::vec3 mPosition{};
    glm::vec3 mRotation{};

public:
    Planet();
    ~Planet();

    auto Update(Timestep) ->  void;

    auto GenerateModelMatrix() -> glm::mat4;

    auto GetPosition() const -> const glm::vec3 & { return mPosition; }
    auto GetRotation() const -> const glm::vec3 & { return mRotation; }
};

#endif