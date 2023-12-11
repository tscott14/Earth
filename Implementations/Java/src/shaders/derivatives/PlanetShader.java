package shaders.derivatives;

import org.joml.Matrix4f;

import camera.OrbitalCamera;
import shaders.ShaderProgram;
import world.Star;

public class PlanetShader extends ShaderProgram {
	private int mLocModelMatrix;
	private int mLocViewMatrix;
	private int mLocProjMatrix;
	
	
	private int mLocSunDirection;
	private int mLocSunColor;

	private int mLocAlbetoSampler;
	private int mLocSpecularSampler;
	private int mLocNormalSampler;

	public PlanetShader() {
		super("planet");
	}

	@Override
	protected void bindAttributes() {
		super.bindAttribute(0, "aPos");
		super.bindAttribute(1, "aTexCoords");
		super.bindAttribute(2, "aTangent");
		super.bindAttribute(3, "aBitangent");
		super.bindAttribute(4, "aNormal");
	}

	@Override
	protected void getAllUniformLocations() {
		mLocModelMatrix = super.getUniformLocation("uModel");
		mLocViewMatrix = super.getUniformLocation("uView");
		mLocProjMatrix = super.getUniformLocation("uProj");

		mLocSunDirection = super.getUniformLocation("uSunDirection");
		mLocSunColor = super.getUniformLocation("uSunColor");

		mLocAlbetoSampler = super.getUniformLocation("uAlbetoTextureSampler");
		mLocSpecularSampler = super.getUniformLocation("uSpecularTextureSampler");
		mLocNormalSampler = super.getUniformLocation("uNormalTextureSampler");
	}

	public void loadModelMatrix(Matrix4f matrix) {
		super.setUniformMat4x4(mLocModelMatrix, matrix);
	}

	public void loadViewMatrix(Matrix4f matrix) {
		super.setUniformMat4x4(mLocViewMatrix, matrix);

	}

	public void loadProjectionMatrix(Matrix4f matrix) {
		super.setUniformMat4x4(mLocProjMatrix, matrix);
	}

	public void loadCamera(OrbitalCamera camera) {
		//super.setUniformVec3f(mLocCameraPosition, camera.getCameraPosition());
	}

	public void loadStar(Star sun) {
		super.setUniformVec3f(mLocSunDirection, sun.getDirection());
		super.setUniformVec3f(mLocSunColor, sun.getColor());
	}

	public void loadTextures() {
		super.setUniform1i(mLocAlbetoSampler, 0);
		super.setUniform1i(mLocSpecularSampler, 1);
		super.setUniform1i(mLocNormalSampler, 2);
	}
}
