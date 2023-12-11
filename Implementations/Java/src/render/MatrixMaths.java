package render;

import org.joml.Matrix4f;
import org.joml.Vector3f;

public class MatrixMaths {
	public static Matrix4f createTransformationMatrix(Matrix4f matrix, Vector3f translation,
			Vector3f rotation, float scale) {
		matrix.identity();
		matrix.translate(
				new Vector3f(translation.x, translation.y, translation.z));
		matrix.rotate((float) Math.toRadians(rotation.x), new Vector3f(1, 0, 0));
		matrix.rotate((float) Math.toRadians(rotation.y), new Vector3f(0, 1, 0));
		matrix.rotate((float) Math.toRadians(rotation.z), new Vector3f(0, 0, 1));
		matrix.scale(scale);
		return matrix;
	}
	
	public static Matrix4f createCubeMapTransformationMatrix(float rx, float ry, float rz) {
		Matrix4f matrix = new Matrix4f().identity();
		//matrix.scale(10 / 2.5f);
		return matrix;
	}

	
}
