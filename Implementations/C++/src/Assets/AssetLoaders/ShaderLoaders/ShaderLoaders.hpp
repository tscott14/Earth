#ifndef SHADER_LOADERS_HPP
#define SHADER_LOADERS_HPP

#include <vector>

#include "Assets/Shaders/Shader.hpp"

class ShaderLoader
{
    private:
        static auto GetShaderFilename(int type) -> const std::string &;
    public:
        static auto LoadShader(int type, const std::string &filepath) -> ShaderHandle;
};

class LoadingScreenShaderLoader
{
    private:
    public:
        static auto GenerateShader() -> Ref<BasicShader>;
};

class PlanetShaderLoader
{
    private:
    public:
        static auto GenerateShader() -> Ref<BasicShader>;
};

class SkyboxShaderLoader
{
    private:
    public:
        static auto GenerateShader() -> Ref<BasicShader>;
};

#endif