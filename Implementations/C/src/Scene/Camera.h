#ifndef __CAMERA__
#define __CAMERA__

#include "Utilities/Transformations.h"

typedef struct CameraPhysics {
  float mVelocity;
  float mInertia;
}CameraPhysics;

typedef struct Camera3D {
  Point3f mPosition;
  Float3 mRotation;

  CameraPhysics mPhysicalAttribs;

  Matrix4f mViewMatrix;
  Matrix4f mProjMatrix;
} * Camera3DPtr;

// Need to impliment functions later
typedef struct CameraUI {
  struct {
    float mLeft, mRight;
    float mTop, mBottom;
    float mBack, mFront;
  } mOrthoData;

  Matrix4f mProjMatrix;

} * CameraUIPtr;

Camera3DPtr CameraCreate(float, float, float, float);
void CameraDestroy(Camera3DPtr);

void CameraTranslate(Camera3DPtr, float, float, float);
void CameraRotate(Camera3DPtr, float, float, float);

Matrix4f CameraGenerateViewMatrix(Camera3DPtr);
Matrix4f CameraGenerateProjectionMatrix(float, float, float, float);

#endif