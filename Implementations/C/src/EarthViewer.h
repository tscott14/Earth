#ifndef __EARTH_VIEWER__
#define __EARTH_VIEWER__

#include <stdlib.h>

#include "Renderer.h"
#include "Scene/Scene.h"
#include "Textures/TextureManager.h"

#include <GLFW/glfw3.h>

typedef struct EarthViewer {
  GLFWwindow *mWindowHandle;
  int mWindowWidth, mWindowHeight;

  TextureManagerPtr mTextureManager;

  struct SceneManager mSceneManager;

} *EarthViewerPtr;

#endif