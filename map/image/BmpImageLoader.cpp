/* 
 * File:   BmpImageLoader.cpp
 * Author: zisis
 * 
 * Created on March 11, 2014, 1:15 AM
 */

#include "BmpImageLoader.h"

BmpImageLoader::BmpImageLoader() {
}

BmpImageLoader::~BmpImageLoader() {
}

TextureImage* BmpImageLoader::load(string filename) {

    // Open the file
    FILE * file = fopen(filename.c_str(), "rb");
    if (!file) {
        printf("Image could not be opened\n");
        return NULL;
    }

    if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return NULL;
    }

    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a correct BMP file\n");
        return NULL;
    }
    // Read ints from the byte array
    dataPos = *(int*) &(header[0x0A]);
    imageSize = *(int*) &(header[0x22]);
    GLuint width = *(int*) &(header[0x12]);
    GLuint height = *(int*) &(header[0x16]);
    
    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0) imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0) dataPos = 54; // The BMP header is done that way

    // Create a buffer
    GLubyte* imageData = new unsigned char [imageSize];

    // Read the actual data from the file into the buffer
    fread(imageData, 1, imageSize, file);
    std::cout << " Loading BMP " << std::endl;
    //Everything is in memory now, the file can be closed
    fclose(file);
    return new TextureImage(imageData, width, height, GL_RGB);
}

