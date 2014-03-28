/* 
 * File:   TextureFactory.cpp
 * Author: zisis
 * 
 * Created on March 27, 2014, 12:08 AM
 */

#include "TextureFactory.h"

TextureFactory::TextureFactory() {
    imgLoaderFactory = new ImageLoaderFactory();
}

TextureFactory::TextureFactory(const TextureFactory& orig) {
}

TextureFactory::~TextureFactory() {
    delete imgLoaderFactory;
}

void TextureFactory::loadTextures() {
    std::vector<string> textureNames;
    textureNames.push_back("mossy_wall.tga");
    textureNames.push_back("sunflower.tga");

    for (std::vector<string>::iterator it = textureNames.begin(); it != textureNames.end(); ++it) {
        string type = (*it).substr((*it).find_last_of(".")).substr(1);        
        ImageLoader* imgLoader = imgLoaderFactory->getImageLoader(type);
        TextureImage* texImage = imgLoader->load(*it);
        if (texImage != NULL) {
            Texture* texture = new Texture(texImage);
            texture->load();
            textures[(*it)] = texture; 
        } else {
            std::cout << " Problem loading image" << (*it) << std::endl;
        }
        delete texImage;        
        delete imgLoader;
    }
}

Texture* TextureFactory::getTexture(const string name) const
{
    return textures.at(name);
}
