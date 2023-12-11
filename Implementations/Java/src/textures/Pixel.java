package textures;

public class Pixel {
	public float mR;
	public float mG;
	public float mB;
	public float mA;

	public Pixel(final float mR, final float mG, final float mB, final float mA) {
		super();
		this.mR = mR;
		this.mG = mG;
		this.mB = mB;
		this.mA = mA;
	}
	
	public String toString() {
		return "[" + this.mR + ", " + this.mG + ", " + this.mB + ", " + this.mA + "]";
	}
}
