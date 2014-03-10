/* 
 * File:   TgaImageLoader.h
 * Author: zisis
 *
 * Created on February 22, 2014, 7:56 PM
 */

#ifndef TGAIMAGELOADER_H
#define	TGAIMAGELOADER_H
#include "ImageLoader.h"
#include <iostream>
#include <glew.h>

struct TGA_Header
{
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

class TgaImageLoader: public ImageLoader 
{
public:
    TgaImageLoader();
    ~TgaImageLoader();
    bool load(string filename);
    bool load2(string filename);
    GLubyte* getImageData() const;
// Variables
private:
	// the image data read from the image file
	GLubyte* imageData;
	// bits per pixel
	unsigned int bpp;
	// width and height of our texture
	unsigned int width;
	unsigned int height;
        // Data read from the header of the BMP file
        unsigned char header[54]; // Each BMP file begins by a 54-bytes header
        unsigned int dataPos;     // Position in the file where the actual data begins
        unsigned int imageSize;   // = width*height*3
};

#endif	/* TGAIMAGELOADER_H */

