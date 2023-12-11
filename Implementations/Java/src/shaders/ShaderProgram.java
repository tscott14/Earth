package shaders;

import java.nio.FloatBuffer;

import org.joml.Matrix4f;
import org.joml.Vector2f;
import org.joml.Vector3f;
import org.joml.Vector4f;
import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL20;

public abstract class ShaderProgram {
	private int mProgramHandle;
	private int mVertexShaderHandle, mFragmentShaderHandle;
	
	private static ShaderReader mShaderReader = new ShaderReader();

	public ShaderProgram(String path) {
		String shaders[] = mShaderReader.loadShaders(path);
		
		String vert_src = shaders[0];
		String frag_src = shaders[1];
		
		mVertexShaderHandle = loadShader(vert_src, GL20.GL_VERTEX_SHADER);
		mFragmentShaderHandle = loadShader(frag_src, GL20.GL_FRAGMENT_SHADER);

		mProgramHandle = GL20.glCreateProgram();

		GL20.glAttachShader(mProgramHandle, mVertexShaderHandle);
		GL20.glAttachShader(mProgramHandle, mFragmentShaderHandle);

		bindAttributes();

		GL20.glLinkProgram(mProgramHandle);
		if (GL20.glGetProgrami(mProgramHandle, GL20.GL_LINK_STATUS) == 0) {
			{
				System.err.println("Error linking Shader code: "
						+ GL20.glGetProgramInfoLog(mProgramHandle, 1024));
			}
		}

		GL20.glDetachShader(mProgramHandle, mVertexShaderHandle);
		GL20.glDetachShader(mProgramHandle, mFragmentShaderHandle);
		GL20.glDeleteShader(mVertexShaderHandle);
		GL20.glDeleteShader(mFragmentShaderHandle);

		GL20.glValidateProgram(mProgramHandle);
		if (GL20.glGetProgrami(mProgramHandle, GL20.GL_VALIDATE_STATUS) == 0) {
			System.err.println("Warning validating Shader code: "
					+ GL20.glGetProgramInfoLog(mProgramHandle, 1024));
		}

		getAllUniformLocations();
	}

	protected int getUniformLocation(String name) {
		int res = GL20.glGetUniformLocation(mProgramHandle, name);
		if (res == -1) {
			System.err.println("Could not find uniform! (" + name + ")");
			System.exit(1);
		}
		return res;
	}

	public void setUniform1i(int location, int value) {
		GL20.glUniform1i(location, value);
	}

	public void setUniform1f(int location, float value) {
		GL20.glUniform1f(location, value);
	}

	public void setUniformMat4x4(int location, Matrix4f value) {
		FloatBuffer buffer = BufferUtils.createFloatBuffer(4 * 4);
		value.get(buffer);
		GL20.glUniformMatrix4fv(location, false, buffer);
	}

	public void setUniformVec2f(int location, Vector2f value) {
		GL20.glUniform2f(location, value.x, value.y);
	}

	public void setUniformVec3f(int location, Vector3f value) {
		GL20.glUniform3f(location, value.x, value.y, value.z);
	}
	
	public void setUniformVec3f(int location, Vector4f value) {
		GL20.glUniform4f(location, value.x, value.y, value.z,value.w);
	}

	public void start() {
		GL20.glUseProgram(mProgramHandle);
	}

	public void stop() {
		GL20.glUseProgram(0);
	}

	public void cleanUp() {
		stop();
		GL20.glDeleteProgram(mProgramHandle);
	}

	protected abstract void bindAttributes();

	protected abstract void getAllUniformLocations();

	protected void bindAttribute(int attrib, String variableName) {
		GL20.glBindAttribLocation(mProgramHandle, attrib, variableName);
	}

	private int loadShader(String src, int type) {
		int id = GL20.glCreateShader(type);
		GL20.glShaderSource(id, src);
		GL20.glCompileShader(id);
		if (GL20.glGetShaderi(id, GL20.GL_COMPILE_STATUS) != GL11.GL_TRUE) {
			System.out.println(GL20.glGetShaderInfoLog(id, 500));
			System.err.println("Could not compile shader! " + src);
			System.exit(1);
		}
		return id;
	}

}
