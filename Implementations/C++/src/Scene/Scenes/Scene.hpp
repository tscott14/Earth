#ifndef SCENE_HPP
#define SCENE_HPP

#include "PDH.hpp"
#include "Events/Event.hpp"

class BasicScene
{
private:
public:
    BasicScene() = default;
    virtual ~BasicScene(){}

    virtual auto Attach() -> void = 0;
    virtual auto Detach() -> void = 0;

    virtual auto HandleEvent(Event &) -> void = 0;
    virtual auto Update(Timestep) -> void = 0;
    virtual auto Render() -> void = 0;
};

#endif