#include "Window.h"

#include <GLFW/glfw3.h>
#include <stdio.h>

static GLFWwindow *window;

static GLFWwindow *CreateWindowInner(int width, int height, const char *title) {
  GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to open GLFW window!\n");
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(window);

  return window;
}

GLFWwindow *CreateWindow(int width, int height, const char *title) {
  return window = CreateWindowInner(width, height, title);
}

GLFWwindow *GetWindow() {
  return window;
}

struct Float2 GetWindowSize() {
  int width = 0, height = 0;
  glfwGetWindowSize(window, &width, &height);
  return Float2Create(width, height);
}