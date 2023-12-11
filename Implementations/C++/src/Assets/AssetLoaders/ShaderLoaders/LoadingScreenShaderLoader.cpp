#include "ShaderLoaders.hpp"

#include <GL/glew.h>

static const auto SHADER_FILEPATH = std::string("res/shaders/StartScreen/");

static auto LoadShaderProgram() -> ProgramHandle
{
    printf("Loading Shader Program \'%s\'\n", SHADER_FILEPATH.c_str());
    auto vs = ShaderLoader::LoadShader(GL_VERTEX_SHADER, SHADER_FILEPATH);
    auto fs = ShaderLoader::LoadShader(GL_FRAGMENT_SHADER, SHADER_FILEPATH);

    auto program = (ProgramHandle)glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glBindAttribLocation(program, 0, "aPosition");
    glBindAttribLocation(program, 1, "aTexCoords");

    glLinkProgram(program);

    auto result = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result)
    {
        auto infoLogLength = -1;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        char infoLog[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
        fprintf(stderr, "ERROR Linking:\n%s\n", infoLog);
        exit(1);
    }

    glDetachShader(program, vs);
    glDetachShader(program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

auto LoadingScreenShaderLoader::GenerateShader() -> Ref<BasicShader>
{
    return std::make_shared<BasicShader>(LoadShaderProgram());
}