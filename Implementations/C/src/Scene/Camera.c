#include "Camera.h"

#include <stdlib.h>

Camera3DPtr CameraCreate(float fov, float aspect, float near, float far) {
  Camera3DPtr cam = (Camera3DPtr)malloc(sizeof(struct Camera3D));
  cam->mPosition = Float3Create(0, 2-0.950, 0);
  cam->mRotation = Float3Create(0, 0, 0);
  cam->mPhysicalAttribs = (CameraPhysics) {
    .mVelocity = 0.02,
    .mInertia = 100,
  };
  cam->mViewMatrix = CameraGenerateViewMatrix(cam);
  cam->mProjMatrix = Matrix4fCreateProspective(fov, aspect, near, far);
  //cam->mProjMatrix = Matrix4fCreateOrthographic(-2, 2, -2, 2, -20, 20);
  return cam;
}

void CameraDestroy(Camera3DPtr camera) {
  //
  free(camera);
}

void CameraTranslate(Camera3DPtr camera, float x, float y, float z) {
  camera->mPosition.x += x;
  camera->mPosition.y += y;
  camera->mPosition.z += z;
}

void CameraRotate(Camera3DPtr camera, float rx, float ry, float rz) {
  camera->mRotation.x += rx;
  camera->mRotation.y += ry;
  camera->mRotation.z += rz;
}

Matrix4f CameraGenerateViewMatrix(Camera3DPtr camera) {
  camera->mViewMatrix = Matrix4fCreateIdentity();
  Matrix4f translationMatrix =
      Matrix4fCreateTranslationMatrix(Float3Negate(camera->mPosition));
  Matrix4f rotationMatrix = Matrix4fCreateRotationMatrix(Float3Negate(camera->mRotation));

  camera->mViewMatrix = Matrix4fMultiply(&rotationMatrix, &translationMatrix);

  return camera->mViewMatrix;
}