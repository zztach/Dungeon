/* 
 * File:   ShaderUniform.h
 * Author: zisis
 *
 * Created on April 13, 2014, 6:57 PM
 */

#ifndef SHADERUNIFORM_H
#define	SHADERUNIFORM_H

#include <glew.h>
#include <map>

class ShaderUniform {
private:
    GLuint program;
    static ShaderUniform* instance;
    std::map<std::string, GLuint> uniforms;
  ShaderUniform(GLuint program) {
        this->program = program;
        uniforms["camera_matrix"] = glGetUniformLocation(program, "camera_matrix");
        uniforms["proj_matrix"] = glGetUniformLocation(program, "proj_matrix");
        uniforms["light_pos"] = glGetUniformLocation(program, "light_pos");
        uniforms["tex"] = glGetUniformLocation(program, "tex");
        uniforms["mv_matrix"] = glGetUniformLocation(program, "mv_matrix");
    }
  
public:
    GLuint get(std::string name) {
        return uniforms.at(name);
    }

    static ShaderUniform* getInstance(GLuint program) {
        static ShaderUniform* instance = new ShaderUniform(program);
        return instance;
    }

};

#endif	/* SHADERUNIFORM_H */

