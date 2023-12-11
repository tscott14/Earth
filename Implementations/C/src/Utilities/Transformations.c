#include "Transformations.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include "DataTypes.h"

#define TORADIANS 3.14159265358f / 180.0f

float FastReverseSqrt(float f) {
  // From Quake
  long i;
  float x2, y;
  const float threehalfs = 1.5f;

  x2 = f * 0.5f;
  y = f;
  i = *(long *)&y;

  i = 0x5f3759df - (i >> 1);

  y = *(float *)&i;
  y = y * (threehalfs - (x2 * y * y));
  y = y * (threehalfs - (x2 * y * y));
  y = y * (threehalfs - (x2 * y * y));
  return y;
}

Float2 Float2Create(float x, float y) {
  return (struct Float2){.x = x, .y = y};
}

Float3 Float3Create(float x, float y, float z) {
  return (struct Float3){.x = x, .y = y, .z = z};
}

Float4 Float4Create(float x, float y, float z, float w) {
  return (struct Float4){.x = x, .y = y, .z = z, .w = w};
}

Float2 Float2AddFloat2(const Float2 l, const Float2 r) {
  return Float2Create(l.x + r.x, l.y + r.y);
}

Float3 Float3AddFloat3(const Float3 l, const Float3 r) {
  return Float3Create(l.x + r.x, l.y + r.y, l.z + r.z);
}

