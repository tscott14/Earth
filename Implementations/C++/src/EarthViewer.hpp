#ifndef EARTH_VIEWER_HPP
#define EARTH_VIEWER_HPP

#include "PDH.hpp"
#include "Display/Display.hpp"
#include "Scene/SceneManager.hpp"
#include "Events/Event.hpp"

class EarthViewer
{
private:
    SceneManager mSceneManager{};

public:
    EarthViewer();
    ~EarthViewer();

    auto HandleEvent(Event &event) -> void;
    auto Update(Timestep timestep) -> void;
    auto Render() -> void;
};

#endif