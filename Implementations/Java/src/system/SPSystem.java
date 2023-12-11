package system;

import window.Keyboard;
import window.Window;

public abstract class SPSystem {
	private static Window mWindow;
	private static Keyboard mKeyboard;

	// private ShaderManager mShaderManager;
	// private TextureManager mTextureManager;

	public static void update() {
		mWindow.update();
		mKeyboard.update();
	}

	public static Window getWindow() {
		if (mWindow == null) {
			System.err.println("Must setup window first!");
			System.exit(1);
		}
		return mWindow;
	}

	public static void createWindow(final String title, final int width, final int height) {
		mWindow = new Window();
		final long windowHandle = mWindow.createWindow(title, width, height);
		setupKeyboard(windowHandle);
	}

	public static Keyboard getKeyboard() {
		if (mWindow == null) {
			System.err.println("Window MUST be created before using Keyboard!");
			System.exit(1);
		}
		if (mKeyboard == null) {
			System.err.println("Keyboard MUST be created!");
		}
		return mKeyboard;
	}

	private static void setupKeyboard(final long windowHandle) {
		if (mKeyboard == null)
			mKeyboard = new Keyboard(windowHandle);
	}
}
