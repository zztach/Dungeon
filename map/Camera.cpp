/* 
 * File:   Camera.cpp
 * Author: zisis
 * 
 * Created on April 13, 2014, 5:00 PM
 */

#include "Camera.h"

Camera::Camera(const int width, const int height) {
    float aspect = (float) width / (float) height;
    proj_matrix = glm::perspective(45.0f, aspect, 0.1f, 100.0f);
    position = glm::vec3(0.0f);
    matrix_initial = glm::mat4(1.0f);
    rotY = -135.0f;
    ortho_matrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
}

void Camera::setPosition(const glm::vec3& position)
{
    
}

void Camera::move(const glm::vec3& offset)
{
    position = position + offset;
}

void Camera::rotate(float yAngle)
{
    // event.motion.rel*frameTime to limit speed of rotation                
    rotY += yAngle;
    if (rotY > 360)
        rotY -= 360;
    if (rotY < -360)
        rotY += 360;
}

float Camera::getRotation() const 
{
    return rotY;
}

const glm::mat4 Camera::getMatrix()
{
    glm::mat4 mv_rot_camera = glm::rotate(matrix_initial, rotY, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mv_matrix_camera = glm::translate(matrix_initial, glm::vec3(position.x, position.y, 30.0f + position.z));
    return mv_rot_camera * mv_matrix_camera;
}
   
const glm::mat4 Camera::getProjection(bool is3D)
{
    return is3D ? proj_matrix : ortho_matrix;
}
    
    
Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
}

