#include "TextureLoaders.hpp"

#include <GL/glew.h>

#include "stb_image/stb_image.h"

static const auto TEXTURE_ROOT_FILEPATH = std::string("res/textures/");

auto StandardTextureLoader::LoadTexture(int wrap,
                                        int filter,
                                        const uint8_t bytes[],
                                        Size width,
                                        Size height,
                                        Size channels) -> TextureHandle
{
    TextureHandle textureHandle;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    const auto channelSetting = GL_RGB + channels - 3;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, channelSetting,
                 GL_UNSIGNED_BYTE, bytes);
    //glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureHandle;
}

auto StandardTextureLoader::GenerateTexture(const uint8_t bytes[],
                                            Size width,
                                            Size height,
                                            Size channels) -> Ref<BasicTexture>
{
    return std::make_shared<BasicTexture>(LoadTexture(GL_REPEAT, GL_LINEAR, bytes, width, height, channels));
}

auto StandardTextureLoader::GenerateTexture(const std::string &filename) -> Ref<BasicTexture>
{
    const auto filepath = TEXTURE_ROOT_FILEPATH + filename + ".png";

    printf("Loading Texture \'%s\'\n", filepath.c_str());

    stbi_set_flip_vertically_on_load(0);

    int width, height, channels;
    auto data = (uint8_t *)stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    if (!data)
    {
        fprintf(stderr, "Could not load image with filepath %s\n", filepath.c_str());
        exit(1);
    }

    auto textureHandle = LoadTexture(GL_REPEAT, GL_NEAREST, data, width, height, channels);

    stbi_image_free(data);

    return std::make_shared<BasicTexture>(textureHandle);
}
