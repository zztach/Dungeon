/* 
 * File:   TextureImage.h
 * Author: zisis
 *
 * Created on March 11, 2014, 12:44 AM
 */

#ifndef TEXTUREIMAGE_H
#define	TEXTUREIMAGE_H

#include <glew.h>

class TextureImage
{
public:
    TextureImage(GLubyte* data, GLuint w, GLuint h, GLuint type) {
        this->imageData = data;
        this->width = w;
        this->height = h;
        this->type = type;
    }
    ~TextureImage() { delete imageData;}
    GLubyte* getImageData() { return imageData;}
    GLuint getWidth() {return width;}
    GLuint getHeight() {return height;}
    GLuint getType() {return type;}  
protected:
    // the image data read from the image file
    GLubyte* imageData;
    // width and height of our texture
    GLuint width;
    GLuint height;
    GLuint type;
};

#endif	/* TEXTUREIMAGE_H */

