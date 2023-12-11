package textures;

public class Image {
	public int mTextureData[];
	public int mWidth, mHeight, mChannels;

	public Image(int[] mTextureData, int mWidth, int mHeight, int mChannels) {
		super();
		this.mTextureData = mTextureData;
		this.mWidth = mWidth;
		this.mHeight = mHeight;
		this.mChannels = mChannels;
	}

	public Pixel sample(float x, float y) {
		x *= mWidth;
		y *= mHeight;

		float bx = (int) x;
		float by = (int) y;

		float mx = x - bx;
		float my = y - by;

		Pixel x00 = getPixel(bx + 0, by + 0);
		Pixel y01 = getPixel(bx + 0, by + 1);
		Pixel x10 = getPixel(bx + 1, by + 0);
		Pixel y11 = getPixel(bx + 1, by + 1);
		
		Pixel nx = lerp(x00, x10, mx);
		Pixel ny = lerp(y01, y11, mx);
		Pixel f = lerp(nx, ny, my);
		
		

		return f;
	}
	
	private Pixel lerp(Pixel c1, Pixel c2, float amount) {
		float r = (c1.mR * amount + c2.mR * (1-amount));
		float g = (c1.mG * amount + c2.mG * (1-amount));
		float b = (c1.mB * amount + c2.mB * (1-amount));
		float a = (c1.mA * amount + c2.mA * (1-amount));
		
		Pixel result = new Pixel(r, g, b, a);
		return result;
	}
	
	private Pixel getPixel(float x, float y) {
		float r = mTextureData[(int) (x + y * mWidth + 0)];
		float g = mTextureData[(int) (x + y * mWidth + 1)];
		float b = mTextureData[(int) (x + y * mWidth + 2)];
		float a = mTextureData[(int) (x + y * mWidth + 3)];
		
		Pixel result = new Pixel(r, g, b, a);
		return result;
	}
}
