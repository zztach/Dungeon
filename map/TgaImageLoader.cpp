/* 
 * File:   TgaImageLoader.cpp
 * Author: zisis
 * 
 * Created on February 22, 2014, 7:53 PM
 */

#include "TgaImageLoader.h"

TgaImageLoader::TgaImageLoader() {}

TgaImageLoader::~TgaImageLoader()
{
    delete[] imageData;
}
bool TgaImageLoader::load(string filename) 
{

    // Open the file
FILE * file = fopen(filename.c_str(),"rb");
if (!file)                              {printf("Image could not be opened\n"); return 0;}

if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    return false;
}

if ( header[0]!='B' || header[1]!='M' ){
    printf("Not a correct BMP file\n");
    return 0;
}
// Read ints from the byte array
dataPos    = *(int*)&(header[0x0A]);
imageSize  = *(int*)&(header[0x22]);
width      = *(int*)&(header[0x12]);
height     = *(int*)&(header[0x16]);
std::cout << "WH : "<< width << " : " << height << std::endl;
// Some BMP files are misformatted, guess missing information
if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
if (dataPos==0)      dataPos=54; // The BMP header is done that way

// Create a buffer
imageData = new unsigned char [imageSize];

// Read the actual data from the file into the buffer
fread(imageData,1,imageSize,file);
      std::cout << " Loading BMP " << std::endl;
//Everything is in memory now, the file can be closed
fclose(file);
return true;
}

bool TgaImageLoader::load2(string filename) 
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
    std::cout << width << " " << height << " " << bpp << " " << type << std::endl;
    // allocate memory for our TGA
    GLuint bytesPerPixel = bpp / 8;
    GLuint imageSize = width * height * bytesPerPixel;
    std::cout << "image size " << imageSize << std::endl;
    imageData = new GLubyte[imageSize];
    std::cout << sizeof(imageData) << std::endl;
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
        //std::cout << sizeof(imageData) << std::endl;
    }
}

GLubyte* TgaImageLoader::getImageData() const
{
    return imageData;
}
