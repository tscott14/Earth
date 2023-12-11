package textures;

public class TextureManager {

	public static final Texture mEarthAlbetoTexture = TextureUtils
			.loadTexture("earth/albedo.png", true, true);
	// public static final Texture mEarthAlbetoTexture =
	// TextureUtils.loadTexture("earth/Albedo_small", false, false);
	public static final Texture mEarthSpecularTexture = TextureUtils
			.loadTexture("earth/specular.png", true, true);
	public static final Texture mEarthNormalMapTexture = TextureUtils
			.loadTexture("earth/NormalMap2.png", true, true);
	public static final Texture mEarthCloudsTexture = TextureUtils
			.loadTexture("earth/clouds.png", true, true);

	public static final SkyboxTexture mCubeMapTexture = TextureUtils
			.loadCubeMapTexture(true);
	// public static final SkyboxTexture mCubeMapTexture =
	// TextureUtils.loadCubeMapTexture("profile_test2", false);

}
