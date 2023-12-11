#include "SceneManager.hpp"

SceneManager::SceneManager(AppScenes initial)
    : mScenes(),
      mCurrentScene(initial)
{
    mScenes.reserve((Size)AppScenes::MAX_SCENE_COUNT);
    mScenes.push_back(nullptr);
    mScenes.push_back(nullptr /*Start Menu*/);
    mScenes.emplace_back(new GameScene());
}

SceneManager::~SceneManager()
{
}

auto SceneManager::SetScene(AppScenes scene) -> void
{
    assert((Size)scene);
    assert((Size)mCurrentScene);
    mScenes[(Size)mCurrentScene]->Detach();
    mCurrentScene = scene;
    mScenes[(Size)scene]->Attach();
}

auto SceneManager::HandleEvent(Event &event) -> void
{
    assert((Size)mCurrentScene);
    mScenes[(Size)mCurrentScene]->HandleEvent(event);
}

auto SceneManager::Update(Timestep timestep) -> void
{
    assert((Size)mCurrentScene);
    mScenes[(Size)mCurrentScene]->Update(timestep);
}

auto SceneManager::Render() -> void
{
    assert((Size)mCurrentScene);
    mScenes[(Size)mCurrentScene]->Render();
}