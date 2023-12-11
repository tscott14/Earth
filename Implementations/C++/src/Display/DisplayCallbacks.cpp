#include "Display.hpp"

#include "Events/Event.hpp"

auto DisplayManager::AttachCallbacks(GLFWwindow *window) -> void
{
    glfwSetWindowCloseCallback(window, DisplayManager::WindowCloseCallback);
    glfwSetWindowSizeCallback(window, DisplayManager::WindowResizeCallback);
    glfwSetFramebufferSizeCallback(window, DisplayManager::WindowFramebufferResizeCallback);
    glfwSetWindowContentScaleCallback(window, DisplayManager::WindowContentScaleCallback);
    glfwSetWindowPosCallback(window, DisplayManager::WindowPositionCallback);
    glfwSetWindowIconifyCallback(window, DisplayManager::WindowIconifyCallback);
    glfwSetWindowMaximizeCallback(window, DisplayManager::WindowMaximizedCallback);
    glfwSetWindowFocusCallback(window, DisplayManager::WindowFocusCallback);
    glfwSetWindowRefreshCallback(window, DisplayManager::WindowRefreshCallback);
    glfwSetKeyCallback(window, DisplayManager::KeyCallback);
    glfwSetCharCallback(window, DisplayManager::TextCallback);
    glfwSetCursorPosCallback(window, DisplayManager::CursorPositionCallback);
    glfwSetCursorEnterCallback(window, DisplayManager::CursorEnterCallback);
    glfwSetMouseButtonCallback(window, DisplayManager::MouseButtonCallback);
    glfwSetScrollCallback(window, DisplayManager::ScrollCallback);
}

auto DisplayManager::WindowCloseCallback(GLFWwindow *) -> void
{
    WindowClosedEvent event;
    HandleEvent(event);
}

auto DisplayManager::WindowResizeCallback(GLFWwindow *, int width, int height) -> void
{
    WindowResizeEvent event(width, height);
    HandleEvent(event);
}

auto DisplayManager::WindowFramebufferResizeCallback(GLFWwindow *, int width, int height) -> void
{
    // TODO:
}

auto DisplayManager::WindowContentScaleCallback(GLFWwindow *, float xfact, float yfact) -> void
{
    //TODO:
}

auto DisplayManager::WindowPositionCallback(GLFWwindow *, int xpos, int ypos) -> void
{
    WindowMovedEvent event(xpos, ypos);
    HandleEvent(event);
}

auto DisplayManager::WindowIconifyCallback(GLFWwindow *, int iconify) -> void
{
    // TODO:
    if (iconify)
    {
        // The window was iconified
    }
    else
    {
        // The window was restored
    }
}

auto DisplayManager::WindowMaximizedCallback(GLFWwindow *, int maximized) -> void
{
    // TODO:
    if (maximized)
    {
        // The window was maximized
    }
    else
    {
        // The window was restored
    }
}

auto DisplayManager::WindowFocusCallback(GLFWwindow *, int focused) -> void
{

    if (focused)
    {
        WindowFocusGainedEvent event;
        HandleEvent(event);
    }
    else
    {
        WindowFocusLostEvent event;
        HandleEvent(event);
    }
}

auto DisplayManager::WindowRefreshCallback(GLFWwindow *) -> void
{
    // TODO:
}

auto DisplayManager::KeyCallback(GLFWwindow *, int key, int scancode, int action, int mods) -> void
{
    KeyEvent event(key, scancode, action, mods);
    HandleEvent(event);
}

auto DisplayManager::TextCallback(GLFWwindow *, unsigned int codepoint) -> void
{
    TextEvent event(codepoint);
    HandleEvent(event);
}

auto DisplayManager::CursorPositionCallback(GLFWwindow *, double xpos, double ypos) -> void
{
    static float ox = (float)xpos, oy = (float)ypos;
    float dx = xpos - (float)ox;
    float dy = ypos - (float)oy;
    ox = (float)xpos;
    oy = (float)ypos;
    CursorMovedEvent event(xpos, ypos, dx, dy);
    HandleEvent(event);
}

auto DisplayManager::CursorEnterCallback(GLFWwindow *, int entered) -> void
{
    if (entered)
    {
        CursorEnteredEvent event;
        HandleEvent(event);
    }
    else
    {
        CursorExitedEvent event;
        HandleEvent(event);
    }
}

auto DisplayManager::MouseButtonCallback(GLFWwindow *, int button, int action, int mods) -> void
{
    MouseButtonEvent event(button, action, mods);
    HandleEvent(event);
}

auto DisplayManager::ScrollCallback(GLFWwindow *, double xoff, double yoff) -> void
{
    ScrollEvent event(xoff, yoff);
    HandleEvent(event);
}