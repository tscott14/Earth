#ifndef MESH_LOADERS_HPP
#define MESH_LOADERS_HPP

#include "Assets/Meshes/Mesh.hpp"

class UnitQuadMeshLoader
{
    private:
    public:
        static auto GenerateMesh() -> Ref<BasicMesh>;
};

class PlanetMeshLoader
{
    private:
    public:
        static auto GenerateMesh() -> Ref<BasicMesh>;
};

class SkyboxMeshLoader
{
    private:
    public:
        static auto GenerateMesh() -> Ref<BasicMesh>;
};

#endif