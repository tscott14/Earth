package model;

import textures.Texture;

public class Model {
	private final Mesh mMesh;
	private final Texture mTexture;

	public Model(Mesh mesh, Texture texture) {
		super();
		this.mMesh = mesh;
		this.mTexture = texture;
	}

	public Mesh getMesh() {
		return mMesh;
	}

	public Texture getTexture() {
		return mTexture;
	}

}
