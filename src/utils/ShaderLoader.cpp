/* 
 * File:   ShaderLoader.cpp
 * Author: zisis
 * 
 * Created on April 13, 2014, 5:49 PM
 */

#include "ShaderLoader.h"

ShaderLoader::ShaderLoader() {
}

GLuint ShaderLoader::load(const char *vertex_path, const char *fragment_path) {
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertShaderStr = FileUtil::readFile(vertex_path);
    std::string fragShaderStr = FileUtil::readFile(fragment_path);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // Compile vertex shader
    std::cout << "Compiling vertex shader." << std::endl;
    compile(vertShader, vertShaderSrc, result, logLength);

    // Compile fragment shader
    std::cout << "Compiling fragment shader." << std::endl;
    compile(fragShader, fragShaderSrc, result, logLength);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError((unsigned long) ((logLength > 1) ? logLength : 1));
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    std::cout << "Shaders successfully attached into GLSL Program : " << program << std::endl;
    return program;
}

void ShaderLoader::compile(GLuint shaderId, const char *&shaderSrc, GLint &result, int &logLength) {
    glShaderSource(shaderId, 1, &shaderSrc, NULL);
    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        std::vector<char> fragShaderError((unsigned long) logLength);
        glGetShaderInfoLog(shaderId, logLength, NULL, &fragShaderError[0]);
        std::cout << &fragShaderError[0] << std::endl;
    }
}

ShaderLoader::ShaderLoader(const ShaderLoader &orig) {
}

ShaderLoader::~ShaderLoader() {
}

