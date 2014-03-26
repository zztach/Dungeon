/* 
 * File:   ImageLoaderFactory.cpp
 * Author: zisis
 * 
 * Created on March 26, 2014, 10:38 PM
 */

#include "ImageLoaderFactory.h"

ImageLoaderFactory::ImageLoaderFactory() 
{
    
}

ImageLoaderFactory::ImageLoaderFactory(const ImageLoaderFactory& orig) 
{
    
}

ImageLoaderFactory::~ImageLoaderFactory() 
{
    
}

ImageLoader* ImageLoaderFactory::getImageLoader(string& imageType) const
{
    if (imageType.compare("bpm") == 0) {
        return new BmpImageLoader();
    } else if (imageType.compare("tga") == 0) {
        return new TgaImageLoader();
    } else {
        return NULL;
    }

}

