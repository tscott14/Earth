package shaders.derivatives;

import org.joml.Matrix4f;

import shaders.ShaderProgram;

public class Basic3DShader extends ShaderProgram {
	private int mLocTrandformationMatrix;
	
	public Basic3DShader() {
		super("error");
	}

	@Override
	protected void bindAttributes() {
		super.bindAttribute(0, "positions");
		super.bindAttribute(1, "textureCoordnates");
	}

	@Override
	protected void getAllUniformLocations() {
		this.mLocTrandformationMatrix = super.getUniformLocation("transformation");
		
	}
	
	public void loadTransformationMatrix(Matrix4f matrix) {
		super.setUniformMat4x4(mLocTrandformationMatrix, matrix);
	}

}
