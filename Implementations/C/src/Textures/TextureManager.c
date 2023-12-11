#include "TextureManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MAX_SIZE_OF_FULL_TEXTURE_FILE_PATH 128

TextureManagerPtr TextureManagerCreate() {
  TextureManagerPtr manager = malloc(sizeof(struct TextureManager));
  return manager;
}

void TextureManagerDestroy(TextureManagerPtr manager) {
  //
  free(manager);
}

static void GetFullTextureFilepath(char result[], const char *name) {
  static const char prefix[] = "res/textures/";
  static const char ext[] = ".png";
  memset(result, '\0', MAX_SIZE_OF_FULL_TEXTURE_FILE_PATH);

  strcpy(result, prefix);
  strcat(result, name);
  strcat(result, ext);
}

Texture TextureManagerLoadTextureFromFile(TextureManagerPtr manager,
                                          Textures textureID, const char *name,
                                          const TextureProperties props) {
  char fullpath[MAX_SIZE_OF_FULL_TEXTURE_FILE_PATH];
  GetFullTextureFilepath(fullpath, name);

  GLuint textureHandle;
  glGenTextures(1, &textureHandle);
  glBindTexture(GL_TEXTURE_2D, textureHandle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_set_flip_vertically_on_load(1);

  int width, height, channels;
  unsigned char *data = stbi_load(fullpath, &width, &height, &channels, 0);
  if (!data) {
    fprintf(stderr, "Could not load image with filepath %s\n", fullpath);
    return (Texture){
        .mTextureHandle = -1,
        .mWidth = -1,
        .mHeight = -1,
    };
  }

  int format = GL_RGBA;
  if(props & SRGB_SPACE)
    format = GL_SRGB;

  const int channelSetting = GL_RGB + channels - 3;
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, channelSetting,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  glBindTexture(GL_TEXTURE_2D, 0);

  return manager->mTextureList[textureID] = (Texture){
             .mTextureHandle = textureHandle,
             .mWidth = width,
             .mHeight = height,
         };
}