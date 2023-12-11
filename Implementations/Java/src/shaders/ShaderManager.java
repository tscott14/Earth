package shaders;

import shaders.derivatives.CloudShader;
import shaders.derivatives.PlanetShader;
import shaders.derivatives.SkyboxShader;

public abstract class ShaderManager {
	//public static Basic3DShader mShader3D = new Basic3DShader();
	public static PlanetShader mPlanetShader = new PlanetShader();
	public static CloudShader mCloudShader = new CloudShader();
	public static SkyboxShader mSkyboxShader = new SkyboxShader();
}
