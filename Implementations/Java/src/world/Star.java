package world;

import org.joml.Vector3f;

public class Star {
	private Vector3f mDirection;
	private Vector3f mColor;
	
	private float intensity;

	public Star() {
		this.mDirection = new Vector3f(1.0f, 0.0f, 0.0f);
		this.mColor = new Vector3f(5.0f, 5.0f, 4.0f);
		this.intensity = 1;
	}

	public Vector3f getDirection() {
		return mDirection;
	}

	public Vector3f getColor() {
		return mColor;
	}
	
	public float getIntensity() {
		return intensity;
	}
	
	public void update() {
		
	}
	
}
