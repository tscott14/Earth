#ifndef __WINDOW__
#define __WINDOW__

#include <GLFW/glfw3.h>

#include "Utilities/Transformations.h"

GLFWwindow *CreateWindow(int, int, const char *);
GLFWwindow *GetWindow();
struct Float2 GetWindowSize();

#endif