#include "ShaderLoaders.hpp"

#include <GL/glew.h>

#include "Utilities/ResourseLoader.hpp"

auto ShaderLoader::GetShaderFilename(int type) -> const std::string &
{
    static const std::string ERROR("***ERROR***");
    static const std::string vs("vs.glsl");
    static const std::string cs("cs.glsl");
    static const std::string es("es.glsl");
    static const std::string gs("gs.glsl");
    static const std::string fs("fs.glsl");

    if (type == GL_VERTEX_SHADER)
        return vs;

    if (type == GL_TESS_CONTROL_SHADER)
        return cs;

    if (type == GL_TESS_EVALUATION_SHADER)
        return es;

    if (type == GL_GEOMETRY_SHADER)
        return gs;

    if (type == GL_FRAGMENT_SHADER)
        return fs;

    return ERROR;
}

auto ShaderLoader::LoadShader(int type, const std::string &fileroot) -> ShaderHandle
{
    const auto filepath = fileroot + GetShaderFilename(type);
    printf("\t- Loading \'%s\'...", filepath.c_str());

    const auto src = TextFileLoader::LoadFile(filepath);
    const auto csrc = src.c_str();

    if (csrc)
        puts("Success!");
    else
        puts("Failed!");

    auto shader = (ShaderHandle)glCreateShader(type);
    glShaderSource(shader, 1, &csrc, NULL);
    glCompileShader(shader);

    auto result = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE)
    {
        auto infoLogLength = -1;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        char infoLog[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
        fprintf(stderr, "ERROR Compiling %d:\n%s\n", type, infoLog);
        exit(1);
    }
    
    return shader;
}