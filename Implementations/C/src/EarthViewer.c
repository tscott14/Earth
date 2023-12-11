#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "EarthViewer.h"
#include "Scene/Scene.h"
#include "Shader/Shader.h"
#include "Textures/TextureManager.h"
#include "Utilities/Transformations.h"
#include "Window.h"

/*
 * TODO:
 *  - Add skybox
 *  - Add UI + Text
 *  - Add Orbital Camera
 *  - Make planet LOD rotation agnostic 3
 *  - Add other menu screens (main menu, loading screen, settings, etc)
 *  - Add Normals + lighting 1
 *  - Fix edge gaps 2
 */

#define RUNNING_TESTS 0
void run_tests();

static int StartGLFW() {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return 1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  return 0;
}

static void LoadAllGameTextures(TextureManagerPtr manager) {
  TextureManagerLoadTextureFromFile(manager, TEST_TEXTURE_ID, "debug",
                                    SRGB_SPACE);
  TextureManagerLoadTextureFromFile(manager, BUMP_TEXTURE_ID, "bump", 0);
  TextureManagerLoadTextureFromFile(manager, BUMP_NORMAL_TEXTURE_ID, "bump_normal", 0);
}

static EarthViewerPtr EarthViewerCreate(GLFWwindow *window_handle) {
  // Pre GLEW initialization
  EarthViewerPtr result = (EarthViewerPtr)malloc(sizeof(struct EarthViewer));

  // Window Setup
  result->mWindowHandle = window_handle;
  glfwGetWindowSize(result->mWindowHandle, &result->mWindowWidth,
                    &result->mWindowHeight);
  glfwSetInputMode(result->mWindowHandle, GLFW_STICKY_KEYS, GL_TRUE);

  // Scene Setup
  result->mTextureManager = TextureManagerCreate();
  LoadAllGameTextures(result->mTextureManager);

  result->mSceneManager = SceneManagerCreate(
      Float2Create(result->mWindowWidth, result->mWindowHeight));

  return result;
}

static void EarthViewerDestroy(EarthViewerPtr ev) {
  // Destroy EarthViewer Data
  SceneManagerDestroy(ev->mSceneManager);

  glfwDestroyWindow(ev->mWindowHandle);
  free(ev);
}

void UpdateWindowTitle(double begin, double end) {
  double interval = end - begin;
  char title[128];
  sprintf(title, "Earth Viewer: [INT: %.3f ms, FPS: %d fps]", interval * 1000,
          (int)(1.0f / interval));
  glfwSetWindowTitle(GetWindow(), title);
}

int main() {
  if (RUNNING_TESTS) {
    run_tests();
    return 0;
  }

  if (StartGLFW())
    return 1;

  GLFWwindow *window = CreateWindow(1600, 1600, "Earth Viewer");
  
  glewExperimental = 1;
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return 1;
  }
  
  EarthViewerPtr ev = EarthViewerCreate(window);

  RendererSetRenderColor(0.25f, 0.2f, 0.25f);
  double previous = glfwGetTime();

  GLint MaxPatchVertices = 0;
  glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
  printf("Max # of patches: %d\n", MaxPatchVertices);
  glPatchParameteri(GL_PATCH_VERTICES, 4);

  while (!glfwWindowShouldClose(ev->mWindowHandle)) {
    const double current = glfwGetTime();
    const double timestep = current - previous;

    RendererClear();

    SceneManagerUpdate(ev->mSceneManager, (float)timestep);
    SceneManagerRender(ev->mSceneManager, ev->mTextureManager);

    UpdateWindowTitle(current, glfwGetTime());
    glfwPollEvents();
    glfwSwapBuffers(ev->mWindowHandle);

    previous = current;
    // return 0;
  }

  EarthViewerDestroy(ev);

  glfwTerminate();

  return 0;
}