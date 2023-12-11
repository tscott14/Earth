package world;

import java.util.ArrayList;
import java.util.HashMap;

import org.joml.Vector2f;
import org.joml.Vector3f;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;

import model.Mesh;

class PlanetData {
	final float mVerticies[];
	final int mIndicies[];

	public PlanetData(final float verticies[], final int indicies[]) {
		this.mVerticies = verticies;
		this.mIndicies = indicies;
	}

};

class TriangleIndices {
	public int v1;
	public int v2;
	public int v3;

	public TriangleIndices(final int v1, final int v2, final int v3) {
		this.v1 = v1;
		this.v2 = v2;
		this.v3 = v3;
	}
}

class PlanetVertex {
	public Vector3f mPosition; // position
	public Vector2f mTexCoords; // texture coordinates

	public Vector3f mTangent; // normal
	public Vector3f mBitangent; // normal
	public Vector3f mNormal; // normal

	public PlanetVertex(final float x, final float y, final float z, final float u, final float v, final float tx,
			final float ty, final float tz, final float bx, final float by, final float bz, final float nx,
			final float ny, final float nz) {

		this.mPosition = new Vector3f(x, y, z);
		this.mTexCoords = new Vector2f(u, v);

		this.mTangent = new Vector3f(tx, ty, tz);
		this.mBitangent = new Vector3f(bx, by, bz);
		this.mNormal = new Vector3f(nx, ny, nz);
	}

	public PlanetVertex clone() {
		return new PlanetVertex(mPosition.x, mPosition.y, mPosition.z, mTexCoords.x, mTexCoords.y, mTangent.x,
				mTangent.y, mTangent.z, mBitangent.x, mBitangent.y, mBitangent.z, mNormal.x, mNormal.y, mNormal.z);
	}
}

public class PlanetGenerator {

	private ArrayList<PlanetVertex> mVerticies;
	private ArrayList<TriangleIndices> mFaces;

	private HashMap<Long, Integer> middlePointIndexCache;

	PlanetGenerator() {
		mVerticies = new ArrayList<>(12);
		mFaces = new ArrayList<>(20);

		middlePointIndexCache = new HashMap<>();

		{ // Add initial verticies
			final float t = (float) ((1.0 + Math.sqrt(5.0)) / 2.0);

			addVertex(-1, t, 0, true); // 0
			addVertex(1, t, 0, true); // 1
			addVertex(-1, -t, 0, true); // 2
			addVertex(1, -t, 0, true); // 3

			addVertex(0, -1, t, true); // 4
			addVertex(0, 1, t, true); // 5
			addVertex(0, -1, -t, true); // 6
			addVertex(0, 1, -t, true); // 7

			addVertex(t, 0, -1, true); // 8
			addVertex(t, 0, 1, true); // 9
			addVertex(-t, 0, -1, true); // 10
			addVertex(-t, 0, 1, true); // 11
		}

		{ // create 20 triangles of the icosahedron

			// 5 mFaces around point 0
			addFace(0, 11, 5); // China Asia + western pacific Ocean
			addFace(0, 5, 1); // pacific side of artic
			addFace(0, 1, 7);// // atlantic side of artic //
			addFace(0, 7, 10);// // middle east //
			addFace(0, 10, 11); // india

			// 5 adjacent mFaces
			addFace(1, 5, 9); // western USA to HAWAII
			addFace(5, 11, 4); // polynesia
			addFace(11, 10, 2); // Idian Ocean
			addFace(10, 7, 6);// central africa
			addFace(7, 1, 8); // Atlantic slave trade

			// 5 mFaces around point 3
			addFace(3, 9, 4); // Southern Pacific
			addFace(3, 4, 2); // pacific side of anartic
			addFace(3, 2, 6);// // atlantic side of anartic //
			addFace(3, 6, 8); // Brazil + Argentina + equator
			addFace(3, 8, 9); // Peru + chile + easter island

			// 5 adjacent mFaces
			addFace(4, 9, 5); // middle of pacific
			addFace(2, 4, 11); // Australia
			addFace(6, 2, 10);// // south africa + matagascar //
			addFace(8, 6, 7); // mid atlantic
			addFace(9, 8, 1); // mid USA + central america
		}
	}

