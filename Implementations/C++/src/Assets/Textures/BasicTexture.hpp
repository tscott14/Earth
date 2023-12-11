#ifndef BASIC_TEXTURE_HPP
#define BASIC_TEXTURE_HPP

#include "PDH.hpp"
#include "Assets/Asset.hpp"

using TextureHandle = unsigned int;

class BasicTexture : public Asset
{
private:
    TextureHandle mTextureHandle{};

public:
    BasicTexture(TextureHandle handle) 
    : Asset(AssetType::TEXTURES), mTextureHandle(handle)
    {}

    auto Bind(int loc = 0) const -> void;
    auto Unbind() const -> void;

    auto GetTextureHandle() const -> TextureHandle { return mTextureHandle; }
};

#endif