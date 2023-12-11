#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "PDH.hpp"
#include "Scene/Environment/Space/Skybox.hpp"
#include "Scene/Environment/Planet/Planet.hpp"
#include "Scene/Environment/Camera/OrbitalCamera/OrbitalCamera.hpp"
#include "Assets/AssetManager.hpp"

class Renderer
{
private:
public:
    static auto RenderStartupScreen() -> void;
    static auto RenderPlanet(Planet &planet, OrbitalCamera &camera) -> void;
    static auto RenderSkybox(Skybox &skybox, OrbitalCamera &camera) -> void;
    static auto RenderUI() -> void;
};

#endif
