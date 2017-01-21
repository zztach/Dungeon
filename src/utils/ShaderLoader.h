/* 
 * File:   ShaderLoader.h
 * Author: zisis
 *
 * Created on April 13, 2014, 5:49 PM
 */

#ifndef SHADERLOADER_H
#define	SHADERLOADER_H

#include <iostream>
#include <string>
#include <glew.h>
#include <vector>
#include "FileUtil.h"

class ShaderLoader {
public:
    static GLuint load(const char *vertex_path, const char *fragment_path);
    ~ShaderLoader();
private:
    ShaderLoader();
    ShaderLoader(const ShaderLoader& orig);

    static void compile(GLuint shaderId, const char *&shaderSrc, GLint &result, int &logLength);
};

#endif	/* SHADERLOADER_H */

