/* 
 * File:   TextureFactory.h
 * Author: zisis
 *
 * Created on March 27, 2014, 12:08 AM
 */

#ifndef TEXTUREFACTORY_H
#define	TEXTUREFACTORY_H

#include "../../image/ImageLoaderFactory.h"
#include "Texture.h"
#include <vector>
#include <map>

/**
 * Responsible for loading all textures used by the application
 */
class TextureFactory {
public:
    TextureFactory();
    TextureFactory(const TextureFactory& orig);
    /**
     * Loads into OpenGL all textures defined in "resources/textures/textures.xml".
     * It gets the proper ImageLoader based on the file extention and loads the raw 
     * image data into a TextureImage object. The TextureImage object is then 
     * passed into Texture which creates an OpenGL texture. The generated OpenGL
     * textures are kept into a Map
     */
    void loadTextures();
    /**
     * Given the name of a texture it returns a Texture object.
     * @param name the name of the texture as in "resources/textures/textures.xml"
     * @return an OpenGL texture object
     */
    Texture* getTexture(const string name) const;
    virtual ~TextureFactory();
private:
    std::map<string,Texture*> textures;
    ImageLoaderFactory* imgLoaderFactory;
};

#endif	/* TEXTUREFACTORY_H */

