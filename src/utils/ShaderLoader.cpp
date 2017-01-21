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

    // Read shaders
    std::string vertShaderStr = FileUtil::readFile(vertex_path);
    std::string fragShaderStr = FileUtil::readFile(fragment_path);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // Compile vertex shader
    std::cout << "Compiling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    // Check vertex shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        std::vector<char> vertShaderError((unsigned long) logLength);
        glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
        std::cout << &vertShaderError[0] << std::endl;
    }

    // Compile fragment shader
    std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);


    // Check fragment shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        std::vector<char> fragShaderError((unsigned long) logLength);
        glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
        std::cout << &fragShaderError[0] << std::endl;
    }
    std::cout << "Linking program" << std::endl;
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
    std::cout << "Program OK" << std::endl;
    return program;
}

ShaderLoader::ShaderLoader(const ShaderLoader &orig) {
}

ShaderLoader::~ShaderLoader() {
}

