package window;

import static org.lwjgl.glfw.GLFW.GLFW_KEY_LAST;
import static org.lwjgl.glfw.GLFW.GLFW_MOUSE_BUTTON_LAST;
import static org.lwjgl.glfw.GLFW.glfwGetKey;
import static org.lwjgl.glfw.GLFW.glfwGetMouseButton;

import org.joml.Vector2f;
import org.lwjgl.glfw.GLFW;
import org.lwjgl.glfw.GLFWCursorPosCallback;
import org.lwjgl.glfw.GLFWKeyCallback;
import org.lwjgl.glfw.GLFWScrollCallback;

public class Keyboard {
	private long mWindowHandle;
	private int mWindowWidth, mWindowHeight;

	private boolean mKeyboardKeys[];
	private boolean mMouseButtons[];
	private float mMouseScrollStatus;
	private boolean mMouseCaptured;

	private Vector2f mMousePosition;
	private Vector2f mRelMousePosition;

	public Keyboard(long window) {
		this.mWindowHandle = window;
		reloadWindowDimensions();

		this.mKeyboardKeys = new boolean[GLFW_KEY_LAST];
		this.mMouseButtons = new boolean[GLFW_MOUSE_BUTTON_LAST];
		for (int i = 0; i < GLFW_KEY_LAST; i++)
			mKeyboardKeys[i] = false;
		this.mMouseScrollStatus = 0;
		this.mMouseCaptured = true;
		this.mMousePosition = new Vector2f();
		this.mRelMousePosition = new Vector2f();

		// setting up keyboard
		GLFW.glfwSetKeyCallback(window, new GLFWKeyCallback() {

			@Override
			public void invoke(long window, int key, int scancode, int action,
					int mods) {
				if (action == GLFW.GLFW_PRESS) {
					if (key == GLFW.GLFW_KEY_ESCAPE)
						System.exit(0);

					if (key == GLFW.GLFW_KEY_RIGHT_CONTROL) {
						mMouseCaptured = !mMouseCaptured;
						GLFW.glfwSetInputMode(window, GLFW.GLFW_CURSOR,
								mMouseCaptured ? GLFW.GLFW_CURSOR_DISABLED
										: GLFW.GLFW_CURSOR_NORMAL);
					}
				}
			}

		});

		// setting up button
		GLFW.glfwSetInputMode(window, GLFW.GLFW_CURSOR,
				GLFW.GLFW_CURSOR_DISABLED);

		if (GLFW.glfwRawMouseMotionSupported())
			GLFW.glfwSetInputMode(window, GLFW.GLFW_RAW_MOUSE_MOTION,
					GLFW.GLFW_TRUE);
		GLFW.glfwSetCursorPosCallback(window, new GLFWCursorPosCallback() {

			@Override
			public void invoke(long window, double xpos, double ypos) {
				xpos -= mWindowWidth * 0.5f;
				ypos -= mWindowHeight * 0.5f;

				mRelMousePosition.x = (float) (xpos - mMousePosition.x);
				mRelMousePosition.y = (float) (ypos - mMousePosition.y);

				mMousePosition.x = (float) xpos;
				mMousePosition.y = (float) ypos;

			}
		});
		
		GLFW.glfwSetScrollCallback(window, new GLFWScrollCallback() {
			
			@Override
			public void invoke(long window, double xoffset, double yoffset) {
				mMouseScrollStatus = (float) yoffset;
				
			}
		});

	}

	public void reloadWindowDimensions() {
		int w[] = { 0 };
		int h[] = { 0 };

		GLFW.glfwGetWindowSize(mWindowHandle, w, h);

		this.mWindowWidth = w[0];
		this.mWindowHeight = h[0];
	}
	
	public float getMouseScrollStatus() {
		float result = this.mMouseScrollStatus;
		this.mMouseScrollStatus = 0;
		return result;
	}

	public boolean isKeyDown(int key) {
		return glfwGetKey(mWindowHandle, key) == 1;
	}

	public boolean isKeyPressed(int key) {
		return (isKeyDown(key) && !mKeyboardKeys[key]);
	}

	public boolean isKeyReleased(int key) {
		return (!isKeyDown(key) && mKeyboardKeys[key]);
	}

	public boolean isMouseButtonDown(int b) {
		return glfwGetMouseButton(mWindowHandle, b) == 1;
	}

	public boolean isMouseButtonPressed(int b) {
		return (isMouseButtonDown(b) && !mMouseButtons[b]);
	}

	public boolean isMouseButtonReleased(int b) {
		return (!isMouseButtonDown(b) && mMouseButtons[b]);
	}

	public Vector2f getMousePosition() {
		return mMousePosition;
	}

	public Vector2f getRelativeMousePosition() {
		Vector2f result = new Vector2f();
		result.x = mRelMousePosition.x;
		result.y = mRelMousePosition.y;
		mRelMousePosition.x = 0;
		mRelMousePosition.y = 0;
		return result;
	}

	public void update() {
		for (int i = 0; i < GLFW_KEY_LAST; i++)
			mKeyboardKeys[i] = isKeyDown(i);
		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
			mMouseButtons[i] = isMouseButtonDown(i);
	}

}
