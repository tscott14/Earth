#ifndef BASIC_SHADER_HPP
#define BASIC_SHADER_HPP

#include <glm/glm.hpp>

#include "PDH.hpp"
#include "Assets/Asset.hpp"

using ProgramHandle = unsigned int;
using ShaderHandle = unsigned int;
using UniformLocation = int;

class BasicShader : public Asset
{
private:
    ProgramHandle mProgramHandle{};

protected:

    auto GetShaderExtention(int type) const -> std::string;
    auto GetFullShaderPath(int type, const std::string &filename) const -> std::string;

public:
    BasicShader(ProgramHandle handle)
        : Asset(AssetType::SHADERS),
          mProgramHandle(handle)
    {
    }

    auto Bind() const -> void;
    auto Unbind() const -> void;

    auto GetUniformLocation(const std::string &name) const -> UniformLocation;
    auto LoadInt(const std::string &name, int value) const -> void;
    auto LoadFloat(const std::string &name, float value) const -> void;
    auto LoadFloat2(const std::string &name, const glm::vec2 &value) const -> void;
    auto LoadFloat3(const std::string &name, const glm::vec3 &value) const -> void;
    auto LoadFloat4(const std::string &name, const glm::vec4 &value) const -> void;
    auto LoadMatrix4(const std::string &name, const glm::mat4 &value) const -> void;

    auto GetProgramHandle() const -> ProgramHandle { return mProgramHandle; }
};

#endif