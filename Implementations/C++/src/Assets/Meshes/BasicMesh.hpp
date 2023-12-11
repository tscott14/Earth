#ifndef BASIC_MESH_HPP
#define BASIC_MESH_HPP

#include <cstdint>

#include "PDH.hpp"
#include "Assets/Asset.hpp"

using VertexArrayHandle = unsigned int;
using VertexBufferObjectHandle = unsigned int;
using Indice = uint32_t;

class BasicMesh : public Asset
{
private:
protected:
    VertexArrayHandle mVertexArrayHandle{};
    Size mLength{};

public:
    BasicMesh(VertexArrayHandle vao, Size length)
        : Asset(AssetType::MESHES),
          mVertexArrayHandle(vao), mLength(length)
    {
    }

    auto Bind() const -> void;
    auto Unbind() const -> void;

    auto GetVertexArrayHandle() const -> VertexArrayHandle { return mVertexArrayHandle; }
    auto GetLength() const -> Size { return mLength; };
};

#endif