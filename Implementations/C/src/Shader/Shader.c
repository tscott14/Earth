#include "Shader.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_OF_SHADER_PATH 256

static void GetFullShaderPath(char result[], GLenum type,
                              const char filename[]) {
  static const char *prefix = "res/shaders/";
  static const char *vext = ".vs.glsl";
  static const char *tcs = ".tcs.glsl";
  static const char *tes = ".tes.glsl";
  static const char *geo = ".geom.glsl";
  static const char *fext = ".fs.glsl";
  memset(result, '\0', MAX_LENGTH_OF_SHADER_PATH);

  strcpy(result, prefix);
  strcat(result, filename);

  if (type == GL_VERTEX_SHADER)
    strcat(result, vext);
  if (type == GL_TESS_CONTROL_SHADER)
    strcat(result, tcs);
  if (type == GL_TESS_EVALUATION_SHADER)
    strcat(result, tes);
  if (type == GL_GEOMETRY_SHADER)
    strcat(result, geo);
  if (type == GL_FRAGMENT_SHADER)
    strcat(result, fext);
}

static const char *LoadShaderFromFile(GLenum type, const char *filepath) {
  char fullpath[MAX_LENGTH_OF_SHADER_PATH];
  GetFullShaderPath(fullpath, type, filepath);

  FILE *file = fopen(fullpath, "rt");
  if (!file)
    fprintf(stderr, "Could not open file: %s", fullpath);
  fseek(file, 0, SEEK_END);
  unsigned int length = ftell(file);
  char *data = (char *)malloc(sizeof(char) * (length + 1));
  memset(data, 0, length + 1);
  fseek(file, 0, SEEK_SET);
  fread(data, 1, length, file);
  fclose(file);

  return data;
}

static GLuint CreateShader(GLenum type, const char *src) {
  GLuint shader = glCreateShader(type);

  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  GLint result = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if (result != GL_TRUE) {
    int infoLogLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    char infoLog[infoLogLength + 1];
    glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
    fprintf(stderr, "ERROR Compiling %d:\n%s\n", type, infoLog);
  }

  return shader;
}

