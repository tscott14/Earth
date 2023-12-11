#ifndef __PLANET_MESH_MANAGER__
#define __PLANET_MESH_MANAGER__

#include <GL/glew.h>
#include <stdint.h>

#include "Utilities/Transformations.h"

typedef uint16_t Indicie;

typedef struct PlanetMesh {
  GLuint mVertexArrayHandle;
  GLuint mVertexPositionsBuffer;
  usize mLength;
} PlanetMesh;

typedef struct PlanetMeshManager {
  PlanetMesh mTerrainMesh;
} PlanetMeshManager;

PlanetMeshManager PlanetMeshManagerCreate();
void PlanetMeshManagerDestroy(PlanetMeshManager);

void PlanetMeshManagerRefresh(PlanetMeshManager*, const Float3);

#endif