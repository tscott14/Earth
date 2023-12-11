package world;

import org.joml.Vector2f;
import org.lwjgl.glfw.GLFW;

import camera.OrbitalCamera;
import render.Renderer;
import system.SPSystem;

public class Scene {
	// private FreeCamera mFreeCamera;
	private OrbitalCamera mOrbitalCamera;

	private Planet mPlanet;
	private Star mSun;
	private Skybox mSkybox;

	public Scene() {
		this.mOrbitalCamera = new OrbitalCamera(SPSystem.getWindow().getWidth(),
				SPSystem.getWindow().getHeight(), 70.0f);

		this.mPlanet = new Planet();
		this.mSun = new Star();
		this.mSkybox = new Skybox();
	}

	public OrbitalCamera getOrbitalCamera() {
		return mOrbitalCamera;
	}

	public Skybox getSkybox() {
		return mSkybox;
	}

	public Planet getPlanet() { 
		return mPlanet;
	}

	public Star getSun() {
		return mSun;
	}

	public void update() {

		mOrbitalCamera.updateCameraOrbitalPosition(SPSystem.getKeyboard().getMouseScrollStatus(), 0, 0);

		if (SPSystem.getKeyboard().isKeyDown(GLFW.GLFW_KEY_J)) {
			mOrbitalCamera.updateCameraOrbitalPosition(0, -1, 0);
		}
		if (SPSystem.getKeyboard().isKeyDown(GLFW.GLFW_KEY_L)) {
			mOrbitalCamera.updateCameraOrbitalPosition(0, 1, 0);
		}
		if (SPSystem.getKeyboard().isKeyDown(GLFW.GLFW_KEY_K)) {
			mOrbitalCamera.updateCameraOrbitalPosition(0, 0, 1);
		}
		if (SPSystem.getKeyboard().isKeyDown(GLFW.GLFW_KEY_I)) {
			mOrbitalCamera.updateCameraOrbitalPosition(0, 0, -1);
		}

		if (SPSystem.getKeyboard().isMouseButtonDown(GLFW.GLFW_MOUSE_BUTTON_LEFT)) {
			Vector2f dm = SPSystem.getKeyboard().getRelativeMousePosition();
			mOrbitalCamera.updateCameraOrbitalPosition(0, dm.x, -dm.y);
		}

		mPlanet.update();
		mSun.update();
	}
	
	public void render() {

		Renderer.renderSkybox(mSkybox, mOrbitalCamera);
		Renderer.renderPlanet(mPlanet, mSun, mOrbitalCamera);
		//Renderer.renderClouds(mPlanet, mSun, mOrbitalCamera);
	}
}