static void ValidateShaderProgram(GLuint program) {
  GLint result = GL_FALSE;
  glGetProgramiv(program, GL_LINK_STATUS, &result);
  if (!result) {
    int infoLogLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
    char infoLog[infoLogLength + 1];
    glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
    fprintf(stderr, "ERROR Linking:\n%s\n", infoLog);
  }
}
static ShaderProgram ShaderProgramCreateTessGeom(const char *shaderName) {
  printf("Loading in tesselation+geometry shader %s.\n", shaderName);
  const char *vertSrc = LoadShaderFromFile(GL_VERTEX_SHADER, shaderName);
  const char *tcsSrc = LoadShaderFromFile(GL_TESS_CONTROL_SHADER, shaderName);
  const char *tesSrc =
      LoadShaderFromFile(GL_TESS_EVALUATION_SHADER, shaderName);
  const char *geomSrc =
      LoadShaderFromFile(GL_GEOMETRY_SHADER, shaderName);
  const char *fragSrc = LoadShaderFromFile(GL_FRAGMENT_SHADER, shaderName);

  GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertSrc);
  GLuint controlShader = CreateShader(GL_TESS_CONTROL_SHADER, tcsSrc);
  GLuint evaluationShader = CreateShader(GL_TESS_EVALUATION_SHADER, tesSrc);
  GLuint geometryShader = CreateShader(GL_GEOMETRY_SHADER, geomSrc);
  GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragSrc);

  free((char *)vertSrc);
  free((char *)tcsSrc);
  free((char *)tesSrc);
  free((char *)geomSrc);
  free((char *)fragSrc);

  ShaderProgram program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, controlShader);
  glAttachShader(program, evaluationShader);
  glAttachShader(program, geometryShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  ValidateShaderProgram(program);

  glDetachShader(program, vertexShader);
  glDetachShader(program, controlShader);
  glDetachShader(program, evaluationShader);
  glDetachShader(program, geometryShader);
  glDetachShader(program, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(controlShader);
  glDeleteShader(evaluationShader);
  glDeleteShader(geometryShader);
  glDeleteShader(fragmentShader);

  return program;
}

static ShaderProgram ShaderProgramCreateTess(const char *shaderName) {
  printf("Loading in tesselation shader %s.\n", shaderName);
  const char *vertSrc = LoadShaderFromFile(GL_VERTEX_SHADER, shaderName);
  const char *tcsSrc = LoadShaderFromFile(GL_TESS_CONTROL_SHADER, shaderName);
  const char *tesSrc =
      LoadShaderFromFile(GL_TESS_EVALUATION_SHADER, shaderName);
  const char *fragSrc = LoadShaderFromFile(GL_FRAGMENT_SHADER, shaderName);

  GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertSrc);
  GLuint controlShader = CreateShader(GL_TESS_CONTROL_SHADER, tcsSrc);
  GLuint evaluationShader = CreateShader(GL_TESS_EVALUATION_SHADER, tesSrc);
  GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragSrc);

  free((char *)vertSrc);
  free((char *)tcsSrc);
  free((char *)tesSrc);
  free((char *)fragSrc);

  ShaderProgram program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, controlShader);
  glAttachShader(program, evaluationShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  ValidateShaderProgram(program);

  glDetachShader(program, vertexShader);
  glDetachShader(program, controlShader);
  glDetachShader(program, evaluationShader);
  glDetachShader(program, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(controlShader);
  glDeleteShader(evaluationShader);
  glDeleteShader(fragmentShader);

  return program;
}

static ShaderProgram ShaderProgramCreateGeom(const char *shaderName) {
  
}

static ShaderProgram ShaderProgramCreateStandard(const char *shaderName) {
  printf("Loading in standard shader %s.\n", shaderName);
  const char *vertSrc = LoadShaderFromFile(GL_VERTEX_SHADER, shaderName);
  const char *fragSrc = LoadShaderFromFile(GL_FRAGMENT_SHADER, shaderName);

  GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertSrc);
  GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragSrc);

  free((char *)vertSrc);
  free((char *)fragSrc);

  ShaderProgram program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  ValidateShaderProgram(program);

  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}

ShaderProgram ShaderProgramCreate(const char *shaderName,
                                  ShaderTypesParam types) {
  if (types.mTesselationShader && types.mGeometryShader)
    return ShaderProgramCreateTessGeom(shaderName);
  if (types.mTesselationShader)
    return ShaderProgramCreateTess(shaderName);
  if (types.mGeometryShader)
    return ShaderProgramCreateGeom(shaderName);
  return ShaderProgramCreateStandard(shaderName);
}

void ShaderProgramDestroy(GLuint shader_program) {
  glDeleteProgram(shader_program);
}

PlanetShader PlanetShaderCreate() {
  ShaderProgram program =
      ShaderProgramCreate("PlanetShader", STNRD_W_TESS_SHADER);

  // glNamedStringARB
  //const char name[] = "/ARB/PlanetNoiseFunction.h.glsl";
  //glNamedStringARB(SHADER_INCLUDE_ARB, strlen(name), name, strlen(""), "");

  GLint modelLoc = glGetUniformLocation(program, "uModelMatrix");
  GLint viewLoc = glGetUniformLocation(program, "uViewMatrix");
  GLint projLoc = glGetUniformLocation(program, "uProjMatrix");

  GLint camPosLoc = glGetUniformLocation(program, "uCameraPosition");

  GLint bumpLoc = glGetUniformLocation(program, "uBumpSampler");
  GLint bump2Loc = glGetUniformLocation(program, "uBumpSampler2");

  return (PlanetShader){
      .mShaderProgramHandle = program,
      .mModelLocation = modelLoc,
      .mViewLocation = viewLoc,
      .mProjLocation = projLoc,

      .mCamPosLocation = camPosLoc,

      .mBumpTextureLocation = bumpLoc,
      .mBumpTextureLocation2 = bump2Loc,
  };
}