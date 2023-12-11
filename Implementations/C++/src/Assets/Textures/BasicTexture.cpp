#include "BasicTexture.hpp"

#include <GL/glew.h>

auto BasicTexture::Bind(int loc) const -> void
{
    glActiveTexture(GL_TEXTURE0 + loc);
    glBindTexture(GL_TEXTURE_2D, mTextureHandle);
}

auto BasicTexture::Unbind() const -> void
{
    glBindTexture(GL_TEXTURE_2D, 0);
}