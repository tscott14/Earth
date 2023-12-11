#include "BasicMesh.hpp"

#include <GL/glew.h>

auto BasicMesh::Bind() const -> void
{
    glBindVertexArray(mVertexArrayHandle);
}

auto BasicMesh::Unbind() const -> void
{
    glBindVertexArray(0);
}