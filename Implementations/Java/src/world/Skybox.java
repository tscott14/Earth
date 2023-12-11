package world;

import org.joml.Matrix4f;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;

import model.Mesh;
import render.MatrixMaths;
import textures.SkyboxTexture;
import textures.TextureManager;

public class Skybox {
	private Mesh mSkyboxMesh;
	private SkyboxTexture mSkyboxTexture;

	public Skybox() {
		final float skyboxVertices[] = {
				// positions
				-1.0f, 1.0f, -1.0f, //
				-1.0f, -1.0f, -1.0f, //
				1.0f, -1.0f, -1.0f, //
				1.0f, -1.0f, -1.0f, //
				1.0f, 1.0f, -1.0f, //
				-1.0f, 1.0f, -1.0f, //

				-1.0f, -1.0f, 1.0f, //
				-1.0f, -1.0f, -1.0f, //
				-1.0f, 1.0f, -1.0f, //
				-1.0f, 1.0f, -1.0f, //
				-1.0f, 1.0f, 1.0f, //
				-1.0f, -1.0f, 1.0f, //

				1.0f, -1.0f, -1.0f, //
				1.0f, -1.0f, 1.0f, //
				1.0f, 1.0f, 1.0f, //
				1.0f, 1.0f, 1.0f, //
				1.0f, 1.0f, -1.0f, //
				1.0f, -1.0f, -1.0f, //

				-1.0f, -1.0f, 1.0f, //
				-1.0f, 1.0f, 1.0f, //
				1.0f, 1.0f, 1.0f, //
				1.0f, 1.0f, 1.0f, //
				1.0f, -1.0f, 1.0f, //
				-1.0f, -1.0f, 1.0f, //

				-1.0f, 1.0f, -1.0f, //
				1.0f, 1.0f, -1.0f, //
				1.0f, 1.0f, 1.0f, //
				1.0f, 1.0f, 1.0f, //
				-1.0f, 1.0f, 1.0f, //
				-1.0f, 1.0f, -1.0f, //

				-1.0f, -1.0f, -1.0f, //
				-1.0f, -1.0f, 1.0f, //
				1.0f, -1.0f, -1.0f, //
				1.0f, -1.0f, -1.0f, //
				-1.0f, -1.0f, 1.0f, //
				1.0f, -1.0f, 1.0f //
		};

		final int vaoID = GL30.glGenVertexArrays();
		GL30.glBindVertexArray(vaoID);
		
		{ // Load in verticies array.
			int vboID = GL15.glGenBuffers();
			GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, vboID);

			GL15.glBufferData(GL15.GL_ARRAY_BUFFER, skyboxVertices,
					GL15.GL_STATIC_DRAW);
			GL20.glVertexAttribPointer(0, 3, GL11.GL_FLOAT, false, 0, 0);

			GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, 0);
		}
		
		GL30.glBindVertexArray(0);

		this.mSkyboxMesh = new Mesh(vaoID, skyboxVertices.length / 3);
		this.mSkyboxTexture = TextureManager.mCubeMapTexture;
	}

	public Matrix4f getModelMatrix() {
		return MatrixMaths.createCubeMapTransformationMatrix(0, 0, 0);
	}

	public SkyboxTexture getSkyboxTexture() {
		return mSkyboxTexture;
	}

	public void setSkyboxTexture(SkyboxTexture cubeMapTexture) {
		this.mSkyboxTexture = cubeMapTexture;
	}

	public Mesh getSkyboxMesh() {
		return mSkyboxMesh;
	}

}
