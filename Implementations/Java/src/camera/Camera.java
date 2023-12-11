package camera;

import org.joml.Matrix4f;

public abstract class Camera {

	protected float mMovementSpeed;
	protected float mZoomSpeed;
	
	public abstract Matrix4f getCameraViewMatrix();

}