Float4 Float4AddFloat4(const Float4 l, const Float4 r) {
  return Float4Create(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
}

Float2 Float2SubFloat2(const Float2 l, const Float2 r) {
  return Float2Create(l.x - r.x, l.y - r.y);
}

Float3 Float3SubFloat3(const Float3 l, const Float3 r) {
  return Float3Create(l.x - r.x, l.y - r.y, l.z - r.z);
}

Float4 Float4SubFloat4(const Float4 l, const Float4 r) {
  return Float4Create(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
}

Float2 Float2MulFloat2(const Float2 l, const Float2 r) {
  return Float2Create(l.x * r.x, l.y * r.y);
}

Float3 Float3MulFloat3(const Float3 l, const Float3 r) {
  return Float3Create(l.x * r.x, l.y * r.y, l.z * r.z);
}

Float4 Float4MulFloat4(const Float4 l, const Float4 r) {
  return Float4Create(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w);
}

Float2 Float2DivFloat2(const Float2 l, const Float2 r) {
  return Float2Create(l.x / r.x, l.y / r.y);
}

Float3 Float3DivFloat3(const Float3 l, const Float3 r) {
  return Float3Create(l.x / r.x, l.y / r.y, l.z / r.z);
}

Float4 Float4DivFloat4(const Float4 l, const Float4 r) {
  return Float4Create(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
}

Float2 Float2Scale(const Float2 v, float f) {
  return Float2Create(v.x * f, v.y * f);
}
Float3 Float3Scale(const Float3 v, float f) {
  return Float3Create(v.x * f, v.y * f, v.z * f);
}
Float4 Float4Scale(const Float4 v, float f) {
  return Float4Create(v.x * f, v.y * f, v.z * f, v.w * f);
}

Float2 Float2Negate(const Float2 v) { return Float2Create(-v.x, -v.y); }

Float3 Float3Negate(const Float3 v) { return Float3Create(-v.x, -v.y, -v.z); }

Float4 Float4Negate(const Float4 v) {
  return Float4Create(-v.x, -v.y, -v.z, -v.w);
}

float FloatDotFloat2(const Float2 l, const Float2 r) {
  return l.x * r.x + l.y + r.y;
}

float FloatDotFloat3(const Float3 l, const Float3 r) {
  return l.x * r.x + l.y + r.y + l.z * r.z;
}

float FloatDotFloat4(const Float4 l, const Float4 r) {
  return l.x * r.x + l.y + r.y + l.z * r.z + l.w * r.w;
}

Float2 Float2CrossFloat2(const Float2 l, const Float2 r) {
  assert(0);
  return Float2Create(0, 0);
}

Float3 Float3CrossFloat3(const Float3 l, const Float3 r) {
  return Float3Create(l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z,
                      l.x * r.y - l.y * r.x);
}

Float4 Float4CrossFloat4(const Float4 l, const Float4 r) {
  assert(0);
  return Float4Create(0, 0, 0, 0);
}

float FloatGetLength2Float2(const Float2 v) { return v.x * v.x + v.y * v.y; }

float FloatGetLength2Float3(const Float3 v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

float FloatGetLength2Float4(const Float4 v) {
  return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

int FloatCompare(float l, float r) {
  static float EPSILON = 1e-3;
  const float diff = r - l;
  const int equal = diff < EPSILON && diff > -EPSILON;
  const int greater = r > l;
  return -1 + equal + !equal * 2 * greater;
}

int Float2Compare(const Float2 l, const Float2 r) {
  const float lenl = FloatGetLength2Float2(l);
  const float lenr = FloatGetLength2Float2(r);
  const int equal = FloatCompare(lenl, lenr) == 0;
  const int greater = lenl > lenr;
  return -1 + equal + !equal * 2 * greater;
}

int Float3Compare(const Float3 l, const Float3 r) {
  const float lenl = FloatGetLength2Float3(l);
  const float lenr = FloatGetLength2Float3(r);
  const int equal = FloatCompare(lenl, lenr) == 0;
  const int greater = lenl > lenr;
  return -1 + equal + !equal * 2 * greater;
}

int Float4Compare(const Float4 l, const Float4 r) {
  const float lenl = FloatGetLength2Float4(l);
  const float lenr = FloatGetLength2Float4(r);
  const int equal = FloatCompare(lenl, lenr) == 0;
  const int greater = lenl > lenr;
  return -1 + equal + !equal * 2 * greater;
}

float FloatLerpFloat(float l, float r, float f) { //
  return l + (r - l) * f;
}

Float2 Float2LerpFloat2(const Float2 l, const Float2 r, float f) {
  const float x = FloatLerpFloat(l.x, r.x, f);
  const float y = FloatLerpFloat(l.y, r.y, f);
  return Float2Create(x, y);
}

Float3 Float3LerpFloat3(const Float3 l, const Float3 r, float f) {
  const float x = FloatLerpFloat(l.x, r.x, f);
  const float y = FloatLerpFloat(l.y, r.y, f);
  const float z = FloatLerpFloat(l.z, r.z, f);
  return Float3Create(x, y, z);
}

Float4 Float4LerpFloat4(const Float4 l, const Float4 r, float f) {
  const float x = FloatLerpFloat(l.x, r.x, f);
  const float y = FloatLerpFloat(l.y, r.y, f);
  const float z = FloatLerpFloat(l.z, r.z, f);
  const float w = FloatLerpFloat(l.w, r.w, f);
  return Float4Create(x, y, z, w);
}

float FloatGetLengthFloat2(const Float2 vec) {
  return (float)sqrt(FloatGetLength2Float2(vec));
}

float FloatGetLengthFloat3(const Float3 vec) {
  return (float)sqrt(FloatGetLength2Float3(vec));
}

float FloatGetLengthFloat4(const Float4 vec) {
  return (float)sqrt(FloatGetLength2Float4(vec));
}

float FloatGetDist2Float2(const Float2 v1, const Float2 v2) {
  const Float2 diff = Float2SubFloat2(v1, v2);
  return FloatGetLength2Float2(diff);
}

float FloatGetDist2Float3(const Float3 v1, const Float3 v2) {
  const Float3 diff = Float3SubFloat3(v1, v2);
  return FloatGetLength2Float3(diff);
}

float FloatGetDist2Float4(const Float4 v1, const Float4 v2) {
  const Float4 diff = Float4SubFloat4(v1, v2);
  return FloatGetLength2Float4(diff);
}

float FloatGetDistFloat2(const Float2 vec1, const Float2 vec2) {
  return (float)sqrt(FloatGetDist2Float2(vec1, vec2));
}

float FloatGetDistFloat3(const Float3 vec1, const Float3 vec2) {
  return (float)sqrt(FloatGetDist2Float3(vec1, vec2));
}

float FloatGetDistFloat4(const Float4 vec1, const Float4 vec2) {
  return (float)sqrt(FloatGetDist2Float4(vec1, vec2));
}

Float2 Float2Normalize(const Float2 vec) {
  const float len = sqrt(FloatGetLength2Float2(vec));
  return Float2Create(vec.x / len, vec.y / len);
}
Float3 Float3Normalize(const Float3 vec) {
  const float len = sqrt(FloatGetLength2Float3(vec));
  return Float3Create(vec.x / len, vec.y / len, vec.z / len);
}

Float4 Float4Normalize(const Float4 vec) {
  const float len = sqrt(FloatGetLength2Float4(vec));
  return Float4Create(vec.x / len, vec.y / len, vec.z / len, vec.w / len);
}

Float2 Float2NormalizeFast(const Float2 v) {
  const float length2 = FloatGetLength2Float2(v);
  const float rsqrt = FastReverseSqrt(length2);
  return Float2Create(rsqrt * v.x, rsqrt * v.y);
}
Float3 Float3NormalizeFast(const Float3 v) {
  const float length2 = FloatGetLength2Float3(v);
  const float rsqrt = FastReverseSqrt(length2);
  return Float3Create(rsqrt * v.x, rsqrt * v.y, rsqrt * v.z);
}
Float4 Float4NormalizeFast(const Float4 v) {
  const float length2 = FloatGetLength2Float4(v);
  const float rsqrt = FastReverseSqrt(length2);
  return Float4Create(rsqrt * v.x, rsqrt * v.y, rsqrt * v.z, rsqrt * v.w);
}

Float2 Float2ScaledNormalize(const Float2 vec, float scale) {
  const Float2 normalizedVec = Float2Normalize(vec);
  return Float2Scale(normalizedVec, scale);
}

Float3 Float3ScaledNormalize(const Float3 vec, float scale) {
  const Float3 normalizedVec = Float3Normalize(vec);
  return Float3Scale(normalizedVec, scale);
}

Float4 Float4ScaledNormalize(const Float4 vec, float scale) {
  const Float4 normalizedVec = Float4Normalize(vec);
  return Float4Scale(normalizedVec, scale);
}

Float2 Float2ScaledNormalizeFast(const Float2 v, float s) {
  const Float2 normalizedVec = Float2NormalizeFast(v);
  return Float2Scale(normalizedVec, s);
}

Float3 Float3ScaledNormalizeFast(const Float3 v, float s) {
  const Float3 normalizedVec = Float3NormalizeFast(v);
  return Float3Scale(normalizedVec, s);
}

Float4 Float4ScaledNormalizeFast(const Float4 v, float s) {
  const Float4 normalizedVec = Float4NormalizeFast(v);
  return Float4Scale(normalizedVec, s);
}

Float4 Float4Rotate(const Float4 pos, const Float3 rot) {
  struct Matrix4f rotmat = Matrix4fCreateRotationMatrix(rot);
  return Float4MulMatrix4f(&rotmat, pos);
}

Float4 Float4MulMatrix4f(const Matrix4fPtr mat, const Float4 vec) {
  Float4 res = Float4Create(0, 0, 0, 0);

  for (usize r = 0; r < 4; r++) {
    res.arr[r] = vec.arr[0] * mat->mData[r * 4 + 0] +
                 vec.arr[1] * mat->mData[r * 4 + 1] +
                 vec.arr[2] * mat->mData[r * 4 + 2] +
                 vec.arr[3] * mat->mData[r * 4 + 3];
  }

  return res;
}

Matrix4f Matrix4fCreate() {
  Matrix4f res;
  memset(res.mData, 0, sizeof(struct Matrix4f));
  return res;
}
Matrix4f Matrix4fCreateIdentity() {
  Matrix4f res = Matrix4fCreate();
  res.m00 = 1;
  res.m11 = 1;
  res.m22 = 1;
  res.m33 = 1;
  return res;
}

Matrix4f Matrix4fCreateProspective(float fov, float aspect, float znear,
                                   float zfar) {
  Matrix4f res = Matrix4fCreateIdentity();

  float tanHalfFOV = (float)tan(fov * TORADIANS / 2.0f);

  res.m00 = 1.0f / (tanHalfFOV * aspect);
  res.m11 = 1.0f / tanHalfFOV;
  res.m22 = -(zfar + znear) / (zfar - znear);
  res.m23 = -1.0f;
  res.m32 = -2.0f * (zfar * znear) / (zfar - znear);
  res.m33 = 0.0f;

  return res;
}

Matrix4f Matrix4fCreateOrthographic(float left, float right, float bottom,
                                    float top, float near, float far) {
  Matrix4f res = Matrix4fCreateIdentity();

  float width = right - left;
  float height = top - bottom;
  float depth = far - near;

  res.m00 = 2 / width;
  res.m11 = 2 / height;
  res.m22 = -2 / depth;
  res.m30 = -(right + left) / width;
  res.m31 = -(top + bottom) / height;
  res.m32 = -(far + near) / depth;
  res.m33 = 1;

  return res;
}

Matrix4f Matrix4fMultiply(const Matrix4fPtr left, const Matrix4fPtr right) {
  Matrix4f res = Matrix4fCreateIdentity();
  for (usize r = 0; r < 4; r++) {
    for (usize c = 0; c < 4; c++) {
      res.mData[c * 4 + r] = left->mData[0 * 4 + r] * right->mData[c * 4 + 0] +
                             left->mData[1 * 4 + r] * right->mData[c * 4 + 1] +
                             left->mData[2 * 4 + r] * right->mData[c * 4 + 2] +
                             left->mData[3 * 4 + r] * right->mData[c * 4 + 3];
    }
  }
  return res;
}

Matrix4f Matrix4fCreateTranslationMatrix(const Float3 trans) {
  Matrix4f res = Matrix4fCreateIdentity();
  res.m30 = trans.x;
  res.m31 = trans.y;
  res.m32 = trans.z;
  return res;
}

Matrix4f Matrix4fCreateRotationMatrix(const Float3 rot) {
  Matrix4f mx = Matrix4fCreateIdentity();
  Matrix4f my = Matrix4fCreateIdentity();
  Matrix4f mz = Matrix4fCreateIdentity();
  Matrix4f res = Matrix4fCreateIdentity();

  float x = rot.x * TORADIANS;
  float y = rot.y * TORADIANS;
  float z = rot.z * TORADIANS;

  float sx = sin(x);
  float cx = cos(x);
  float sy = sin(y);
  float cy = cos(y);
  float sz = sin(z);
  float cz = cos(z);

  mx.m11 = cx;
  mx.m12 = sx;
  mx.m21 = -sx;
  mx.m22 = cx;

  my.m00 = cy;
  my.m02 = -sy;
  my.m20 = sy;
  my.m22 = cy;

  mz.m00 = cz;
  mz.m01 = sz;
  mz.m10 = -sz;
  mz.m11 = cz;

  res = Matrix4fMultiply(&res, &mx);
  res = Matrix4fMultiply(&res, &mz);
  res = Matrix4fMultiply(&res, &my);

  return res;
}

Matrix4f Matrix4fScale(float scale) {
  Matrix4f res = Matrix4fCreateIdentity();
  res.m00 = scale;
  res.m11 = scale;
  res.m22 = scale;
  return res;
}

void Matrix4fPrint(const Matrix4fPtr mat) {
  for (usize r = 0; r < 4; r++) {
    for (usize c = 0; c < 4; c++) {
      printf("%f, ", mat->mData[c * 4 + r]);
    }
    printf("\n");
  }
  printf("\n");
}