	Mesh generatePlanetMesh(final int level) {
		generatePlanetData(level);

		int vaoID = GL30.glGenVertexArrays();
		GL30.glBindVertexArray(vaoID);

		int lengthOfIndicies = -1;

		{
			int vbo = GL15.glGenBuffers();
			GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, vbo);

			lengthOfIndicies = mFaces.size();
			int buffer[] = new int[lengthOfIndicies * 3];
			for (int i = 0; i < lengthOfIndicies; i++) {
				TriangleIndices face = mFaces.get(i);
				buffer[i * 3 + 0] = face.v1;
				buffer[i * 3 + 1] = face.v2;
				buffer[i * 3 + 2] = face.v3;
			}

			GL15.glBufferData(GL15.GL_ELEMENT_ARRAY_BUFFER, buffer, GL15.GL_STATIC_DRAW);
		}

		{
			int vboID = GL15.glGenBuffers();
			GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, vboID);

			final int SIZE = 14;
			float buffer[] = new float[mVerticies.size() * SIZE];
			for (int i = 0; i < mVerticies.size(); i++) {
				buffer[i * SIZE + +0] = mVerticies.get(i).mPosition.x;
				buffer[i * SIZE + +1] = mVerticies.get(i).mPosition.y;
				buffer[i * SIZE + +2] = mVerticies.get(i).mPosition.z;

				buffer[i * SIZE + +3] = mVerticies.get(i).mTexCoords.x;
				buffer[i * SIZE + +4] = mVerticies.get(i).mTexCoords.y;

				buffer[i * SIZE + +5] = mVerticies.get(i).mTangent.x;
				buffer[i * SIZE + +6] = mVerticies.get(i).mTangent.y;
				buffer[i * SIZE + +7] = mVerticies.get(i).mTangent.z;

				buffer[i * SIZE + +8] = mVerticies.get(i).mBitangent.x;
				buffer[i * SIZE + +9] = mVerticies.get(i).mBitangent.y;
				buffer[i * SIZE + 10] = mVerticies.get(i).mBitangent.z;

				buffer[i * SIZE + 11] = mVerticies.get(i).mNormal.x;
				buffer[i * SIZE + 12] = mVerticies.get(i).mNormal.y;
				buffer[i * SIZE + 13] = mVerticies.get(i).mNormal.z;
			}

			GL15.glBufferData(GL15.GL_ARRAY_BUFFER, buffer, GL15.GL_STATIC_DRAW);

			final int SIZE_OF_FLOAT = 4;
			GL20.glVertexAttribPointer(0, 3, GL11.GL_FLOAT, false, SIZE * SIZE_OF_FLOAT, 0 * SIZE_OF_FLOAT);
			GL20.glVertexAttribPointer(1, 2, GL11.GL_FLOAT, false, SIZE * SIZE_OF_FLOAT, 3 * SIZE_OF_FLOAT);

			GL20.glVertexAttribPointer(2, 3, GL11.GL_FLOAT, false, SIZE * SIZE_OF_FLOAT, 5 * SIZE_OF_FLOAT);
			GL20.glVertexAttribPointer(3, 3, GL11.GL_FLOAT, false, SIZE * SIZE_OF_FLOAT, 8 * SIZE_OF_FLOAT);
			GL20.glVertexAttribPointer(4, 3, GL11.GL_FLOAT, false, SIZE * SIZE_OF_FLOAT, 11 * SIZE_OF_FLOAT);

			GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, 0);
		}

		GL30.glBindVertexArray(0);

		return new Mesh(vaoID, lengthOfIndicies * 3);
	}

	private void generatePlanetData(final int recursionLevel) {
		for (int l = 0; l < recursionLevel; l++) {

			ArrayList<TriangleIndices> faces2 = new ArrayList<>();
			for (TriangleIndices tri : mFaces) {
				// replace triangle by 4 triangles
				int a = getMiddlePoint(tri.v1, tri.v2);
				int b = getMiddlePoint(tri.v2, tri.v3);
				int c = getMiddlePoint(tri.v3, tri.v1);

				faces2.add(new TriangleIndices(tri.v1, a, c));
				faces2.add(new TriangleIndices(tri.v2, b, a));
				faces2.add(new TriangleIndices(tri.v3, c, b));
				faces2.add(new TriangleIndices(a, b, c));
			}
			mFaces = faces2;
		}

		fixWrappedUV(detectWrappedUVCoordinates());

		calculateNormals();
	}

	private void calculateNormals() {
		for (TriangleIndices tri : this.mFaces) {
			// Vector3f resultingNormal = new Vector3f();

			// Vector3i permutations[] = { new Vector3i(tri.v1, tri.v2, tri.v3), new
			// Vector3i(tri.v2, tri.v3, tri.v1),
			// new Vector3i(tri.v3, tri.v1, tri.v2), };

			// for (Vector3i p : permutations) {
			PlanetVertex p1 = this.mVerticies.get(tri.v1).clone();
			PlanetVertex p2 = this.mVerticies.get(tri.v2).clone();
			PlanetVertex p3 = this.mVerticies.get(tri.v3).clone();

			Vector3f edge1 = p2.mPosition.sub(p1.mPosition);
			Vector3f edge2 = p3.mPosition.sub(p1.mPosition);
			Vector2f duv1 = p2.mTexCoords.sub(p1.mTexCoords);
			Vector2f duv2 = p3.mTexCoords.sub(p1.mTexCoords);

			Vector3f tangent1 = new Vector3f();
			Vector3f bitangent1 = new Vector3f();
			Vector3f normal = new Vector3f();

			float f = 1.0f / (duv1.x * duv2.y - duv2.x * duv1.y);

			tangent1.x = f * (duv2.y * edge1.x - duv1.y * edge2.x);
			tangent1.y = f * (duv2.y * edge1.y - duv1.y * edge2.y);
			tangent1.z = f * (duv2.y * edge1.z - duv1.y * edge2.z);

			bitangent1.x = f * (-duv2.x * edge1.x + duv1.x * edge2.x);
			bitangent1.y = f * (-duv2.x * edge1.y + duv1.x * edge2.y);
			bitangent1.z = f * (-duv2.x * edge1.z + duv1.x * edge2.z);

			normal = bitangent1.cross(tangent1);

			tangent1 = tangent1.normalize();
			bitangent1 = bitangent1.normalize();
			normal = normal.normalize();

			this.mVerticies.get(tri.v1).mTangent = tangent1;
			this.mVerticies.get(tri.v1).mBitangent = bitangent1;
			this.mVerticies.get(tri.v1).mNormal = normal;
			
			this.mVerticies.get(tri.v2).mTangent = tangent1;
			this.mVerticies.get(tri.v2).mBitangent = bitangent1;
			this.mVerticies.get(tri.v2).mNormal = normal;
			
			this.mVerticies.get(tri.v3).mTangent = tangent1;
			this.mVerticies.get(tri.v3).mBitangent = bitangent1;
			this.mVerticies.get(tri.v3).mNormal = normal;

			// }

			// resultingNormal = resultingNormal.normalize();
		}

	}

	private int addVertex(float x, float y, float z, boolean normalize) {
		if (normalize) {
			float dist = (float) Math.sqrt(x * x + y * y + z * z);
			x /= dist;
			y /= dist;
			z /= dist;
		}

		float u = (float) (Math.atan2(x, z) / (2 * Math.PI));
		float v = (float) (Math.acos(y) / Math.PI);

		mVerticies.add(new PlanetVertex(x, y, z, u, v, 0, 0, 0, 0, 0, 0, 0, 0, 0));
		return mVerticies.size() - 1;
	}

	private void addFace(final int v1, final int v2, final int v3) {
		mFaces.add(new TriangleIndices(v1, v2, v3));
	}

	private int getMiddlePoint(int p1, int p2) {
		// first check if we have it already
		boolean firstIsSmaller = p1 < p2;
		long smallerIndex = firstIsSmaller ? p1 : p2;
		long greaterIndex = firstIsSmaller ? p2 : p1;
		long key = (smallerIndex << 32) + greaterIndex;

		if (middlePointIndexCache.containsKey(key)) {
			return middlePointIndexCache.get(key);
		}

		// not in cache, calculate it
		PlanetVertex point1 = this.mVerticies.get(p1);
		PlanetVertex point2 = this.mVerticies.get(p2);

		float dx = 0.5f * (point1.mPosition.x + point2.mPosition.x);
		float dy = 0.5f * (point1.mPosition.y + point2.mPosition.y);
		float dz = 0.5f * (point1.mPosition.z + point2.mPosition.z);

		// add vertex makes sure point is on unit sphere
		int i = addVertex(dx, dy, dz, true);

		// store it, return index
		this.middlePointIndexCache.put(key, i);
		return i;
	}

	/*
	 * Credit to Michael Thygesen from https://mft-dev.dk/uv-mapping-sphere/
	 */
	private Integer[] detectWrappedUVCoordinates() {
		ArrayList<Integer> indicies = new ArrayList<>();
		for (int i = 0; i < mFaces.size(); i++) {
			TriangleIndices face = mFaces.get(i);

			final PlanetVertex p1 = mVerticies.get(face.v1);
			final PlanetVertex p2 = mVerticies.get(face.v2);
			final PlanetVertex p3 = mVerticies.get(face.v3);

			final Vector3f texP1 = new Vector3f(p1.mTexCoords.x, p1.mTexCoords.y, 0);
			final Vector3f texP2 = new Vector3f(p2.mTexCoords.x, p2.mTexCoords.y, 0);
			final Vector3f texP3 = new Vector3f(p3.mTexCoords.x, p3.mTexCoords.y, 0);

			final Vector3f bma = texP2.sub(texP1);
			final Vector3f cma = texP3.sub(texP1);

			Vector3f texNormal = cma.cross(bma);

			if (texNormal.z < 0)
				indicies.add(i);
			// System.out.println(texNormal.z);
		}
		Integer result[] = new Integer[indicies.size()];
		indicies.toArray(result);
		return result;
	}

	/*
	 * Credit to Michael Thygesen from https://mft-dev.dk/uv-mapping-sphere/
	 */
	private void fixWrappedUV(Integer[] wrapped) {
		int verticeIndex = mVerticies.size() - 1;
		HashMap<Integer, Integer> visited = new HashMap<>();
		for (int i : wrapped) {

			TriangleIndices face = mFaces.get(i);
			int a = face.v1;
			int b = face.v2;
			int c = face.v3;
			PlanetVertex v1 = mVerticies.get(a).clone();
			PlanetVertex v2 = mVerticies.get(b).clone();
			PlanetVertex v3 = mVerticies.get(c).clone();

			if (v1.mTexCoords.x < 0.25f) {
				int tempA = a;
				// if (!visited.TryGetValue(a, out tempA))
				if (visited.containsKey(a)) {
					tempA = visited.get(a);
				} else {
					v1.mTexCoords.x += 1;
					mVerticies.add(v1); // change ABC to v1 v2 v3
					verticeIndex++;
					visited.put(a, verticeIndex);
					tempA = verticeIndex;
				}
				a = tempA;
			}
			if (v2.mTexCoords.x < 0.25f) {
				int tempB = b;
				if (visited.containsKey(b)) {
					tempB = visited.get(b);
				} else {
					v2.mTexCoords.x += 1;
					mVerticies.add(v2);
					verticeIndex++;
					visited.put(b, verticeIndex);
					tempB = verticeIndex;
				}
				b = tempB;
			}
			if (v3.mTexCoords.x < 0.25f) {
				int tempC = c;
				if (visited.containsKey(c)) {
					tempC = visited.get(c);
				} else {
					v3.mTexCoords.x += 1;
					mVerticies.add(v3);
					verticeIndex++;
					visited.put(c, verticeIndex);
					tempC = verticeIndex;
				}
				c = tempC;
			}

			face.v1 = a;
			face.v2 = b;
			face.v3 = c;
		}
	}

	// http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
}
