#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <array>

#include "PDH.hpp"
#include "Utilities/StringView.hpp"

#include "Asset.hpp"
#include "Textures/Texture.hpp"
#include "Meshes/Mesh.hpp"
#include "Shaders/Shader.hpp"

enum class AppMesh
{
    UNIT_QUAD,
    PLANET,
    SKYBOX,
    APP_MESHES_COUNT
};

enum class AppShader
{
    LOADING_SCREEN,
    PLANET,
    SKYBOX,
    APP_SHADERS_COUNT
};

enum class AppTexture
{
    NOT_FOUND,
    DEMO,
    SKYBOX,
    APP_TEXTURES_COUNT
};

class AssetManager
{
private:
    template <typename T, Size S>
    using AssetElements = std::array<Ref<T>, S>;

    static AssetElements<BasicMesh, (Size)AppMesh::APP_MESHES_COUNT> sMeshes;
    static AssetElements<BasicShader, (Size)AppShader::APP_SHADERS_COUNT> sShaders;
    static AssetElements<BasicTexture, (Size)AppTexture::APP_TEXTURES_COUNT> sTextures;

public:
    static auto LoadMeshesAssets() -> void;
    static auto LoadShadersAssets() -> void;
    static auto LoadTextureAssets() -> void;

    static auto DestroyAssets() -> void;

    static auto GetMesh(AppMesh mesh) -> const BasicMesh &;
    static auto GetShader(AppShader shader) -> const BasicShader &;
    static auto GetTexture(AppTexture texture) -> const BasicTexture &;
};

#endif