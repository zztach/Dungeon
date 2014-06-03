/* 
 * File:   TgaImageLoader.h
 * Author: zisis
 *
 * Created on February 22, 2014, 7:56 PM
 */

#ifndef TGAIMAGELOADER_H
#define	TGAIMAGELOADER_H
#include <iostream>
#include <glew.h>
#include "ImageLoader.h"

struct TGA_Header {
    // # of bytes of our TGA header
    GLubyte ID_Length;
    GLubyte ColorMapType;
    // this need to be 2 for uncompressed TGA file
    GLubyte imageType;
    GLubyte colorMapSpecification[5];
    GLshort xOrigin;
    GLshort yOrigin;
    GLshort imageWidth;
    GLshort imageHeight;
    GLubyte pixelDepth;
};

class TgaImageLoader : public ImageLoader {
public:
    TextureImage* load(string filename);
};

#endif	/* TGAIMAGELOADER_H */

