#include "texture.h"
#include "vendor/stb_image/stb_image.h"
#include <iostream>

unsigned int Texture::idcount = 1;

Texture::Texture() {
    _id = idcount;
    ++idcount;
}

void Texture::createCubemap(std::vector<std::string> filePaths) {
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &_id);
    glTextureStorage2D(_id, 1, GL_RGB8, 2048,2048);
    stbi_set_flip_vertically_on_load(0);

    for (size_t i = 0; i < filePaths.size(); ++i) {
        int w, h, nchan;
        auto img = loadImage(filePaths[i], w,h,nchan);
        glTextureSubImage3D(_id, 0, 0, 0, i, w, h, 1, GL_RGB, GL_UNSIGNED_BYTE, static_cast<void*>(img));
        stbi_image_free(img);
    }
}

void Texture::createTexture2D(const std::string& filePath) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* image = loadImage(filePath, width, height, channels);

    glCreateTextures(GL_TEXTURE_2D, 1, &_id);
    glTextureStorage2D(_id, 1, GL_RGB8, width, height);
    glTextureSubImage2D(_id, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, static_cast<void*>(image));
    glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image);

}

Texture::~Texture() {
    glDeleteTextures(1, &_id);
}

void Texture::bind() const {
    glBindTextureUnit(0, _id);
}

void Texture::unbind() const {
}

unsigned char* Texture::loadImage(std::string filepath, int& w, int& h, int& nChannels) {
    unsigned char* image = stbi_load(filepath.c_str(), &w, &h, &nChannels, STBI_rgb);
    if (image == nullptr) {
        std::cerr << "Failed load image" << std::endl;
    }
    return image;
}
