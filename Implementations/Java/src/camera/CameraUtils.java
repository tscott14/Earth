package camera;

import org.joml.Matrix4f;
import org.joml.Vector3f;

public abstract class CameraUtils {
	public static Matrix4f generateFreeCameraTransformationMatrix(
			Vector3f translation, float pitch, float yaw) {
		Matrix4f matrix = new Matrix4f().identity();
		matrix.rotate((float) Math.toRadians(pitch), new Vector3f(1, 0, 0));
		matrix.rotate((float) Math.toRadians(yaw), new Vector3f(0, 1, 0));
		matrix.translate(
				new Vector3f(-translation.x, -translation.y, -translation.z));
		return matrix;
	}

	public static Matrix4f generateOrbitalCameraTransformationMatrix(
			final float rho, final float theta, final float phi) {
		Matrix4f matrix = new Matrix4f().identity();

		final float nx = (float) (rho * Math.sin(phi) * Math.cos(theta));
		final float ny = (float) (rho * Math.cos(phi));
		final float nz = (float) (rho * Math.sin(phi) * Math.sin(theta));

		matrix.lookAt(0, 0, 0, -nx, -ny, -nz, 0, 1, 0);

		matrix.translate(-nx, -ny, -nz);

		return matrix;

	}
	
	public static Matrix4f generateOrbitalCameraRotationMatrix(final float rho, final float theta, final float phi) {
		Matrix4f matrix = new Matrix4f().identity();
		
		final float nx = (float) (rho * Math.sin(phi) * Math.cos(theta));
		final float ny = (float) (rho * Math.cos(phi));
		final float nz = (float) (rho * Math.sin(phi) * Math.sin(theta));
		
		matrix.lookAt(0, 0, 0, -nx, -ny, -nz, 0, 1, 0);
		
		return matrix;
	}

	public static Matrix4f generateCameraProjectionMatrix(float fov, float aspect,
			float zNear, float zFar) {
		Matrix4f matrix = new Matrix4f().identity();
		matrix.perspective(fov, aspect, zNear, zFar);
		return matrix;
	} 
}
