#include "Particle.h"

Particle::Particle(int id) {
    this->id = id;
    totalLife = 1.0f;
    life = 1.0f;

    color.x = 255;color.y=0;color.z=0;
    alpha = 1.0f;
    size = 10.0f;

    bounciness = 0.9f;

    active = true;

    lastTime = -1;
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
    GLuint mv_location = glGetUniformLocation(program, "mv_matrix");

    glBindVertexArray(vao);
    GLfloat colora[] = {1.0f, 1.0f, 0.0f, 1.0f};
    glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.1, -30.0));
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
    glVertexAttrib4fv(2, colora);
    
    
    if (active == false)
        return;

    if (lastTime == -1)
        lastTime = timeElapsed;

    // number of seconds since our last update
    float change = (float) (timeElapsed - lastTime) / 10000.0f;

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

    if (totalLife - life < fadeTime)
        glColor4f(color.x, color.y, color.z, (totalLife - life) / fadeTime * alpha);
    else if (life < 1.0f)
        glColor4f(color.x, color.y, color.z, life * alpha);
    else
        glColor4f(color.x, color.y, color.z, alpha);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    life -= change * 17;

    if (life <= 0.0f) {
        active = false;
    }

    lastTime = timeElapsed;       
}
