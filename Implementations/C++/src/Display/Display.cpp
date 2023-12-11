#include "Display.hpp"

#include "EarthViewer.hpp"
#include "Events/Event.hpp"

std::shared_ptr<Display> DisplayManager::sDisplay{};
EventHandlerFn DisplayManager::sEventHandler{};

auto DisplayManager::HandleEvent(Event &event) -> void
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(
        [&](WindowResizeEvent &event)
        {
            printf("Screen Resize Event: [%d, %d]\n", event.mWidth, event.mHeight);
            glViewport(0, 0, event.mWidth, event.mHeight);
            return false;
        });
    dispatcher.Dispatch<KeyEvent>(
        [&](KeyEvent &event)
        {
            const auto window = sDisplay->GetWindowHandle();
            const auto &df = sDisplay->GetFlags();
            if (df.mMouseCaptured && event.mKey == GLFW_KEY_RIGHT_CONTROL && event.mAction == GLFW_PRESS)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                sDisplay->SetFlags(false);
            }

            if (event.mKey == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
            return false;
        });
    dispatcher.Dispatch<MouseButtonEvent>(
        [&](MouseButtonEvent &event)
        {
            const auto window = sDisplay->GetWindowHandle();
            const DisplayFlags &df = sDisplay->GetFlags();
            if (!df.mMouseCaptured && event.mButton == GLFW_MOUSE_BUTTON_LEFT)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                sDisplay->SetFlags(true);
            }
            return false;
        });
    sEventHandler(event);
}

auto DisplayManager::MakeDisplay(int width, int height, const std::string &title) -> Ref<Display>
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == nullptr)
    {
        fprintf(stderr, "Failed to open GLFW window!\n");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);

    AttachCallbacks(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

    sDisplay = std::make_shared<Display>(window);
    sDisplay->SetFlags(true);
    sDisplay->SetVisable(true);
    return sDisplay;
}

auto DisplayManager::GetDisplay(int) -> Display &
{
    return *sDisplay.get();
}

auto DisplayManager::SetEventHandler(EventHandlerFn func) -> void
{
    sEventHandler = func;
}

auto Display::Clear() -> void
{
    //glClearColor(0.2, 0.4, 0.8, 1.0);
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto Display::Update() -> void
{
    glfwPollEvents();
    glfwSwapBuffers(mWindow);
}

auto Display::SetVisable(bool visible) -> void
{
    if (visible)
        glfwShowWindow(mWindow);
    else
        glfwHideWindow(mWindow);
}

auto Display::SetSize(int width, int height) -> void
{
    glfwSetWindowSize(mWindow, width, height);
}

auto Display::SetFlags(bool mouse_captured) -> void
{
    mFlags.mMouseCaptured = mouse_captured;
}

auto Display::ShouldClose() const -> bool
{
    return glfwWindowShouldClose(mWindow);
}

auto Display::GetSize() const -> DisplaySize
{
    DisplaySize res;
    glfwGetWindowSize(mWindow, &res.mWidth, &res.mHeight);
    return res;
}

auto Display::GetAspectRatio() const -> float
{
    DisplaySize size = GetSize();
    return (float)size.mWidth / (float)size.mHeight;
}