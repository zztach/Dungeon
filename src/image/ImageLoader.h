/* 
 * File:   ImageLoader.h
 * Author: zisis
 *
 * Created on February 22, 2014, 7:48 PM
 */

#ifndef IMAGELOADER_H
#define	IMAGELOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <glew.h>
#include "../rendering/textures/TextureImage.h"

using std::string;
using std::ifstream;

/**
 * ImageLoader implementations load data from raw image files (.BPM,.TGA) and convert them into
 * TextureImage objects. These are utilized from Texture objects which generate the final OpenGL
 * textures.
 * The contract that the implementations must honor is to return a TextureImage object from the image raw data.
 * 
 */
class ImageLoader 
{
public:
    virtual ~ImageLoader() {};
    
    /**
     * Reads the filename data and generates a TextureImage object.
     * 
     * @param filename the path to the filename which contains the texture image
     * @return A TextureImage object from the given filename
     */
    virtual TextureImage* load(string filename) = 0;
};


#endif	/* IMAGELOADER_H */

