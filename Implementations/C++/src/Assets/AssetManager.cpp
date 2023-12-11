#include "AssetManager.hpp"

#include <GL/glew.h>
#include "AssetLoaders/AssetLoaders.hpp"

AssetManager::AssetElements<BasicMesh, (Size)AppMesh::APP_MESHES_COUNT> AssetManager::sMeshes{};
AssetManager::AssetElements<BasicShader, (Size)AppShader::APP_SHADERS_COUNT> AssetManager::sShaders{};
AssetManager::AssetElements<BasicTexture, (Size)AppTexture::APP_TEXTURES_COUNT> AssetManager::sTextures{};

auto AssetManager::DestroyAssets() -> void
{
    for (auto &mesh : sMeshes)
    {
        auto id = mesh->GetVertexArrayHandle();
        glDeleteVertexArrays(1, &id);
    }

    for (auto &shader : sShaders)
        glDeleteProgram(shader->GetProgramHandle());

    for (auto &texture : sTextures)
    {
        auto id = texture->GetTextureHandle();
        glDeleteTextures(1, &id);
    }
}

auto AssetManager::LoadMeshesAssets() -> void
{
    sMeshes[(Size)AppMesh::UNIT_QUAD] = UnitQuadMeshLoader::GenerateMesh();
    sMeshes[(Size)AppMesh::PLANET] = PlanetMeshLoader::GenerateMesh();
    sMeshes[(Size)AppMesh::SKYBOX] = SkyboxMeshLoader::GenerateMesh();
}

auto AssetManager::LoadShadersAssets() -> void
{
    sShaders[(Size)AppShader::LOADING_SCREEN] = LoadingScreenShaderLoader::GenerateShader();
    sShaders[(Size)AppShader::PLANET] = PlanetShaderLoader::GenerateShader();
    sShaders[(Size)AppShader::SKYBOX] = SkyboxShaderLoader::GenerateShader();
}

auto AssetManager::LoadTextureAssets() -> void
{
    static const uint8_t NOT_FOUND_DATA[] =
        {1, 0, 1, 1,
         0, 0, 0, 1,
         1, 0, 1, 1,
         0, 0, 0, 0};

    sTextures[(Size)AppTexture::NOT_FOUND] = StandardTextureLoader::GenerateTexture(NOT_FOUND_DATA, 2, 2, 4);
    sTextures[(Size)AppTexture::DEMO] = StandardTextureLoader::GenerateTexture("stone");
    sTextures[(Size)AppTexture::SKYBOX] = CubemapTextureLoader::GenerateTexture("skybox");
}

auto AssetManager::GetMesh(AppMesh mesh) -> const BasicMesh &
{
    return *sMeshes[(Size)mesh].get();
}

auto AssetManager::GetShader(AppShader shader) -> const BasicShader &
{
    return *sShaders[(Size)shader].get();
}

auto AssetManager::GetTexture(AppTexture texture) -> const BasicTexture &
{
    const auto &texture_ref = sTextures[(Size)texture];
    if (texture_ref)
        return *texture_ref.get();
    return *sTextures[(Size)AppTexture::NOT_FOUND].get();
}