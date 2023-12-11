package model;

import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.ArrayList;
import java.util.List;

import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL15;

public class Model_ {
	private List<Integer> vbos = new ArrayList<Integer>();

	private int draw_count;
	private int v_id;
	private int t_id;
	private int i_id;

	public Model_(float[] verticies, float[] uvs, int[] indices) {
		draw_count = indices.length;
		v_id = createBufferObject(GL15.GL_ARRAY_BUFFER, verticies);
		t_id = createBufferObject(GL15.GL_ARRAY_BUFFER, uvs);
		i_id = createBufferObject(GL15.GL_ELEMENT_ARRAY_BUFFER, indices);
	}

	private int createBufferObject(int type, float[] data) {
		int id = GL15.glGenBuffers();
		vbos.add(id);
		GL15.glBindBuffer(type, id);
		GL15.glBufferData(type, createFloatBuffer(data), GL15.GL_STATIC_DRAW);
		GL15.glBindBuffer(type, 0);
		return id;
	}

	private int createBufferObject(int type, int[] data) {
		int id = GL15.glGenBuffers();
		vbos.add(id);
		GL15.glBindBuffer(type, id);
		GL15.glBufferData(type, createIntBuffer(data), GL15.GL_STATIC_DRAW);
		GL15.glBindBuffer(type, 0);
		return id;
	}

	private IntBuffer createIntBuffer(int[] data) {
		IntBuffer res = BufferUtils.createIntBuffer(data.length);
		res.put(data);
		res.flip();
		return res;
	}

	private FloatBuffer createFloatBuffer(float[] data) {
		FloatBuffer res = BufferUtils.createFloatBuffer(data.length);
		res.put(data);
		res.flip();
		return res;
	}

	public int getDraw_count() {
		return draw_count;
	}

	public void cleanUp() {
		for (int v : vbos)
			GL15.glDeleteBuffers(v);
	}
}
