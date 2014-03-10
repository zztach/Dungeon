#include "Texture.h"


Texture::Texture(TgaImageLoader* imgLoader)
{
    this->imgLoader = imgLoader;
    data = new float[512 * 512 * 4];
}

void Texture::load()
{
    // Define some data to upload into the texture
    //float * data = new float[512 * 512 * 4];

        // generate_texture() is a function that fills memory with image data
    generate_texture(data, 512, 512);
    glGenTextures(1, &texture);
    //SDL_Surface* textureImage;
    //textureImage = SDL_LoadBMP("stone_wall.bmp");
    glBindTexture(GL_TEXTURE_2D, texture);
// sunflower and GL_RGBA32F, GL_RGBA
   glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 512, 512);
                std::cout <<"Error : " << glGetError() << std::endl;
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 512, 512, 
//                    GL_RGBA, GL_FLOAT, data);
                   GL_RGB, GL_UNSIGNED_BYTE, imgLoader->getImageData());
                   //     GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels);

        std::cout << "OK";
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
           glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, imgLoader->getImageData());
     //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_FLOAT, data);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage->pixels);
    glBindTexture(GL_TEXTURE_2D, texture);        
}

/* this one must be passed into the shader using uniform variable */
GLuint Texture::getTexture() const
{
    return texture;
}

Texture::~Texture() {
    delete[] data;
    glDeleteTextures(1, &texture);
}

void Texture::generate_texture(float * data, int width, int height)
    {
        int x, y;

        for (y = 0; y < height; y++)
        {
            for (x = 0; x < width; x++)
            {
                data[(y * width + x) * 4 + 0] = (float)((x & y) & 0xFF) / 255.0f;
                data[(y * width + x) * 4 + 1] = (float)((x | y) & 0xFF) / 255.0f;
                data[(y * width + x) * 4 + 2] = (float)((x ^ y) & 0xFF) / 255.0f;
                data[(y * width + x) * 4 + 3] = 1.0f;
            }
        }
    }