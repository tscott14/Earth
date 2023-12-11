package shaders.derivatives;

import org.joml.Matrix4f;

import shaders.ShaderProgram;
import world.Star;

public class CloudShader extends ShaderProgram {
	private int mLocModelMatrix;
	private int mLocViewMatrix;
	private int mLocProjMatrix;

	private int mLocSunDirection;
	private int mLocSunColor;
	
	private int mLocAlbetoSampler;
	
	public CloudShader() {
		super("clouds");
	}

	@Override
	protected void bindAttributes() {
		super.bindAttribute(0, "positions");
		super.bindAttribute(1, "normals");
		super.bindAttribute(2, "textureCoordnates");
	}

	@Override
	protected void getAllUniformLocations() {
		mLocModelMatrix = super.getUniformLocation("model");
		mLocViewMatrix = super.getUniformLocation("view");
		mLocProjMatrix = super.getUniformLocation("proj");

		mLocSunDirection = super.getUniformLocation("uSunDirection");
		mLocSunColor = super.getUniformLocation("uSunColor");
		
		mLocAlbetoSampler = super.getUniformLocation("uAlbetoTextureSampler");
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
	
	public void loadTextures() {
		super.setUniform1i(mLocAlbetoSampler, 0);
	}

	public void loadStar(Star sun) {
		super.setUniformVec3f(mLocSunDirection, sun.getDirection());
		super.setUniformVec3f(mLocSunColor, sun.getColor());
	}
}
