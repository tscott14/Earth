package shaders;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class ShaderReader {

	private enum ShaderType {
		VERTEX_SHADER, GEOMETRY_SHADER, FRAGMENT_SHADER, SHADER_TYPE_LENGTH
	};

	public String loadVertexShader(String path) {
		return loadShaderSourceFromFile(path, ShaderType.VERTEX_SHADER);
	}

	public String loadGeometryShader(String path) {
		return loadShaderSourceFromFile(path, ShaderType.GEOMETRY_SHADER);
	}

	public String loadFragmentShader(String path) {
		return loadShaderSourceFromFile(path, ShaderType.FRAGMENT_SHADER);
	}

	public String[] loadShaders(String path) {
		final String fixedPath = "shaders/" + path + ".glsl";
	
		StringBuilder builder = new StringBuilder();
		try {
			Scanner reader = new Scanner(new File(fixedPath));
			while (reader.hasNextLine()) {
				String line = reader.nextLine();
				builder.append(line + "\n");
			}
		} catch (FileNotFoundException e) {
			System.err.printf("Couldnt open file: ", fixedPath);
			e.printStackTrace();
		}

		return builder.toString().split("<split>");
	}

	private String loadShaderSourceFromFile(String path, ShaderType type) {
		final String exts[] = { ".vs", ".gs", ".fs" };
		final int index = type.ordinal();
		final String fixedPath = "" + path + exts[index];

		StringBuilder builder = new StringBuilder();
		try {
			Scanner reader = new Scanner(new File(fixedPath));
			while (reader.hasNextLine()) {
				String line = reader.nextLine();
				builder.append(line + "\n");
			}
		} catch (FileNotFoundException e) {
			System.err.printf("Couldnt open file: ", fixedPath);
			e.printStackTrace();
		}

		return builder.toString();
	}

}
