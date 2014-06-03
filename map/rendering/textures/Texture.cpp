#include "Texture.h"

Texture::Texture(TextureImage* textureImage) {
    this->textureImage = textureImage;
}

void Texture::load() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, textureImage->getWidth(), textureImage->getHeight());
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureImage->getWidth(), textureImage->getHeight(),
            textureImage->getType(), GL_UNSIGNED_BYTE, textureImage->getImageData());
    glBindTexture(GL_TEXTURE_2D, texture);
}

/* this one must be passed into the shader using uniform variable */
GLuint Texture::getTexture() const {
    return texture;
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}