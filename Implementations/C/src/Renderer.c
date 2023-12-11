#include "Renderer.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#include "Shader/Shader.h"
#include "Textures/TextureManager.h"
#include "Utilities/Transformations.h"
#include <stdlib.h>

void RendererClear() {
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_FRAMEBUFFER_SRGB);
  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void RendererSetRenderColor(float r, float g, float b) {
  glClearColor(r, g, b, 1);
}

void RendererRenderPlanet(PlanetPtr planet, Point3f sun,
                          TextureManagerPtr texture_manager,
                          Camera3DPtr camera) {

  const PlanetShader shader = planet->mPlanetShader;
  const struct PlanetMesh mesh = planet->mPlanetMeshManager.mTerrainMesh;
  PlanetGenerateModelMatrix(planet);
  CameraGenerateViewMatrix(camera);

  glBindVertexArray(mesh.mVertexArrayHandle);


  glUseProgram(shader.mShaderProgramHandle);

  glUniformMatrix4fv(shader.mModelLocation, 1, GL_FALSE,
                     (GLfloat *)planet->mModelMatrix.mData);
  glUniformMatrix4fv(shader.mViewLocation, 1, GL_FALSE,
                     (GLfloat *)camera->mViewMatrix.mData);
  glUniformMatrix4fv(shader.mProjLocation, 1, GL_FALSE,
                     (GLfloat *)camera->mProjMatrix.mData);

  const Point3f *cpos = &camera->mPosition;
  glUniform3f(shader.mCamPosLocation, cpos->x, cpos->y, cpos->z);

  // printf("\rDistance: %f", FloatGetLengthFloat3(*cpos));

  // glUniform3f(shader.mSunDirectionLocation, sun.x, sun.y, sun.z);

  glUniform1i(shader.mBumpTextureLocation, 0);
  glUniform1i(shader.mBumpTextureLocation2, 1);
  // glUniform1i(shader.mAlbetoTextureLocation, 1);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,
                texture_manager->mTextureList[BUMP_TEXTURE_ID].mTextureHandle);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(
      GL_TEXTURE_2D,
      texture_manager->mTextureList[BUMP_TEXTURE_ID].mTextureHandle);
  // glActiveTexture(GL_TEXTURE1);
  // glBindTexture(GL_TEXTURE_2D,
  //              texture_manager->mTextureList[TEST_TEXTURE_ID].mTextureHandle);

  glEnableVertexAttribArray(0);

  glPointSize(4);
  glPolygonMode(GL_FRONT_AND_BACK, GL_QUADS);
  glDrawElements(GL_PATCHES, mesh.mLength, GL_UNSIGNED_SHORT, NULL);

  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
  glUseProgram(0);
}