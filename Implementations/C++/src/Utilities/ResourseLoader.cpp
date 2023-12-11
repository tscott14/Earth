#include "ResourseLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

auto GLFWLoader::Initialize() -> bool
{
    static bool initialized = false;
    printf("Initializing GLFW...");
    if (initialized)
    {
        puts("Success!");
        return true;
    }

    if (!glfwInit())
    {
        puts("Failed!");
        fprintf(stderr, "Failed to initialize GLFW\n");
        return false;
    }

    initialized = true;
    puts("Success!");
    return true;
}

auto GLEWLoader::Initialize() -> bool
{
    static bool initialized = false;
    printf("Initializing GLEW...");
    if (initialized)
    {
        puts("Success!");
        return true;
    }

    glewExperimental = 1;
    if (glewInit() != GLEW_OK)
    {
        puts("Failed!");
        fprintf(stderr, "Failed to initialize GLEW\n");
        return false;
    }

    initialized = true;
    puts("Success!");
    return true;
}

auto GLEWLoader::SetPatchVertices(int count) -> void
{
    int MaxPatchVertices = 0;
    glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
    printf("Max number of patch vertices: %d\n", MaxPatchVertices);
    glPatchParameteri(GL_PATCH_VERTICES, count);
    printf("Set number of patch vertices: %d\n", count);
}

auto TextFileLoader::LoadFile(const std::string &filepath) -> const std::string
{
    auto file = fopen(filepath.c_str(), "rt");
    if (!file)
        fprintf(stderr, "Could not open file: %s", filepath.c_str());
    fseek(file, 0, SEEK_END);
    auto length = ftell(file);
    auto data = (char *)malloc(sizeof(char) * (length + 1));
    memset(data, 0, length + 1);
    fseek(file, 0, SEEK_SET);
    fread(data, 1, length, file);
    fclose(file);

    auto result = std::string(data);
    free(data);
    return result;
}
