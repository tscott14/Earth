#include "ShaderLoaders.hpp"

#include <GL/glew.h>

static const auto SHADER_FILEPATH = std::string("res/shaders/Planet/");

static auto LoadShaderProgram() -> ProgramHandle
{
   printf("Loading Shader Program \'%s\'\n", SHADER_FILEPATH.c_str());
    auto vs = ShaderLoader::LoadShader(GL_VERTEX_SHADER, SHADER_FILEPATH);
    auto cs = ShaderLoader::LoadShader(GL_TESS_CONTROL_SHADER, SHADER_FILEPATH);
    auto es = ShaderLoader::LoadShader(GL_TESS_EVALUATION_SHADER, SHADER_FILEPATH);
    auto fs = ShaderLoader::LoadShader(GL_FRAGMENT_SHADER, SHADER_FILEPATH);

    auto program = (ProgramHandle)glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, cs);
    glAttachShader(program, es);
    glAttachShader(program, fs);

    glBindAttribLocation(program, 0, "aPosition_VS_in");
    glBindAttribLocation(program, 1, "aTextureCoords_VS_in");

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
    glDetachShader(program, cs);
    glDetachShader(program, es);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(cs);
    glDeleteShader(es);
    glDeleteShader(fs);

    return program;
}

auto PlanetShaderLoader::GenerateShader() -> Ref<BasicShader>
{
    return std::make_shared<BasicShader>(LoadShaderProgram());
}
