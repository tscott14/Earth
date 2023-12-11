#ifndef __PLANET__
#define __PLANET__

#include "Utilities/Transformations.h"
#include "Shader/Shader.h"
#include "PlanetMeshManager.h"
#include "PlanetSettings.h"

enum PlanetFaces {
    PLANET_FACE_RIGHT,
    PLANET_FACE_LEFT,
    PLANET_FACE_TOP,
    PLANET_FACE_BOTTOM,
    PLANET_FACE_BACK,
    PLANET_FACE_FRONT,
};

typedef struct Planet {
    Point3f mPosition;
    Float3 mRotation;

    PlanetGenSettings  mSettings;

    struct Matrix4f mModelMatrix;

    PlanetMeshManager mPlanetMeshManager;

    PlanetShader mPlanetShader;
} *PlanetPtr;

PlanetPtr PlanetCreate();
void PlanetDestroy(PlanetPtr);
void PlanetUpdate(PlanetPtr);

Matrix4f PlanetGenerateModelMatrix(PlanetPtr);

#endif