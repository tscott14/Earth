package model;

public class Mesh {
	private final int mVertexArrayObjectHandle;
	private final int mVertexCount;
	
	public Mesh(int vertexArrayObjectHandle, int vertexCount) {
		super();
		this.mVertexArrayObjectHandle = vertexArrayObjectHandle;
		this.mVertexCount = vertexCount;
	}

	public int getVertexArrayObjectHandle() {
		return mVertexArrayObjectHandle;
	}

	public int getVertexCount() {
		return mVertexCount;
	}
}
