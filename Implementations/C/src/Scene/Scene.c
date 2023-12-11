#include "Scene.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Camera.h"

#include "Window.h"

GameScenePtr GameSceneCreate(Float2 window_size) {
  GameScenePtr result = (GameScenePtr)malloc(sizeof(struct GameScene));
  result->mCamera = CameraCreate(70, window_size.x / window_size.y, 0.001, 10);
  result->mPlanet = PlanetCreate();
  result->mSun = Float3Create(-1, -1, -1);
  return result;
}

void GameSceneDestroy(GameScenePtr scene) {
  PlanetDestroy(scene->mPlanet);
  CameraDestroy(scene->mCamera);
  free(scene);
}

void GameSceneUpdate(GameScenePtr scene, const float timestep) {

  // static
  int planetShouldRefreshMesh = 1;
  PlanetUpdate(scene->mPlanet);

  Camera3DPtr cam = scene->mCamera;

  static const float TO_RADIANS = 3.14159265f / 180.0f;

  float sy = sin(TO_RADIANS * scene->mCamera->mRotation.y);
  float cy = cos(TO_RADIANS * scene->mCamera->mRotation.y);

  int superspeed = 0;
  if (glfwGetKey(GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    superspeed = 1;

  float realVelocity =
      (cam->mPhysicalAttribs.mVelocity + superspeed) * timestep;

  if (glfwGetKey(GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
    cam->mPosition.z -= realVelocity * cy;
    cam->mPosition.x -= realVelocity * sy;
    planetShouldRefreshMesh = 1;
  }
  if (glfwGetKey(GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
    cam->mPosition.x -= realVelocity * cy;
    cam->mPosition.z += realVelocity * sy;
    planetShouldRefreshMesh = 1;
  }
  if (glfwGetKey(GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
    cam->mPosition.z += realVelocity * cy;
    cam->mPosition.x += realVelocity * sy;
    planetShouldRefreshMesh = 1;
  }
  if (glfwGetKey(GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
    cam->mPosition.x += realVelocity * cy;
    cam->mPosition.z -= realVelocity * sy;
    planetShouldRefreshMesh = 1;
  }
  if (glfwGetKey(GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
    cam->mPosition.y += realVelocity;
    planetShouldRefreshMesh = 1;
  }
  if (glfwGetKey(GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    cam->mPosition.y -= realVelocity;
    planetShouldRefreshMesh = 1;
  }
  static double x, y;
  static double ox, oy;
  static double dx, dy;
  glfwGetCursorPos(GetWindow(), &x, &y);
  dx = x - ox;
  dy = y - oy;
  ox = x;
  oy = y;
  x = 0;
  y = 0;
  if (glfwGetMouseButton(GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    cam->mRotation.x += -dy;
    cam->mRotation.y += -dx;
  }

  while (cam->mRotation.y < 0)
    cam->mRotation.y += 360;
  while (cam->mRotation.y > 360)
    cam->mRotation.y -= 360;

  while (cam->mRotation.x < -90)
    cam->mRotation.x = -90;
  while (cam->mRotation.x > 90)
    cam->mRotation.x = 90;

  if (planetShouldRefreshMesh) {
    
    //PlanetMeshManagerRefresh(&scene->mPlanet->mPlanetMeshManager,
    //                         cam->mPosition);
    planetShouldRefreshMesh = 0;
  }
}

void GameSceneRender(GameScenePtr scene, TextureManagerPtr manager) {
  RendererRenderPlanet(scene->mPlanet, scene->mSun, manager, scene->mCamera);
}

struct SceneManager SceneManagerCreate(Float2 window_size) {
  return (struct SceneManager){
      .mCurrentScene = GAME_SCENE,
      .mGeneralScenePtr = GameSceneCreate(window_size),
  };
}

void SceneManagerDestroy(struct SceneManager scene_manager) {
  if (scene_manager.mCurrentScene == GAME_SCENE)
    GameSceneDestroy(scene_manager.mGameScene);
}

void SceneManagerUpdate(struct SceneManager scene_manager,
                        const float timestep) {
  if (scene_manager.mCurrentScene == GAME_SCENE)
    GameSceneUpdate(scene_manager.mGameScene, timestep);
}

void SceneManagerRender(struct SceneManager scene_manager,
                        TextureManagerPtr texture_manager) {

  if (scene_manager.mCurrentScene == GAME_SCENE)
    GameSceneRender(scene_manager.mGameScene, texture_manager);
}