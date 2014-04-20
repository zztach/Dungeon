#include "Particle.h"

Particle::Particle(int id, float rotY) {
    this->id = id;
    totalLife = 5.0f;
    life = 1.0f;

    color.x = 255;color.y=0;color.z=0;
    alpha = 0.8f;
    size = 0.1f;

    bounciness = 0.9f;
    this->rotY = rotY;
    active = true;
}
  
Particle::~Particle()
{
    glDeleteBuffers(1, &buffer);
    glDeleteVertexArrays(1, &vao);
}

void Particle::bindVAO() 
{
    glGenVertexArrays(1, &vao); // Create our Vertex Array Object  
    glBindVertexArray(vao); // Bind our Vertex Array Object so we can use it  

    static const GLfloat vertex_positions[] = {
        // CW order to get it in front
        -size, -size, 0, 0, 0,
        -size, size, 0, 0, 1,
        size, -size, 0, 1, 0,
        size, size, 0, 1, 1,
    };
    
    // load vertex positions into the buffer, input to vertex attributes 0,3
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertex_positions), vertex_positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);
    
    glBindVertexArray(0);
}

void Particle::render(const GLuint program, const double timeElapsed) {
    
    if (active == false)
        return;

    // number of seconds since our last update
//    float change = (float) (timeElapsed - lastTime) / 10000.0f;
    float change = timeElapsed / 20.0f;
    velocity += acceleration * change;
    position += velocity * change;

    float x = position.x;
    float y = position.y;
    float z = position.z;

    if (position.y < 0.0f) {
        velocity.y = velocity.y * - bounciness;
        position.y = 0.0f;
    }

    const float fadeTime = 0.5f;

    if (totalLife - life < fadeTime) {
        glVertexAttrib4fv(2, glm::value_ptr(glm::vec4(glm::vec3(color), (totalLife - life) / fadeTime * alpha)));
    } else if (life < 1.0f) {
        glVertexAttrib4fv(2, glm::value_ptr(glm::vec4(glm::vec3(color), life * alpha)));
    } else {
        glVertexAttrib4fv(2, glm::value_ptr(glm::vec4(glm::vec3(color), alpha)));
    }

       GLuint mv_location = glGetUniformLocation(program, "mv_matrix");

    glBindVertexArray(vao);
    GLfloat colora[] = {1.0f, 1.0f, 0.0f, 1.0f};
    glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y-1.2f, position.z -35.0f)) 
                          * glm::rotate(glm::mat4(1.0f), -rotY, glm::vec3(0.0f,1.0f, 0.0f));
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    life -= change * 17;

    if (life <= 0.0f) {
        active = false;
    }   
}
