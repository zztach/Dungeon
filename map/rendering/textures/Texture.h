/* 
 * File:   Texture.h
 * Author: zisis
 *
 * Created on March 8, 2014, 1:22 PM
 */

#ifndef TEXTURE_H
#define	TEXTURE_H
#include "TextureImage.h"
#include "../../utils/pugixml.hpp"
#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>

class Texture
{
public:
    Texture(TextureImage* imgLoader);
    ~Texture();
    void load();
    GLuint getTexture() const;
    
private:
    TextureImage* textureImage;
    GLuint texture;
};

#endif	/* TEXTURE_H */

