#ifndef __TEXTURE__
#define __TEXTURE__

#include <GL/glew.h>

#include "Utilities/DataTypes.h"

typedef enum {
  SRGB_SPACE = 1 << 0,
} TextureProperties;

typedef enum Textures {
  TEST_TEXTURE_ID,
  BUMP_TEXTURE_ID,
  BUMP_NORMAL_TEXTURE_ID,
  NUM_OF_TEXTURES,
} Textures;

typedef struct Texture {
  GLuint mTextureHandle;
  usize mWidth, mHeight;
} Texture;

typedef struct TextureManager {
  Texture mTextureList[NUM_OF_TEXTURES];
} * TextureManagerPtr;

TextureManagerPtr TextureManagerCreate();
void TextureManagerDestroy(TextureManagerPtr);

Texture TextureManagerLoadTextureFromFile(TextureManagerPtr manager, Textures,
                                          const char *,
                                          const TextureProperties);

#endif