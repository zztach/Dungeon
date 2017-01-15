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

/**
 * Responsible for loading OpenGL textures out of TextureImage objects. 
 */
class Texture
{
public:
    Texture(TextureImage* imgLoader);
    ~Texture();
    /**
     * Generates and binds an OpenGL texture based on the information provided inside TextureImage.
     * Inside this function the texture identifier is generated
     */
    void load();
    GLuint getTexture() const;
    
private:
    /* the object containing all the texture information */    
    TextureImage* textureImage;
    /* the texture identifier returned by OpenGL*/
    GLuint texture;
};

#endif	/* TEXTURE_H */

