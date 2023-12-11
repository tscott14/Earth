#ifndef __SHADER__
#define __SHADER__

#include <GL/glew.h>

typedef GLuint ShaderProgram;

typedef struct ShaderTypesParam {
  uint8_t mTesselationShader : 1;
  uint8_t mGeometryShader : 1;
} ShaderTypesParam;

#define DefineShaderType(using_tesselation_shader, using_geometry_shader)      \
  (ShaderTypesParam) {                                                         \
    .mTesselationShader = using_tesselation_shader,                            \
    .mGeometryShader = using_geometry_shader,                                  \
  }

#define STNRD_SHADER DefineShaderType(0, 0)
#define STNRD_W_GEOM_SHADER DefineShaderType(0, 1)
#define STNRD_W_TESS_SHADER DefineShaderType(1, 0)
#define STNRD_W_GEOM_TESS_SHADER DefineShaderType(1, 1)

typedef struct PlanetShader {
  ShaderProgram mShaderProgramHandle;
  GLint mModelLocation;
  GLint mViewLocation;
  GLint mProjLocation;

  GLint mCamPosLocation;

  GLint mBumpTextureLocation;
  GLint mBumpTextureLocation2;
  //   GLint mSunDirectionLocation;

  //   GLint mHurlTextureLocation;
  //   GLint mAlbetoTextureLocation;

} PlanetShader;

ShaderProgram ShaderProgramCreate(const char *, const ShaderTypesParam);
void ShaderProgramDestroy(GLuint);

PlanetShader PlanetShaderCreate();

#endif