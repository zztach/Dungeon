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
    std::map<std::string, Texture*>::iterator iter;    
    for (iter = textures.begin(); iter != textures.end(); iter++) {
        delete iter->second;
    }
    delete imgLoaderFactory;
}

void TextureFactory::loadTextures() {
    std::vector<string> textureNames;    
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("textures/textures.xml");
    std::cout << "TEXTURES:" << result.description() << std::endl;
    pugi::xpath_node_set nodes = doc.select_nodes("/Textures/texture");
    for (pugi::xpath_node_set::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        pugi::xpath_node node = *it;
        string textureID = node.node().child("id").child_value();
        string textureFile = node.node().child("fileName").child_value();
        
        string type = (textureFile).substr(textureFile.find_last_of(".")).substr(1);
        ImageLoader* imgLoader = imgLoaderFactory->getImageLoader(type);
        TextureImage* texImage = imgLoader->load(textureFile);
        if (texImage != NULL) {
            Texture* texture = new Texture(texImage);
            texture->load();
            textures[textureID] = texture;
            std::cout << "Successfully loaded texture : " << textureFile << std::endl;
        } else {
            std::cout << " Problem loading texture" << textureFile << std::endl;
        }
        delete texImage;
        delete imgLoader;
    }
}

Texture* TextureFactory::getTexture(const string name) const {
    return textures.at(name);
}
