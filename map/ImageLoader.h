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

using std::string;
using std::ifstream;

class ImageLoader 
{
public:
    virtual bool load(string filename) = 0;
    GLubyte* getImageData(); 
};


#endif	/* IMAGELOADER_H */

