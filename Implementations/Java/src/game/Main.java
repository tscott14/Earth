package game;

import static org.lwjgl.glfw.GLFW.glfwInit;
import static org.lwjgl.glfw.GLFW.glfwTerminate;

import render.Renderer;
import shaders.ShaderManager;
import shaders.ShaderProgram;
import system.SPSystem;
import window.Window;
import world.Scene;

/*
 * TODO: Smoother camera movement
 * TODO: motion blur
 * TODO: Clouds
 * TODO: normals
 * TODO: ~~Displacement Maps~~
 */

public class Main {

	public static final int WIDTH = 720 * 2;
	public static final int HEIGHT = WIDTH * 9 / 16;

	public static void main(String[] args) {
		if (!glfwInit()) {
			throw new RuntimeException("Could not init GLFW!");
		}

		SPSystem.createWindow("SP2", WIDTH, HEIGHT);
		Window window = SPSystem.getWindow();
 
		{@SuppressWarnings("unused") ShaderProgram s = ShaderManager.mPlanetShader;}
		
		Scene mainScene = new Scene();

		Renderer.setup();
		
		
		while (!window.shouldClose()) {
			Renderer.prepare();

			mainScene.render();

			mainScene.update();

			SPSystem.update();
			window.swapBuffers();
		}

		glfwTerminate();

	}

}
