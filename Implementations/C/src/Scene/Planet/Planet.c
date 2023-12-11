#include "Planet.h"

#include <stdlib.h>

static struct PlanetGenSettings PlanetConfigureSettings() {
  return (struct PlanetGenSettings) {
    .mRadius = 1,
    .mLacunarity = 2,
    .mGain = 0.5,
    .mOctives = 6,
  };
}

PlanetPtr PlanetCreate() {
  PlanetPtr planet = (PlanetPtr)malloc(sizeof(struct Planet));

  planet->mPosition = Float3Create(0, 0, 0);
  planet->mRotation = Float3Create(0, 0, 0);
  planet->mSettings = PlanetConfigureSettings();

  planet->mModelMatrix = PlanetGenerateModelMatrix(planet);

  planet->mPlanetMeshManager = PlanetMeshManagerCreate();

  planet->mPlanetShader = PlanetShaderCreate();

  return planet;
}

void PlanetDestroy(PlanetPtr planet) {
  ShaderProgramDestroy(planet->mPlanetShader.mShaderProgramHandle);
  PlanetMeshManagerDestroy(planet->mPlanetMeshManager);
  free(planet);
}

void PlanetUpdate(PlanetPtr planet) {
  //planet->mRotation.y += 1;
  //
}

struct Matrix4f PlanetGenerateModelMatrix(PlanetPtr planet) {
  Matrix4f rotationMatrix =
      Matrix4fCreateRotationMatrix(planet->mRotation);
  Matrix4f translationMatrix =
      Matrix4fCreateTranslationMatrix(planet->mPosition);
  return planet->mModelMatrix =
             Matrix4fMultiply(&translationMatrix, &rotationMatrix);
}