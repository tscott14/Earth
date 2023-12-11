package world;

import org.joml.Matrix4f;
import org.joml.Vector3f;

import model.Mesh;
import render.MatrixMaths;
import textures.Texture;
import textures.TextureManager;

public class Planet {
	// private
	private Mesh mPlanetMesh;
	private Texture mPlanetAlbetoTexture;
	private Texture mPlanetSpecularTexture;
	private Texture mPlanetNormalTexture;
	private Texture mPlanetCloudsTexture;

	private float mTheta;
	private Matrix4f mPlanetModelMatrix;
	private Matrix4f mCloudsModelMatrix;

	public Planet() {
		super();

		PlanetGenerator g = new PlanetGenerator();

		this.mPlanetMesh = g.generatePlanetMesh(6);
		this.mPlanetAlbetoTexture = TextureManager.mEarthAlbetoTexture;
		this.mPlanetSpecularTexture = TextureManager.mEarthSpecularTexture;
		this.mPlanetNormalTexture = TextureManager.mEarthNormalMapTexture;
		this.mPlanetCloudsTexture =TextureManager.mEarthCloudsTexture;

		this.mTheta = 180;
		this.mPlanetModelMatrix = new Matrix4f().identity();
		this.mCloudsModelMatrix = new Matrix4f().identity();
	}

	public Mesh getPlanetMesh() {
		return mPlanetMesh;
	}

	public Texture getPlanetAlbetoTexture() {
		return mPlanetAlbetoTexture;
	}
	
	public Texture getPlanetSpecularTexture() {
		return mPlanetSpecularTexture;
	}

	public Texture getPlanetCloudsTexture() {
		return mPlanetCloudsTexture;
	}

	public Texture getPlanetNormalTexture() {
		return mPlanetNormalTexture;
	}

	public Matrix4f getPlanetModelMatrix() {
		return MatrixMaths.createTransformationMatrix(mPlanetModelMatrix, new Vector3f(),
				new Vector3f(0, mTheta, 0), 1);
	}
	
	public Matrix4f getCloudsModelMatrix() {
		return MatrixMaths.createTransformationMatrix(mCloudsModelMatrix, new Vector3f(),
				new Vector3f(0, mTheta * 0.5f, 0), 1);
	}

	public void update() {
		mTheta += 0.1;
	}

}
