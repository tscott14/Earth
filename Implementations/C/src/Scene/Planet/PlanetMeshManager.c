#include "PlanetMeshManager.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// https://prideout.net/blog/old/blog/index.html@p=48.html

#define DEGREES_TO_RADIANS (3.1415926535897 / 180.0f)

#define FACE_SIDE_LENGTH 20
#define VERT_SIDE_LENGTH (FACE_SIDE_LENGTH + 1)

#define ClearBuffer(buffer) memset(buffer, 0, sizeof(buffer))

typedef struct Face {
  Indicie i00, i01, i02, i03;
} Face;

typedef struct PlanetFaceVertices {
  Point3f mVertices[VERT_SIDE_LENGTH][VERT_SIDE_LENGTH];
} PlanetFaceVertices;

typedef struct PlanetFaceIndicies {
  Face mFaces[FACE_SIDE_LENGTH][FACE_SIDE_LENGTH];
} PlanetFaceIndicies;

static PlanetFaceVertices PLANET_VERTICES[6];
static PlanetFaceIndicies PLANET_INDICIES[6];

static void GenerateFaceBuffer(Point3f verticies[]) {
  static const float dTHETA = 90.0f / (VERT_SIDE_LENGTH - 1);
  static const float OFFSET = 45.0f;
  for (usize v = 0; v < VERT_SIDE_LENGTH; v++) {
    const float vTheta = v * dTHETA - OFFSET;
    const float vcos = (float)cos(vTheta * DEGREES_TO_RADIANS);
    const float vsin = (float)sin(vTheta * DEGREES_TO_RADIANS);
    for (usize u = 0; u < VERT_SIDE_LENGTH; u++) {
      const float uTheta = u * dTHETA - OFFSET;
      const float ucos = (float)cos(uTheta * DEGREES_TO_RADIANS);
      const float usin = (float)sin(uTheta * DEGREES_TO_RADIANS);
      verticies[u + v * VERT_SIDE_LENGTH] = Float3Create(usin / ucos, vsin / vcos, 1);
    }
  }
}

static void GenerateVertexPositions() {
  const Matrix4f transforms[6] = {
      Matrix4fCreateRotationMatrix(Float3CreateConstexpr(0, -90, 0)),
      Matrix4fCreateRotationMatrix(Float3CreateConstexpr(0, 90, 0)),
      Matrix4fCreateRotationMatrix(Float3CreateConstexpr(90, 0, 0)),
      Matrix4fCreateRotationMatrix(Float3CreateConstexpr(-90, 0, 0)),
      Matrix4fCreateRotationMatrix(Float3CreateConstexpr(0, 0, 0)),
      Matrix4fCreateRotationMatrix(Float3CreateConstexpr(0, 180, 0)),
  };

  Point3f buffer[VERT_SIDE_LENGTH][VERT_SIDE_LENGTH];
  ClearBuffer(buffer);
  GenerateFaceBuffer(&buffer[0][0]);

  ClearBuffer(PLANET_VERTICES);
  for (usize f = 0; f < 6; f++) {
    PlanetFaceVertices * const vert = &PLANET_VERTICES[f];
    for (usize v = 0; v < VERT_SIDE_LENGTH; v++) {
      for (usize u = 0; u < VERT_SIDE_LENGTH; u++) {
        const Point3f *oPoint3 = &buffer[u][v];
        const Point4f pPoint4 = *(Point4f*) oPoint3;
        const Point4f tPoint4 =
            Float4MulMatrix4f((Matrix4fPtr)&transforms[f], pPoint4);
        const Point3f *tPoint3 = (Point3f *)&tPoint4;
        vert->mVertices[u][v] = *tPoint3;
      }
    }
  }
}

static void GenerateVertexIndicies() {
  static const usize STRIDE = VERT_SIDE_LENGTH * VERT_SIDE_LENGTH;

  ClearBuffer(PLANET_INDICIES);
  for (usize f = 0; f < 6; f++) {
    PlanetFaceIndicies *indicies = &PLANET_INDICIES[f];
    for (usize v = 0; v < FACE_SIDE_LENGTH; v++) {
      for (usize u = 0; u < FACE_SIDE_LENGTH; u++) {
        const usize index = v * VERT_SIDE_LENGTH + u;
        const usize offset = STRIDE * f;

        const Indicie p0 = offset + index;
        const Indicie p1 = offset + index + 1;
        const Indicie p2 = offset + index + VERT_SIDE_LENGTH;
        const Indicie p3 = offset + index + VERT_SIDE_LENGTH + 1;

        indicies->mFaces[u][v].i00 = p0;
        indicies->mFaces[u][v].i01 = p1;
        indicies->mFaces[u][v].i02 = p3;
        indicies->mFaces[u][v].i03 = p2;
        
      }
    }
  }
}

static void GenerateStaticCubeSphereMesh() {
  GenerateVertexPositions();
  GenerateVertexIndicies();
}

static PlanetMesh GenerateVertexArrayObject() {
  static const usize VERTEX_POSITION_SIZE =
      sizeof(Point3f) * VERT_SIDE_LENGTH * VERT_SIDE_LENGTH * 6;
  static const usize VERTEX_INDICIES_SIZE =
      sizeof(Face) * FACE_SIDE_LENGTH * FACE_SIDE_LENGTH * 6;

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vertexPositionBuffer;
  glGenBuffers(1, &vertexPositionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBuffer);
  glBufferData(GL_ARRAY_BUFFER, VERTEX_POSITION_SIZE,
               PLANET_VERTICES->mVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point3f), NULL);

  GLuint vertexIndiciesBuffer;
  glGenBuffers(1, &vertexIndiciesBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndiciesBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, VERTEX_INDICIES_SIZE,
               PLANET_INDICIES->mFaces, GL_STATIC_DRAW);

  glBindVertexArray(0);

  return (PlanetMesh){
      .mVertexArrayHandle = vao,
      .mVertexPositionsBuffer = vertexPositionBuffer,
      .mLength = VERTEX_INDICIES_SIZE / sizeof(Indicie),
  };
}

PlanetMeshManager PlanetMeshManagerCreate() {
  GenerateStaticCubeSphereMesh();
  return (PlanetMeshManager){.mTerrainMesh = GenerateVertexArrayObject()};
}

void PlanetMeshManagerDestroy(PlanetMeshManager manager) {
  glDeleteVertexArrays(1, &manager.mTerrainMesh.mVertexArrayHandle);
  ClearBuffer(PLANET_VERTICES);
  ClearBuffer(PLANET_INDICIES);
}