package textures;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL14;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL30;

public abstract class TextureUtils {
	public static Image loadImageFromFile(String path) {
		BufferedImage bi;
		try {
			bi = ImageIO.read(new File("./res/textures/" + path));
		} catch (IOException e) {
			System.out.println(
					"Unable to load texture: " + "./res/textures/" + path);
			e.printStackTrace();
			return null; 
		}

		int width = bi.getWidth();
		int height = bi.getHeight();

		int[] pixels_raw = new int[width * height];
		bi.getRGB(0, 0, width, height, pixels_raw, 0, width);

		return new Image(pixels_raw, width, height, 4);
	}

	public static Texture loadTexture(String path, boolean smooth,
			boolean mipmap) { 

		Image img = loadImageFromFile(path);

		int textureHandle = createTexture(img.mTextureData, img.mWidth,
				img.mHeight, smooth, mipmap);

		return new Texture(textureHandle, img.mWidth, img.mHeight);

	}

	public static SkyboxTexture loadCubeMapTexture(final boolean smooth) {

		final int id = GL15.glGenTextures();
		GL15.glBindTexture(GL15.GL_TEXTURE_CUBE_MAP, id);

		for (int i = 0; i < 6; i++) {
			String currentPath = "background_debug/panorama_" + i + ".png";

			Image img = loadImageFromFile(currentPath);

			GL15.glTexImage2D(GL15.GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
					GL15.GL_RGBA, img.mWidth, img.mHeight, 0, GL15.GL_BGRA,
					GL11.GL_UNSIGNED_BYTE, img.mTextureData);

			if (smooth) {
				GL15.glTexParameteri(GL15.GL_TEXTURE_CUBE_MAP,
						GL15.GL_TEXTURE_MAG_FILTER, GL15.GL_LINEAR);
				GL15.glTexParameteri(GL15.GL_TEXTURE_CUBE_MAP,
						GL15.GL_TEXTURE_MIN_FILTER, GL15.GL_LINEAR);
			} else {
				GL15.glTexParameteri(GL15.GL_TEXTURE_CUBE_MAP,
						GL15.GL_TEXTURE_MAG_FILTER, GL15.GL_NEAREST);
				GL15.glTexParameteri(GL15.GL_TEXTURE_CUBE_MAP,
						GL15.GL_TEXTURE_MIN_FILTER, GL15.GL_NEAREST);

			}
			GL15.glTexParameteri(GL15.GL_TEXTURE_CUBE_MAP, GL15.GL_TEXTURE_WRAP_S,
					GL15.GL_CLAMP_TO_EDGE);
			GL15.glTexParameteri(GL15.GL_TEXTURE_CUBE_MAP, GL15.GL_TEXTURE_WRAP_T,
					GL15.GL_CLAMP_TO_EDGE);
			GL15.glTexParameteri(GL15.GL_TEXTURE_CUBE_MAP, GL15.GL_TEXTURE_WRAP_R,
					GL15.GL_CLAMP_TO_EDGE);

			// System.out.println(img.mWidth);
		}

		return new SkyboxTexture(id);

	}

	private static int createTexture(int[] pixels, int width, int height,
			boolean smooth, boolean mipmap) {

		final int id = GL15.glGenTextures();
		GL15.glBindTexture(GL15.GL_TEXTURE_2D, id);
		if (smooth) {
			GL15.glTexParameterf(GL15.GL_TEXTURE_2D, GL15.GL_TEXTURE_MIN_FILTER,
					GL15.GL_LINEAR);
			GL15.glTexParameterf(GL15.GL_TEXTURE_2D, GL15.GL_TEXTURE_MAG_FILTER,
					GL15.GL_LINEAR);
		} else {
			GL15.glTexParameterf(GL15.GL_TEXTURE_2D, GL15.GL_TEXTURE_MIN_FILTER,
					GL15.GL_NEAREST);
			GL15.glTexParameterf(GL15.GL_TEXTURE_2D, GL15.GL_TEXTURE_MAG_FILTER,
					GL15.GL_NEAREST);
		}

		GL15.glTexImage2D(GL15.GL_TEXTURE_2D, 0, GL15.GL_RGBA, width, height, 0,
				GL15.GL_BGRA, GL15.GL_UNSIGNED_BYTE, pixels);
		// GL15.glTexImage2D(target, level, internalformat, width, height, border,
		// format, type, pixels);

		if (mipmap) {
			GL30.glGenerateMipmap(GL11.GL_TEXTURE_2D);
			GL11.glTexParameteri(GL11.GL_TEXTURE_2D, GL11.GL_TEXTURE_MIN_FILTER,
					GL11.GL_LINEAR_MIPMAP_LINEAR);
			GL11.glTexParameterf(GL11.GL_TEXTURE_2D, GL14.GL_TEXTURE_LOD_BIAS,
					-1.4f);
		}
		return id;
	}
}
