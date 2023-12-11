package shaders.derivatives;

import org.joml.Matrix4f;

import shaders.ShaderProgram;

public class SkyboxShader extends ShaderProgram {
	private int mLocModelMatrix;
	private int mLocViewMatrix;
	private int mLocProjMatrix;

	public SkyboxShader() {
		super("skybox");
	}

	@Override
	protected void bindAttributes() {
		super.bindAttribute(0, "aPos");
	}

	@Override
	protected void getAllUniformLocations() {
		mLocModelMatrix = super.getUniformLocation("model");
		mLocViewMatrix = super.getUniformLocation("view");
		mLocProjMatrix = super.getUniformLocation("proj");

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

}
