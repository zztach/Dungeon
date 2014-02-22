/* 
 * File:   TgaImageLoader.cpp
 * Author: zisis
 * 
 * Created on February 22, 2014, 7:53 PM
 */

#include "TgaImageLoader.h"

bool TgaImageLoader::load(string filename) 
{
    TGA_Header TGAheader;
    // load the file contents in binary format
    ifstream file(filename.data(), std::ios_base::binary);

    if (!file.is_open())
        return false;
    // read a number of "sizeof(TGAHeader) bytes and store them in TGAHeader"
    if (!file.read((char*) &TGAheader, sizeof (TGAheader)))
        return false;

    // in case of not uncompressed TGA header quit
    if (TGAheader.imageType != 2)
        return false;

    width = TGAheader.imageWidth;
    height = TGAheader.imageHeight;
    bpp = TGAheader.pixelDepth;

    if (width <= 0 || height <= 0 || (bpp != 24 && bpp != 32))
        return false;

    GLuint type = GL_RGBA;
    if (bpp == 24)
        type = GL_RGB;

    // allocate memory for our TGA
    GLuint bytesPerPixel = bpp / 8;
    GLuint imageSize = width * height * bytesPerPixel;

    imageData = new GLubyte[imageSize];
    if (imageData == NULL)
        return false;

    // make sure that you free memory when reading file fails
    if (!file.read((char*) imageData, imageSize)) {
        delete imageData;
        return false;
    }

    // BGR --> RGB
    for (GLuint i = 0; i < (int) imageSize; i += bytesPerPixel) {
        GLuint temp = imageData[i];
        imageData[i] = imageData[i + 2];
        imageData[i + 2] = temp;
    }
};
