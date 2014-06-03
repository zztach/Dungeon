/* 
 * File:   BmpImageLoader.h
 * Author: zisis
 *
 * Created on March 11, 2014, 1:15 AM
 */

#ifndef BMPIMAGELOADER_H
#define	BMPIMAGELOADER_H

#include "ImageLoader.h"

class BmpImageLoader : public ImageLoader
{
public:
    BmpImageLoader();
    virtual ~BmpImageLoader();
    TextureImage* load(string filename);
private:
// Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos; // Position in the file where the actual data begins
    unsigned int imageSize; // = width*height*3
};

#endif	/* BMPIMAGELOADER_H */

