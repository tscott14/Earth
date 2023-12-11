#ifndef __SCENE__
#define __SCENE__

#include "Camera.h"
#include "Planet/Planet.h"
#include "Textures/TextureManager.h"

enum Scenes {
    TITLE_SCENE,
    GAME_SCENE,
};

typedef struct GameScene {
  Camera3DPtr mCamera;
  PlanetPtr mPlanet;
  Vector3f mSun;
  // Skybox
  // UI
} *GameScenePtr;

typedef struct SceneManager {
    enum Scenes mCurrentScene;
    union {
        void* mGeneralScenePtr;
        GameScenePtr mGameScene;
    };
} *SceneManagerPtr;

GameScenePtr GameSceneCreate(Float2);
void GameSceneDestroy(GameScenePtr);
void GameSceneUpdate(GameScenePtr, const float);
void GameSceneRender(GameScenePtr, TextureManagerPtr);


struct SceneManager SceneManagerCreate(Float2 window_size);
void SceneManagerDestroy(struct SceneManager);
void SceneManagerUpdate(struct SceneManager, const float);
void SceneManagerRender(struct SceneManager, TextureManagerPtr);

#endif