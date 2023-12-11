#include "EarthViewer.hpp"
#include "Assets/AssetManager.hpp"

/*
	- Maintence
	- Asset Manager
	- Frame Buffers
	- Normals
	- Skybox
*/

#include <glm/gtc/matrix_transform.hpp>
#include "Assets/AssetLoaders/TextureLoaders/TextureLoaders.hpp"
auto SplashLoadingScreen() -> void
{
	auto &mesh = AssetManager::GetMesh(AppMesh::UNIT_QUAD);
	auto &shader = AssetManager::GetShader(AppShader::LOADING_SCREEN);
	auto texture = StandardTextureLoader::GenerateTexture("icon");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Bind();
	mesh.Bind();

	const auto dis = DisplayManager::GetDisplay();
	const auto dim = dis.GetSize();

	const auto hwidth = dim.mWidth * 0.5f;
	const auto hheight = dim.mHeight * 0.5f;

	shader.LoadMatrix4("uModel", glm::scale(glm::mat4(1.0f), glm::vec3(120, 120, 120)));
	shader.LoadMatrix4("uProj", glm::ortho(-hwidth, hwidth, -hheight, hheight));
	shader.LoadInt("mTextureSampler", 0);

	texture->Bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glPointSize(20);
	glDrawArrays(GL_TRIANGLES, 0, mesh.GetLength());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	texture->Unbind();
	shader.Unbind();
	mesh.Unbind();

	glfwSwapBuffers(DisplayManager::GetDisplay().GetWindowHandle());

	auto handle = texture->GetTextureHandle();
	glDeleteTextures(1, &handle);
}

auto main() -> int
{
	GLFWLoader::Initialize();
	Ref<Display> display = DisplayManager::MakeDisplay(720, 480, "EarthViewer");

	GLEWLoader::Initialize();
	GLEWLoader::SetPatchVertices(4);

	AssetManager::LoadMeshesAssets();
	AssetManager::LoadShadersAssets();

	SplashLoadingScreen();

	AssetManager::LoadTextureAssets();

	EarthViewer game;
	DisplayManager::SetEventHandler(
		[&game](Event &event) -> void
		{
			game.HandleEvent(event);
		});
	double previous = glfwGetTime();
	while (!display->ShouldClose())
	{
		double current = glfwGetTime();
		display->Clear();

		game.Update((Timestep)(current - previous));
		game.Render();

		display->Update();
		previous = current;
	}

	AssetManager::DestroyAssets();

	return 0;
}
