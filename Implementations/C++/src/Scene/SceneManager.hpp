#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "Scenes/GameScene/GameScene.hpp"

enum class AppScenes
{
    NONE,
    MAIN_SCENE,
    GAME_SCENE,
    MAX_SCENE_COUNT,
};

class SceneManager
{
private:
    std::vector<Ref<BasicScene>> mScenes{};
    AppScenes mCurrentScene{};

public:
    SceneManager() = default;
    SceneManager(AppScenes scene);
    ~SceneManager();

    auto SetScene(AppScenes scene) -> void;

    auto HandleEvent(Event & event) -> void;
    auto Update(Timestep timestep) -> void;
    auto Render() -> void;
};

#endif