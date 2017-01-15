/* 
 * File:   ImageLoaderFactory.h
 * Author: zisis
 *
 * Created on March 26, 2014, 10:38 PM
 */

#ifndef IMAGELOADERFACTORY_H
#define	IMAGELOADERFACTORY_H

#include "ImageLoader.h"
#include "BmpImageLoader.h"
#include "TgaImageLoader.h"

/**
 * Factory class that returns  ImageLoader implementations
 */
class ImageLoaderFactory {
public:
    ImageLoaderFactory();
    /**
     * Responsible for creating the proper ImageLoader implementation based on
     * the incoming imageType
     * 
     * @param imageType the extention of the filename (. not included)
     * @return an ImageLoader implementation
     */
    ImageLoader* getImageLoader(string& imageType) const;
    virtual ~ImageLoaderFactory();
private:
    
};

#endif	/* IMAGELOADERFACTORY_H */

