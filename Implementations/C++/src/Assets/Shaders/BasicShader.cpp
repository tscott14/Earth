#include "BasicShader.hpp"

#include <GL/glew.h>

// auto BasicShader::ValidateShader(ShaderHandle shader) const -> bool
// {
//     auto result = GL_FALSE;
//     glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
//     if (result != GL_TRUE)
//     {
//         auto infoLogLength = -1;
//         glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
//         char infoLog[infoLogLength + 1];
//         glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
//         fprintf(stderr, "ERROR Compiling:\n%s\n", infoLog);
//         return false;
//     }
//     return true;
// }

// auto BasicShader::ValidateProgram(ProgramHandle program) const -> bool
// {
//     auto result = GL_FALSE;
//     glGetProgramiv(program, GL_LINK_STATUS, &result);
//     if (!result)
//     {
//         auto infoLogLength = -1;
//         glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
//         char infoLog[infoLogLength + 1];
//         glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
//         fprintf(stderr, "ERROR Linking:\n%s\n", infoLog);
//         return false;
//     }
//     return true;
// }

// auto BasicShader::LoadShader(int type, const std::string &fileroot) const -> ShaderHandle
// {
//     auto fullpath = fileroot + GetShaderExtention(type);
//     auto src = TextFileLoader::LoadFile(fullpath);
//     auto csrc = src.c_str();
//     printf("\t- Loading Shader \'%s\'...", fullpath.c_str());
//     auto shader = (ShaderHandle)glCreateShader(type);
//     glShaderSource(shader, 1, &csrc, NULL);
//     glCompileShader(shader);

//     if(!ValidateShader(shader))
//     {
//         puts("Failed");
//         exit(1);
//     }

//     puts("Success!");
//     return shader;
// }

// auto BasicShader::GetShaderExtention(int type) const -> std::string
// {
//     if (type == GL_VERTEX_SHADER)
//         return std::string("vs.glsl");
//     if (type == GL_TESS_CONTROL_SHADER)
//         return std::string("cs.glsl");
//     if (type == GL_TESS_EVALUATION_SHADER)
//         return std::string("es.glsl");
//     if (type == GL_GEOMETRY_SHADER)
//         return std::string("gs.glsl");
//     if (type == GL_FRAGMENT_SHADER)
//         return std::string("fs.glsl");

//     fprintf(stderr, "Invalid value for parameter \'type\'");
//     exit(1);
//     return std::string("");
// }

// auto BasicShader::GetFullShaderPath(int type, const std::string &filename) const -> std::string
// {
//     return std::string("res/shaders/")
//         .append(filename)
//         .append("/")
//         .append(GetShaderExtention(type));
// }

auto BasicShader::Bind() const -> void
{
    glUseProgram(mProgramHandle);
}

auto BasicShader::Unbind() const -> void
{
    glUseProgram(0);
}

auto BasicShader::GetUniformLocation(const std::string &name) const -> UniformLocation
{
    return (UniformLocation)glGetUniformLocation(mProgramHandle, name.c_str());
}

auto BasicShader::LoadInt(const std::string &name, int value) const -> void
{
    UniformLocation loc = GetUniformLocation(name);
    glUniform1i((GLint)loc, (GLint)value);
}

auto BasicShader::LoadFloat(const std::string &name, float value) const -> void
{
    UniformLocation loc = GetUniformLocation(name);
    glUniform1f((GLint)loc, (GLfloat)value);
}

auto BasicShader::LoadFloat2(const std::string &name, const glm::vec2 &value) const -> void
{
    UniformLocation loc = GetUniformLocation(name);
    glUniform2f((GLint)loc, (GLfloat)value.x, (GLfloat)value.y);
}

auto BasicShader::LoadFloat3(const std::string &name, const glm::vec3 &value) const -> void
{
    UniformLocation loc = GetUniformLocation(name);
    glUniform3f((GLint)loc, (GLfloat)value.x, (GLfloat)value.y, (GLfloat)value.z);
}

auto BasicShader::LoadFloat4(const std::string &name, const glm::vec4 &value) const -> void
{
    UniformLocation loc = GetUniformLocation(name);
    glUniform4f((GLint)loc, (GLfloat)value.x, (GLfloat)value.y, (GLfloat)value.z, (GLfloat)value.w);
}

auto BasicShader::LoadMatrix4(const std::string &name, const glm::mat4 &value) const -> void
{
    UniformLocation loc = GetUniformLocation(name);
    glUniformMatrix4fv((GLint)loc, 1, GL_FALSE, (GLfloat *)&value[0][0]);
}