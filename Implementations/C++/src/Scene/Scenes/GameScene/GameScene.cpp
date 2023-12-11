#include "GameScene.hpp"

#include "Display/Display.hpp"

GameScene::GameScene()
    : mSkybox(), mPlanet(),
      mOrbitalCamera(0, 0, 2, 120, DisplayManager::GetDisplay().GetAspectRatio(), 0.01, 100)
{
}

GameScene::~GameScene()
{
}

void GameScene::Attach()
{
}

void GameScene::Detach()
{
}

auto GameScene::HandleEvent(Event &event) -> void
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(
        [&](WindowResizeEvent &event)
        {
            CameraSettings set = mOrbitalCamera.GetCameraSettings();
            float ratio = (float)event.mWidth / (float)event.mHeight;
            mOrbitalCamera.SetCameraSettings(set.mFOV, ratio, set.mNear, set.mFar);
            mOrbitalCamera.UpdateProjMatrix();
            return false;
        });
    dispatcher.Dispatch<ScrollEvent>(
        [&](ScrollEvent &event)
        {
            mOrbitalCamera.ChangePhysicalAcceleration(-event.mOffsetY * 2, 0, 0);
            return false;
        });
    dispatcher.Dispatch<CursorMovedEvent>(
        [&](CursorMovedEvent &event)
        {
            GLFWwindow *window = DisplayManager::GetDisplay().GetWindowHandle();
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                mOrbitalCamera.ChangePhysicalAcceleration(0, -event.mPosDy, event.mPosDx);
            return false;
        });
}

void GameScene::Update(Timestep timestep)
{
    mPlanet.Update(timestep);
    mOrbitalCamera.Update(timestep);
}

void GameScene::Render()
{
    mOrbitalCamera.UpdateViewMatrix();
    //mOrbitalCamera.UpdateProjMatrix();
    Renderer::RenderPlanet(mPlanet, mOrbitalCamera);
    Renderer::RenderSkybox(mSkybox, mOrbitalCamera);
}