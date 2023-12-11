#ifndef TEXTURE_LOADERS_HPP
#define TEXTURE_LOADERS_HPP

#include <string>

#include "Assets/Textures/Texture.hpp"

class StandardTextureLoader
{
private:
    static auto LoadTexture(int, int, const uint8_t[], Size, Size, Size) -> TextureHandle;

public:
    static auto GenerateTexture(const uint8_t bytes[], Size width, Size height, Size channels) -> Ref<BasicTexture>;
    static auto GenerateTexture(const std::string &filename) -> Ref<BasicTexture>;
};

class CubemapTextureLoader
{
private:
public:
    static auto GenerateTexture(const std::string &dirname) -> Ref<BasicTexture>;
};

#endif