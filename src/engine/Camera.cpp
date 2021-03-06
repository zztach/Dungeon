/* 
 * File:   Camera.cpp
 * Author: zisis
 * 
 * Created on April 13, 2014, 5:00 PM
 */

#include "Camera.h"

Camera::Camera(const int width, const int height) {
    float aspect = (float) width / (float) height;
    proj_matrix = glm::perspective(90.0f, aspect, 0.2f, 30.0f);
    position = glm::vec3(0.0f);
    // openGL is right-handed, -z goes into the screen
    viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    strafeDirection = glm::vec3(1.0f, 0.0f, 0.0f);
    matrix_initial = glm::mat4(1.0f);
    rotY = 0.0f;
    ortho_matrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
}

void Camera::moveForward(const float distance)
{
    // when we move forward we actually move the rest of the world backwards, this
    // explains the minus in front of viewDirection
    position += -viewDirection * distance;
}

void Camera::moveBackwards(const float distance)
{
    position += viewDirection * distance;
}

void Camera::strafeRight(const float distance)
{
    position += -strafeDirection * distance;
}

void Camera::strafeLeft(const float distance)
{
    position += strafeDirection * distance;
}
    
void Camera::rotate(float yAngle)
{
    // event.motion.rel*frameTime to limit speed of rotation                
    rotY += yAngle;
    if (rotY > 360)
        rotY -= 360;
    if (rotY < -360)
        rotY += 360;
    
    double temp = rotY / 180.0f * M_PI;
    // rotY rotates around the Y-axis. Right-rotation gives us positive values in rotY, left-rotation
    // gives negatives. The positive angles start from -Z and go to +X, this explains that 
    // sin(temp) gives us X-axis values and cos(temp) Z-axis values
    viewDirection = glm::vec3(sin(temp), 0.0f, -cos(temp));        
    strafeDirection = glm::vec3(cos(temp), 0.0f, sin(temp));
}

float Camera::getRotation() const 
{
    return rotY;
}

void Camera::process(map<char,KeyState*> keysPressed, MouseState& mouseState, double frameTime)
{
//    float velocity = 625.0f;
    float distance = 2.0f;//velocity * frameTime;
    
    //continuous-response keys
    if (keysPressed[SDLK_w] || 
         keysPressed[SDLK_a] || 
         keysPressed[SDLK_s] || 
         keysPressed[SDLK_d]) 
    {
        if (keysPressed[SDLK_w]->pressed) {
            this->moveForward(distance);
            keysPressed[SDLK_w]->pressed = false;
        }
        if (keysPressed[SDLK_s]->pressed) {
            this->moveBackwards(distance);
            keysPressed[SDLK_s]->pressed = false;
        }
        if (keysPressed[SDLK_a]->pressed) {
            this->strafeLeft(distance);
            keysPressed[SDLK_a]->pressed = false;
        }
        if (keysPressed[SDLK_d]->pressed) {
            this->strafeRight(distance);
            keysPressed[SDLK_d]->pressed = false;
        }
        if (keysPressed[SDLK_q]->pressed) {
            this->rotate(-90.0f);
            keysPressed[SDLK_q]->pressed = false;
        }
        if (keysPressed[SDLK_e]->pressed) {
            this->rotate(90.0f);
            keysPressed[SDLK_e]->pressed = false;
        }
    }
}

const glm::mat4 Camera::getMatrix()
{
    glm::mat4 mv_rot_camera = glm::rotate(matrix_initial, rotY, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mv_matrix_camera = glm::translate(matrix_initial, glm::vec3(position.x, position.y, 30.0f + position.z));
    return mv_rot_camera * mv_matrix_camera;
}
   
const glm::mat4 Camera::getPerpsectiveProjection() const
{
    return proj_matrix;
}

const glm::mat4 Camera::getOrthoProjection() const
{
    return ortho_matrix;
}
    
glm::vec3 Camera::getPosition() const
{
    return position;
}

Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
}

