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

class ImageLoaderFactory {
public:
    ImageLoaderFactory();
    ImageLoader* getImageLoader(string& imageType) const;
    virtual ~ImageLoaderFactory();
private:
    
};

#endif	/* IMAGELOADERFACTORY_H */

