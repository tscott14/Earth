package camera;

import org.joml.Matrix4f;
import org.joml.Vector3f;

public class OrbitalCamera extends Camera {
	private static float POLES_THRESHOLD = 0.1f;
	private static float MAX_ZOOM = 0.05f;
	private static float MIN_ZOOM = 2.5f;

	private float mRho, mTheta, mPhi;

	private Matrix4f mProjection;

	public OrbitalCamera(final int width, final int height, final float fov) {
		this.mRho = 2.5f;
		this.mTheta = 0.0f;
		this.mPhi = 90;

		this.mMovementSpeed = 0.5f;
		this.mZoomSpeed = 0.4f;

		this.updateCameraProjectionMatrix(width, height, fov);

	}

	private float calculateDeltaRho(float dr) {
		return -0.25f * this.mRho * dr;
	}

	private float calculateDeltaTheta(float dr) {
		return this.mRho * dr;
	}

	private float calculateDeltaPhi(float dr) {
		return this.mRho * dr;
	}

	public void updateCameraOrbitalPosition(float drho, float dtheta, float dphi) {

		this.mRho += calculateDeltaRho(drho) * mZoomSpeed;
		this.mTheta += calculateDeltaTheta(dtheta) * mMovementSpeed;
		this.mPhi += calculateDeltaPhi(dphi) * mMovementSpeed;
		

		if (mRho < MAX_ZOOM)
			this.mRho = MAX_ZOOM;

		if (mRho > MIN_ZOOM)
			this.mRho = MIN_ZOOM;

		while (this.mTheta < 0)
			this.mTheta += 360;

		while (this.mTheta > 360)
			this.mTheta -= 360;

		if (this.mPhi < POLES_THRESHOLD)
			this.mPhi = POLES_THRESHOLD;

		if (this.mPhi > 180 - POLES_THRESHOLD)
			this.mPhi = 180 - POLES_THRESHOLD;
	}

	public void updateCameraProjectionMatrix(final int width, final int height, final float fov) {
		this.mProjection = CameraUtils.generateCameraProjectionMatrix(fov, (float) width / (float) height, 0.01f,
				10.0f);
	}

	public Matrix4f getCameraViewMatrix() {
		final float rt = this.getThetaR();
		final float rp = this.getPhiR();
		return CameraUtils.generateOrbitalCameraTransformationMatrix(this.getRho(), rt, rp);
	}

	public Matrix4f getCameraRotationMatrix() {
		final float rt = this.getThetaR();
		final float rp = this.getPhiR();
		return CameraUtils.generateOrbitalCameraRotationMatrix(this.getRho(), rt, rp);
	}

	public Vector3f getCameraPosition() {
		final float rho = this.getRho();
		final float phi = this.getPhiR();
		final float theta = this.getThetaR();

		final float nx = (float) (rho * Math.sin(phi) * Math.cos(theta));
		final float ny = (float) (rho * Math.cos(phi));
		final float nz = (float) (rho * Math.sin(phi) * Math.sin(theta));

		return new Vector3f(nx, ny, nz);
	}

	public Matrix4f getCameraProjectionMatrix() {
		return this.mProjection;
	}

	public float getRho() {
		return this.mRho + 1;
	}

	public float getThetaD() {
		return this.mTheta;
	}

	public float getPhiD() {
		return this.mPhi;
	}

	public float getThetaR() {
		return (float) Math.toRadians(this.mTheta);
	}

	public float getPhiR() {
		return (float) Math.toRadians(this.mPhi);
	}

}
