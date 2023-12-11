#include "TextureLoaders.hpp"

#include <GL/glew.h>
#include "stb_image/stb_image.h"

static const auto TEXTURE_ROOT_FILEPATH = std::string("res/textures/");

auto CubemapTextureLoader::GenerateTexture(const std::string &dirname) -> Ref<BasicTexture>
{
    static const std::string IMAGE_NAMES[] = {
        std::string("panorama_0.jpg"),
        std::string("panorama_1.jpg"),
        std::string("panorama_2.jpg"),
        std::string("panorama_3.jpg"),
        std::string("panorama_4.jpg"),
        std::string("panorama_5.jpg"),
    };

    const auto fulldirpath = TEXTURE_ROOT_FILEPATH + dirname + "/";

    printf("Loading Texture \'%s\'\n", fulldirpath.c_str());

    TextureHandle texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    stbi_set_flip_vertically_on_load(0);
    for (Size i = 0; i < 6; i++)
    {
        const std::string filepath = fulldirpath + IMAGE_NAMES[i];
        printf("\t- Loading %s Cubemap Texture: \'%s\'\n", dirname.c_str(), filepath.c_str());

        int width, height, nrChannels;
        auto data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB + nrChannels - 3, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            fprintf(stderr, "Cubemap texture file not found %s\n", filepath.c_str());
            stbi_image_free(data);
            exit(1);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return std::make_shared<BasicTexture>(texture);
}
