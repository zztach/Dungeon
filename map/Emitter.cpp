/* 
 * File:   Emitter.cpp
 * Author: zisis
 * 
 * Created on April 8, 2014, 9:44 PM
 */

#include "Emitter.h"

Emitter::Emitter(GLuint prog) {
    texture = NULL;
    emissionRate = 5.0f;
    emissionRadius = 0.2f;

    life = 2.0f;
    lifeRange = 0.5f;

    size = 0.4f;
    sizeRange = 0.2f;

    saturation = 0.5f;
    alpha = 0.8f;

    spread = 2.0f;
    gravity = 5.0f;
    wind = glm::vec3(0.0, 0.0, 0.0);
    program = prog;
}

Emitter::~Emitter() {
    for (std::list<Particle*>::iterator it = particles.begin(); it != particles.end(); it++) {
        delete (*it);
    }
}

void Emitter::update(double time, float rotY) {
    static float interval = 0;

    if (texture == NULL)     
        return;

    int numEmission = time * 50.0f * emissionRate;
    for (int i = 0; i < numEmission; i++)
        addParticle(rotY);

    // ALWAYS draw all particles
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_TEXTURE_2D);
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture->getTexture());

    for (std::list<Particle*>::iterator it = particles.begin(); it != particles.end();) {
        Particle *particle = (*it);
        particle->acceleration.y = -gravity;
        particle->acceleration += wind;
        particle->alpha = alpha;
        particle->rotation = rotation;
        particle->rotY = rotY;

        particle->render(program, time);

        if (particle->active == false) {
            delete particle;
            it = particles.erase(it);
        } else
            ++it;
    }

   // glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

}

void Emitter::setTexture(Texture *tex) {
    texture = tex;
}

void Emitter::addParticle(float rotY) {
    Particle *particle = new Particle((int) particles.size(), rotY);
    particle->bindVAO();
    float r = frand() * saturation + (1 - saturation);
    float g = frand() * saturation + (1 - saturation);
    float b = frand() * saturation + (1 - saturation);

    particle->color = glm::vec3(r, g, b);
    particle->life = frand(life - lifeRange, life + lifeRange);
    particle->totalLife = particle->life;

    particle->velocity = glm::vec3(frand(-spread, spread), frand(3, 20), frand(-spread, spread));

    particle->acceleration = glm::vec3(0.0f, -gravity, 0.0f);
    particle->size = frand(size - sizeRange, size + sizeRange);

    particle->position.x = frand(-emissionRadius, emissionRadius);
    particle->position.z = frand(-emissionRadius, emissionRadius);

    particles.push_back(particle);

}

float Emitter::frand(float start, float end) {
    float num = (float) rand() / (float) RAND_MAX;
    return (start + (end - start) * num);
}

Emitter::Emitter(const Emitter& orig) {

}


