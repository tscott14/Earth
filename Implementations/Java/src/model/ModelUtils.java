package model;

import java.nio.FloatBuffer;
import java.nio.IntBuffer;

import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;

public class ModelUtils {
	// List<Integer> vaos = new ArrayList<>();

	public static Mesh loadToMesh(float positions[], int indices[],
			float textureCoordnates[]) {
		int vaoID = createVao();
		bindIndicesBuffer(indices);
		storeDatInAttributeList(0, 3, positions);
		storeDatInAttributeList(1, 2, textureCoordnates);
		unbindVao();
		return new Mesh(vaoID, indices.length);
	}

	private static int createVao() {
		int vaoID = GL30.glGenVertexArrays();
		GL30.glBindVertexArray(vaoID);
		return vaoID;
	}

	private static void storeDatInAttributeList(int attribNumber, int size, float[] data) {
		int vboID = GL15.glGenBuffers();
		GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, vboID);
		FloatBuffer buffer = createFloatBuffer(data);
		GL15.glBufferData(GL15.GL_ARRAY_BUFFER, buffer, GL15.GL_STATIC_DRAW);
		GL20.glVertexAttribPointer(attribNumber, size, GL11.GL_FLOAT, false, 0, 0);
		GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, 0);
	}

	private static void unbindVao() {
		GL30.glBindVertexArray(0);
	}

	private static void bindIndicesBuffer(int indices[]) {
		int vbo = GL15.glGenBuffers();
		GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, vbo);
		IntBuffer buffer = storeDataInIntBuffer(indices);
		GL15.glBufferData(GL15.GL_ELEMENT_ARRAY_BUFFER, buffer,
				GL15.GL_STATIC_DRAW);
	}

	private static FloatBuffer createFloatBuffer(float[] data) {
		FloatBuffer res = BufferUtils.createFloatBuffer(data.length);
		res.put(data);
		res.flip();
		return res;
	}

	private static IntBuffer storeDataInIntBuffer(int[] data) {
		IntBuffer res = BufferUtils.createIntBuffer(data.length);
		res.put(data);
		res.flip();
		return res;
	}
}
