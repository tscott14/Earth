#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Render/Renderer.hpp"
#include "Scene/Scenes/Scene.hpp"
#include "Scene/Environment/Planet/Planet.hpp"
#include "Scene/Environment/Space/Skybox.hpp"
#include "Scene/Environment/Camera/OrbitalCamera/OrbitalCamera.hpp"

class GameScene : public BasicScene
{
private:
    Skybox mSkybox{};
    Planet mPlanet{};
    OrbitalCamera mOrbitalCamera{};

public:
    GameScene();
    ~GameScene();

    virtual auto Attach() -> void override;
    virtual auto Detach() -> void override;

    virtual auto HandleEvent(Event &event) -> void override;
    virtual auto Update(Timestep timestep) -> void override;
    virtual auto Render() -> void override;
};

#endif