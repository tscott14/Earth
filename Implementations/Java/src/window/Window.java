package window;

import org.lwjgl.glfw.GLFW;
import org.lwjgl.glfw.GLFWErrorCallback;
import org.lwjgl.opengl.GL;
import org.lwjgl.opengl.GL11;

public class Window {
	private long mWindowHandle;

	private String mTitle;
	private int mWidth, mHeight;

	public long createWindow(final String title, final int width, final int height) {
		this.mTitle = title;
		this.mWidth = width;
		this.mHeight = height;

		//System.out.printf("Creating Window with size [%d, %d].", width,height);
		
		GLFW.glfwWindowHint(GLFW.GLFW_VISIBLE, GLFW.GLFW_FALSE);

		this.mWindowHandle = GLFW.glfwCreateWindow(width, height, title, 0, 0);

		if (mWindowHandle == 0)
			throw new IllegalStateException("Failed to create window!");
		
		GLFW.glfwShowWindow(mWindowHandle);

		GLFW.glfwMakeContextCurrent(mWindowHandle);

		GLFW.glfwSwapBuffers(mWindowHandle);

		GL.createCapabilities();
		
		GL11.glViewport(0, 0, width, height);

		GL11.glClear(GL11.GL_COLOR_BUFFER_BIT | GL11.GL_DEPTH_BUFFER_BIT);

		return this.mWindowHandle;
	}

	public boolean shouldClose() {
		return GLFW.glfwWindowShouldClose(mWindowHandle);
	}

	public void swapBuffers() {
		GLFW.glfwSwapBuffers(mWindowHandle);
	}

	public void update() {
		GLFW.glfwPollEvents();
	}

	public void setSize(int width, int height) {
		this.mWidth = width;
		this.mHeight = height;
	}

	public int getWidth() {
		return mWidth;
	}

	public int getHeight() {
		return mHeight;
	}

	public long getWindowID() {
		return mWindowHandle;
	}

	public String getTitle() {
		return mTitle;
	}

	public void setTitle(String title) {
		this.mTitle = title;
	}

	public static void setCallbacks() {
		GLFW.glfwSetErrorCallback(GLFWErrorCallback.createPrint(System.err));
	}

}
