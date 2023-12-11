#ifndef __VECTOR_TYPES__
#define __VECTOR_TYPES__

#include "DataTypes.h"

#define PURE __attribute__((pure))

#define Float2CreateConstexpr(p1, p2)                                        \
  (struct Float2) { .x = p1, .y = p2 }
#define Float3CreateConstexpr(p1, p2, p3)                                    \
  (struct Float3) { .x = p1, .y = p2, .z = p3 }
#define Float4CreateConstexpr(p1, p2, p3, p4)                                \
  (struct Float4) { .x = p1, .y = p2, .z = p3, .w = p4 }

float FastReverseSqrt(float f);

Float2 Float2Create(float, float) PURE;
Float3 Float3Create(float, float, float) PURE;
Float4 Float4Create(float, float, float, float) PURE;

Float2 Float2AddFloat2(const Float2, const Float2) PURE;
Float3 Float3AddFloat3(const Float3, const Float3) PURE;
Float4 Float4AddFloat4(const Float4, const Float4) PURE;

Float2 Float2SubFloat2(const Float2, const Float2) PURE;
Float3 Float3SubFloat3(const Float3, const Float3) PURE;
Float4 Float4SubFloat4(const Float4, const Float4) PURE;

Float2 Float2MulFloat2(const Float2, const Float2) PURE;
Float3 Float3fMulFloat3(const Float3, const Float3) PURE;
Float4 Float4fMulFloat4(const Float4, const Float4) PURE;

Float2 Float2DivFloat2(const Float2, const Float2) PURE;
Float3 Float3fDivFloat3(const Float3, const Float3) PURE;
Float4 Float4fDivFloat4(const Float4, const Float4) PURE;

Float2 Float2Scale(const Float2, float) PURE;
Float3 Float3fScale(const Float3, float) PURE;
Float4 Float4fScale(const Float4, float) PURE;

Float2 Float2Negate(const Float2) PURE;
Float3 Float3Negate(const Float3) PURE;
Float4 Float4Negate(const Float4) PURE;

float FloatDotFloat2(const Float2, const Float2) PURE;
float FloatDotFloat3(const Float3, const Float3) PURE;
float FloatDotFloat4(const Float4, const Float4) PURE;

Float2 Float2CrossFloat2(const Float2, const Float2) PURE;
Float3 Float3CrossFloat3(const Float3, const Float3) PURE;
Float4 Float4CrossFloat4(const Float4, const Float4) PURE;

float FloatGetLength2Float2(const Float2) PURE;
float FloatGetLength2Float3(const Float3) PURE;
float FloatGetLength2Float4(const Float4) PURE;

int FloatCompare(float, float);
int Float2Compare(const Float2, const Float2) PURE;
int Float3Compare(const Float3, const Float3) PURE;
int Float4Compare(const Float4, const Float4) PURE;

float FloatLerpFloat(float, float, float) PURE;
Float2 Float2LerpFloat2(const Float2, const Float2, float) PURE;
Float3 Float3LerpFloat3(const Float3, const Float3, float) PURE;
Float4 Float4LerpFloat4(const Float4, const Float4, float) PURE;

float FloatGetLengthFloat2(const Float2) PURE;
float FloatGetLengthFloat3(const Float3) PURE;
float FloatGetLengthFloat4(const Float4) PURE;

float FloatGetDist2Float2(const Float2, const Float2) PURE;
float FloatGetDist2Float3(const Float3, const Float3) PURE;
float FloatGetDist2Float4(const Float4, const Float4) PURE;

float FloatGetDistFloat2(const Float2, const Float2) PURE;
float FloatGetDistFloat3(const Float3, const Float3) PURE;
float FloatGetDistFloat4(const Float4, const Float4) PURE;

Float2 Float2Normalize(const Float2) PURE;
Float3 Float3Normalize(const Float3) PURE;
Float4 Float4Normalize(const Float4) PURE;

Float2 Float2NormalizeFast(const Float2) PURE;
Float3 Float3NormalizeFast(const Float3) PURE;
Float4 Float4NormalizeFast(const Float4) PURE;

Float2 Float2ScaledNormalize(const Float2, float) PURE;
Float3 Float3ScaledNormalize(const Float3, float) PURE;
Float4 Float4ScaledNormalize(const Float4, float) PURE;

Float2 Float2ScaledNormalizeFast(const Float2, float) PURE;
Float3 Float3ScaledNormalizeFast(const Float3, float) PURE;
Float4 Float4ScaledNormalizeFast(const Float4, float) PURE;

Float3 Float3Rotate(float, float, float, float, float, float) PURE;

Float4 Float4MulMatrix4f(const Matrix4fPtr, const Float4);

Matrix4f Matrix4fCreate() PURE;
Matrix4f Matrix4fCreateIdentity() PURE;

Matrix4f Matrix4fCreateProspective(float, float, float, float) PURE;
Matrix4f Matrix4fCreateOrtho(float, float, float, float, float, float) PURE;

Matrix4f Matrix4fMultiply(const Matrix4fPtr, const Matrix4fPtr) PURE;

Matrix4f Matrix4fCreateTranslationMatrix(const Float3) PURE;
Matrix4f Matrix4fCreateRotationMatrix(const Float3) PURE;
Matrix4f Matrix4fScale(float) PURE;

void Matrix4fPrint(const Matrix4fPtr);

#endif