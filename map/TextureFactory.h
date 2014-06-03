/* 
 * File:   TextureFactory.h
 * Author: zisis
 *
 * Created on March 27, 2014, 12:08 AM
 */

#ifndef TEXTUREFACTORY_H
#define	TEXTUREFACTORY_H

#include "image/ImageLoaderFactory.h"
#include "Texture.h"
#include <vector>
#include <map>

class TextureFactory {
public:
    TextureFactory();
    TextureFactory(const TextureFactory& orig);
    void loadTextures();
    Texture* getTexture(const string name) const;
    virtual ~TextureFactory();
private:
    std::map<string,Texture*> textures;
    ImageLoaderFactory* imgLoaderFactory;
};

#endif	/* TEXTUREFACTORY_H */

