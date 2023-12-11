#include "EarthViewer.hpp"

EarthViewer::EarthViewer()
    : mSceneManager(AppScenes::GAME_SCENE)
{
}

EarthViewer::~EarthViewer()
{
}

auto EarthViewer::HandleEvent(Event &event) -> void
{
    mSceneManager.HandleEvent(event);
}

auto EarthViewer::Update(Timestep Timestep) -> void
{
    mSceneManager.Update(Timestep);
}

void EarthViewer::Render()
{
    mSceneManager.Render();
}