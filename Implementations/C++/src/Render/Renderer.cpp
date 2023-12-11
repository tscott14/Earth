#include "Renderer.hpp"

#include <GL/glew.h>

auto Renderer::RenderPlanet(Planet &planet, OrbitalCamera &camera) -> void
{
    auto &mesh = AssetManager::GetMesh(AppMesh::PLANET);
    auto &shader = AssetManager::GetShader(AppShader::PLANET);
    auto &texture = AssetManager::GetTexture(AppTexture::DEMO);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    mesh.Bind();
    shader.Bind();

    glm::mat4 model = planet.GenerateModelMatrix();
    shader.LoadMatrix4("uModelMatrix", model);
    shader.LoadMatrix4("uViewMatrix", camera.GetViewMatrix());
    shader.LoadMatrix4("uProjMatrix", camera.GetProjMatrix());
    shader.LoadMatrix4("uReverse_ModelMatrix", glm::inverse(model));
    shader.LoadFloat3("uCameraPosition", camera.GenerateCartesianPosition());
    shader.LoadInt("mAlbetoSampler", 0);

    texture.Bind(0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //printf("ID: %d, Length %d\n", mesh.GetVertexArrayHandle(), mesh.GetLength());

    glPointSize(12);
    glPolygonMode(GL_FRONT_AND_BACK, GL_QUADS);
    glDrawElements(GL_PATCHES, mesh.GetLength(), GL_UNSIGNED_INT, NULL);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    shader.Unbind();
    mesh.Unbind();
}

auto Renderer::RenderSkybox(Skybox &skybox, OrbitalCamera &camera) -> void
{
    auto &mesh = AssetManager::GetMesh(AppMesh::SKYBOX);
    auto &shader = AssetManager::GetShader(AppShader::SKYBOX);
    auto &texture = AssetManager::GetTexture(AppTexture::SKYBOX);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader.Bind();
    mesh.Bind();

    glm::mat4 view_without_translation = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    shader.LoadMatrix4("uViewMatrix", view_without_translation);
    shader.LoadMatrix4("uProjMatrix", camera.GetProjMatrix());
    shader.LoadInt("mAlbetoSampler", 0);

    texture.Bind(0);

    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, mesh.GetLength());
    glDisableVertexAttribArray(0);

    shader.Unbind();
    mesh.Unbind();
}

auto Renderer::RenderUI() -> void
{
}