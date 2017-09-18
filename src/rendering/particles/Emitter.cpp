/* 
 * File:   Emitter.cpp
 * Author: zisis
 * 
 * Created on April 8, 2014, 9:44 PM
 */

#include "Emitter.h"

Emitter::Emitter(GLuint prog) {
    texture = nullptr;
    emissionRate = 5.0f;
    emissionRadius = 0.2f;

    life = 2.0f;
    lifeRange = 0.5f;

    size = 0.4f;
    sizeRange = 0.2f;

    saturation = 0.5f;
    alpha = 0.8f;

    spread = 3.0f;
    gravity = 5.0f;
    wind = glm::vec3(0.0, 0.0, 0.0);
    program = prog;
}

Emitter::~Emitter() {
    for (auto &particle : particles) {
        delete particle;
    }
}

void Emitter::update(double time, float rotY) {
    if (texture == nullptr)
        return;

    // ALWAYS draw all particles, but do not write to depth buffer, 
    // otherwise particles will always be drawn
    glDepthMask(GL_FALSE); 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);  
    glBindTexture(GL_TEXTURE_2D, texture->getTexture());

    auto numEmission = (int)(0.2f * emissionRate);
    for (int i = 0; i < numEmission; i++)
        addParticle(rotY, time);

    for (auto it = particles.begin(); it != particles.end();) {
        Particle *particle = (*it);

        particle->acceleration.y = -gravity;
        particle->acceleration += wind;
        particle->alpha = alpha;
        particle->rotation = rotation;
        particle->rotY = rotY;

        float change = (float)time / 20.0f;
        particle->velocity += particle->acceleration * change;
        particle->position += particle->velocity * change;

        if (particle->position.y < 0.0f) {
            particle->velocity.y = particle->velocity.y * - particle->bounciness;
            particle->position.y = 0.0f;
        }
        float x_offset = 8.0f;
        float y_offset = 1.0f;
        float z_offset = 32.0f;
        glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-x_offset + particle->position.x,
                                                                        particle->position.y - y_offset,
                                                                        particle->position.z - z_offset))
                              * glm::rotate(glm::mat4(1.0f), -rotY, glm::vec3(0.0f,1.0f, 0.0f));

        particle->setMvMatrix(mv_matrix);

//        particle->render(program, time);

        life -= change * 17;
        if (life <= 0.0f) {
            particle->active = false;
        }

        if (!particle->active) {
            delete particle;
            it = particles.erase(it);
        } else
            ++it;
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
}

void Emitter::setTexture(Texture *tex) {
    texture = tex;
}

void Emitter::addParticle(float rotY, double time) {
    auto *particle = new Particle((int) particles.size(), rotY);
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


