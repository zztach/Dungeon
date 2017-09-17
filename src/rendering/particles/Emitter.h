/* 
 * File:   Emitter.h
 * Author: zisis
 *
 * Created on April 8, 2014, 9:44 PM
 */

#ifndef EMITTER_H
#define	EMITTER_H

#include "Particle.h"
#include "../textures/Texture.h"
#include <list>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Emitter {
public:
    Emitter(GLuint program);
    Emitter(const Emitter& orig);
    virtual ~Emitter();
    void update(double time, float rotY);
    void setTexture(Texture *texture);
protected :
    void addParticle(float rotY, double time);
    float frand(float start = 0, float end = 0);
private:
	std::list<Particle*> particles;
	Texture	*texture;
	// Attributes
	float	emissionRate;
	float	emissionRadius;

	float	life;
	float	lifeRange;

	float size;
	float sizeRange;

	float saturation;
	float alpha;
	float spread;
	float gravity;

	glm::vec3 position;
	glm::vec3 wind;
	glm::vec3 rotation;

        GLuint program;
};

#endif	/* EMITTER_H */

