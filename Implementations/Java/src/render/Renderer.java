package render;

import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL13;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;

import camera.OrbitalCamera;
import model.Mesh;
import model.Model;
import shaders.ShaderManager;
import shaders.derivatives.CloudShader;
import shaders.derivatives.PlanetShader;
import shaders.derivatives.SkyboxShader;
import textures.SkyboxTexture;
import textures.Texture;
import world.Planet;
import world.Skybox;
import world.Star;

public abstract class Renderer {
	public static void setup() {
		GL11.glEnable(GL11.GL_DEPTH_TEST);
		GL11.glEnable(GL11.GL_CULL_FACE);

		GL11.glClearColor(0.7f, 0.3f, 0.7f, 1.0f);
		GL11.glCullFace(GL11.GL_BACK);
	}

	public static void prepare() {
		GL11.glClear(GL11.GL_COLOR_BUFFER_BIT | GL11.GL_DEPTH_BUFFER_BIT);
	}

	public static void render(Model model) {
		Mesh mesh = model.getMesh();
		Texture texture = model.getTexture();
		// Basic3DShader shader = ShaderManager.mShader3D;

		// Matrix4f transformation = MatrixMaths.createTransformationMatrix(
		// new Vector3f(1, 0, 0), new Vector3f(0, 0, 0), 1.0f);

		// System.out.println(transformation);

		// shader.start();
		// shader.loadTransformationMatrix(transformation);

		GL30.glBindVertexArray(mesh.getVertexArrayObjectHandle());
		GL20.glEnableVertexAttribArray(0);
		GL20.glEnableVertexAttribArray(1);

		GL13.glActiveTexture(GL13.GL_TEXTURE0);
		GL11.glBindTexture(GL11.GL_TEXTURE_2D, texture.getTextureHandle());

		GL11.glDrawElements(GL11.GL_TRIANGLES, mesh.getVertexCount(),
				GL11.GL_UNSIGNED_INT, 0);
		GL20.glDisableVertexAttribArray(0);
		GL20.glDisableVertexAttribArray(1);
		GL30.glBindVertexArray(0);
		// ShaderManager.mShader3D.stop();
	}

	public static void renderPlanet(Planet planet, Star sun,
			OrbitalCamera camera) {
		PlanetShader shader = ShaderManager.mPlanetShader;
		Mesh mesh = planet.getPlanetMesh();
		Texture albeto = planet.getPlanetAlbetoTexture();
		Texture specular = planet.getPlanetSpecularTexture();
		Texture normal = planet.getPlanetNormalTexture();


		shader.start();

		GL30.glBindVertexArray(mesh.getVertexArrayObjectHandle());
		GL20.glEnableVertexAttribArray(0);
		GL20.glEnableVertexAttribArray(1);
		GL20.glEnableVertexAttribArray(2);
		GL20.glEnableVertexAttribArray(3);
		GL20.glEnableVertexAttribArray(4);

		shader.loadModelMatrix(planet.getCloudsModelMatrix());
		shader.loadViewMatrix(camera.getCameraViewMatrix());
		shader.loadProjectionMatrix(camera.getCameraProjectionMatrix());

		shader.loadStar(sun);
		shader.loadTextures();

		GL13.glActiveTexture(GL13.GL_TEXTURE0);
		GL11.glBindTexture(GL11.GL_TEXTURE_2D, albeto.getTextureHandle());
		GL13.glActiveTexture(GL13.GL_TEXTURE1);
		GL11.glBindTexture(GL11.GL_TEXTURE_2D, specular.getTextureHandle());
		GL13.glActiveTexture(GL13.GL_TEXTURE2);
		GL11.glBindTexture(GL11.GL_TEXTURE_2D, normal.getTextureHandle());

		GL11.glDrawElements(GL11.GL_TRIANGLES, mesh.getVertexCount(),
				GL11.GL_UNSIGNED_INT, 0);
		
		
		GL20.glDisableVertexAttribArray(0);
		GL20.glDisableVertexAttribArray(1);
		GL20.glDisableVertexAttribArray(2);
		GL20.glDisableVertexAttribArray(3);
		GL20.glDisableVertexAttribArray(4);
		GL30.glBindVertexArray(0);

		shader.stop();
	}
	
	public static void renderClouds(Planet planet, Star sun, OrbitalCamera camera) {
		CloudShader shader = ShaderManager.mCloudShader;
		Mesh mesh = planet.getPlanetMesh();
		Texture clouds = planet.getPlanetCloudsTexture();

		GL11.glEnable(GL11.GL_DEPTH_TEST);
		GL11.glEnable(GL11.GL_BLEND);
		GL11.glBlendFunc(GL11.GL_SRC_ALPHA, GL11.GL_ONE_MINUS_SRC_ALPHA);
		
		shader.start();

		GL30.glBindVertexArray(mesh.getVertexArrayObjectHandle());
		GL20.glEnableVertexAttribArray(0);
		GL20.glEnableVertexAttribArray(1);
		GL20.glEnableVertexAttribArray(2);

		shader.loadStar(sun);
		shader.loadTextures();

		shader.loadModelMatrix(planet.getPlanetModelMatrix());
		shader.loadViewMatrix(camera.getCameraViewMatrix());
		shader.loadProjectionMatrix(camera.getCameraProjectionMatrix());

		GL13.glActiveTexture(GL13.GL_TEXTURE0);
		GL11.glBindTexture(GL11.GL_TEXTURE_2D, clouds.getTextureHandle());

		GL11.glDrawElements(GL11.GL_TRIANGLES, mesh.getVertexCount(),
				GL11.GL_UNSIGNED_INT, 0);
		
		
		GL20.glDisableVertexAttribArray(0);
		GL20.glDisableVertexAttribArray(1);
		GL20.glDisableVertexAttribArray(2);
		GL30.glBindVertexArray(0);

		shader.stop();
	}

	public static void renderSkybox(Skybox sb, OrbitalCamera camera) {
		SkyboxShader shader = ShaderManager.mSkyboxShader;
		Mesh mesh = sb.getSkyboxMesh();
		SkyboxTexture t0 = sb.getSkyboxTexture();

		// System.out.println(t0.getTextureHandle());
		GL11.glDepthFunc(GL11.GL_LEQUAL);
		GL11.glDepthMask(false);

		shader.start();

		shader.loadModelMatrix(sb.getModelMatrix()); // Mostly unused
		shader.loadViewMatrix(camera.getCameraRotationMatrix());
		shader.loadProjectionMatrix(camera.getCameraProjectionMatrix());

		GL30.glBindVertexArray(mesh.getVertexArrayObjectHandle());
		GL20.glEnableVertexAttribArray(0);

		GL13.glActiveTexture(GL13.GL_TEXTURE0);
		GL11.glBindTexture(GL15.GL_TEXTURE_CUBE_MAP, t0.getTextureHandle());

		GL11.glDrawArrays(GL11.GL_TRIANGLES, 0, mesh.getVertexCount());

		GL20.glDisableVertexAttribArray(0);
		GL30.glBindVertexArray(0);

		shader.stop();

		GL11.glDepthMask(true);
		GL11.glDepthFunc(GL11.GL_LESS);
	}
}
