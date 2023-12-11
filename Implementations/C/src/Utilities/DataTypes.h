#ifndef __DATA_TYPES__
#define __DATA_TYPES__

#include <stdint.h>

typedef unsigned int usize;
typedef int size;

typedef struct Float2 Point2f;
typedef struct Float3 Point3f;
typedef struct Float4 Point4f;
typedef struct Float2 Vector2f;
typedef struct Float3 Vector3f;
typedef struct Float4 Vector4f;
typedef struct Matrix4f Matrix4f;

typedef struct Float2 {
  union {
    struct {
      float x, y;
    };
    struct {
      float u, v;
    };
    struct {
      float s, t;
    };
    struct {
        float mTheta, mPhi;
    };
    float arr[2];
  };
  ;
} Float2;

typedef struct Float3 {
  union {
    struct {
      float x, y, z;
    };
    struct {
      float r, g, b;
    };
    struct {
        float mRadius, mTheta, mPhi;
    };
    float arr[3];
  };
} Float3;

typedef struct Float4 {
  union {
    struct {
      float x, y, z, w;
    };
    struct {
      float r, g, b, a;
    };
    float arr[4];
  };
} Float4;

typedef struct Matrix4f {
  union {
    struct {
      float m00, m01, m02, m03;
      float m10, m11, m12, m13;
      float m20, m21, m22, m23;
      float m30, m31, m32, m33;
    };
    struct {
      Float4 mColumns[4];
    };
    float mData[4 * 4];
  };
} * Matrix4fPtr;

#endif