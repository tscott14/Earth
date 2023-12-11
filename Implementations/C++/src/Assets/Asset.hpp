#ifndef ASSET_HPP
#define ASSET_HPP

enum class AssetType
{
    TEXTURES,
    MESHES,
    SHADERS,
};

class Asset
{
private:
    AssetType mType{};

public:
    Asset(AssetType type)
        : mType(type)
    {
    }
};

#endif