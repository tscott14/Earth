package camera;

import org.joml.Matrix4f;
import org.joml.Vector3f;

import render.MatrixMaths;

public class FreeCamera extends Camera {
	private Vector3f mPosition;
	private float mPitch;
	private float mYaw;

	private Matrix4f mProjection;

	public FreeCamera(final int width, final int height, final float fov) {
		this.mPosition = new Vector3f(0, 0, 3);
		this.mPitch = 0.0f;
		this.mYaw = 0.0f;
		this.mZoomSpeed = 0.1f;

		this.updateCameraProjectionMatrix(width, height, fov);
		
	}

	public void setPosition(final float x, final float y, final float z) {
		this.mPosition.x = x;
		this.mPosition.y = y;
		this.mPosition.z = z;
	}

	public void updatePosition(final float forward, final float vertical,
			final float sizeways) {
		// moving forwards
		this.mPosition.x -= Math.sin(Math.toRadians(mYaw)) * forward * mZoomSpeed;
		this.mPosition.y += Math.sin(Math.toRadians(mPitch)) * forward * mZoomSpeed;
		this.mPosition.z += Math.cos(Math.toRadians(mYaw)) * forward * mZoomSpeed;

		// moving vertical
		this.mPosition.y += vertical * mZoomSpeed;

		// moving sideways
		this.mPosition.x += Math.cos(Math.toRadians(mYaw)) * sizeways * mZoomSpeed;
		this.mPosition.z += Math.sin(Math.toRadians(mYaw)) * sizeways * mZoomSpeed;
	}

	public void setRotation(final float pitch, final float yaw) {
		this.mPitch = pitch;
		this.mYaw = yaw;
	}

	public void updateRotation(final float pitch, final float yaw) {
		this.mPitch += pitch;
		this.mYaw += yaw;
	}

	public void updateCameraProjectionMatrix(final int width, final int height,
			final float fov) {
		this.mProjection = CameraUtils.generateCameraProjectionMatrix(fov,
				(float) width / (float) height, 0.01f, 10.0f);
	}

	public Vector3f getPosition() {
		return mPosition;
	}

	public Matrix4f getCameraViewMatrix() {
		return CameraUtils.generateFreeCameraTransformationMatrix(mPosition, mPitch,
				mYaw);
	}

	public Matrix4f getCameraProjectionMatrix() {
		return mProjection;
	}
}
