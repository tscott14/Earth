package textures;

public class Texture {
	private final int mTextureHandle;
	private final int mWidth, mHeight;

	public Texture(int textureHandle, int width, int height) {
		super();
		this.mTextureHandle = textureHandle;
		this.mWidth = width;
		this.mHeight = height;
	}

	public int getTextureHandle() {
		return mTextureHandle;
	}

	public int getmWidth() {
		return mWidth;
	}

	public int getmHeight() {
		return mHeight;
	}
}
