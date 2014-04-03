/* 
 * File:   Particle.h
 * Author: zisis
 *
 * Created on March 29, 2014, 12:24 PM
 */

#ifndef PARTICLE_H
#define	PARTICLE_H

#include "IDrawable.h"

class Particle : public IDrawable {
public:

    Particle(int id);
    void update(long time);
    // IDrawable        
    void bindVAO();
    void render(const GLuint program, const double timeElapsed);
public:
    long lastTime;
    int id;

    glm::vec3 color;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 rotation;

    float totalLife;
    float life;

    float alpha;
    float size;

    float bounciness;
    bool active;
private :
    GLuint vao;
    GLuint buffer;       
};
#endif	/* PARTICLE_H */

