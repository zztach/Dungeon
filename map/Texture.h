/* 
 * File:   Texture.h
 * Author: zisis
 *
 * Created on March 8, 2014, 1:22 PM
 */

#ifndef TEXTURE_H
#define	TEXTURE_H
#include "TgaImageLoader.h"
#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>

class Texture
{
public:
    Texture(TgaImageLoader* imgLoader);
    ~Texture();
    void load();
    GLuint getTexture() const;
    
private:
    void generate_texture(float * data, int width, int height);
    TgaImageLoader* imgLoader;
    float * data;
    GLuint texture;
};

#endif	/* TEXTURE_H */

