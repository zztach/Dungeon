/* 
 * File:   Camera.h
 * Author: zisis
 *
 * Created on April 13, 2014, 5:00 PM
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera {
public:
    Camera(const int width, const int height);
    Camera(const Camera& orig);
    
    void moveForward(const float distance);
    void moveBackwards(const float distance);
    void strafeRight(const float distance);
    void strafeLeft(const float distance);
    void rotate(float yAngle);
    
    const glm::mat4 getMatrix();
    float getRotation() const;
    const glm::mat4 getPerpsectiveProjection() const;
    const glm::mat4 getOrthoProjection() const;
    virtual ~Camera();
private:
    glm::vec3       position;
    glm::vec3       viewDirection;
    glm::vec3       strafeDirection;
    glm::mat4       matrix_initial;
    glm::mat4       mv_rot_camera;
    glm::mat4       proj_matrix;
    glm::mat4       ortho_matrix;
    float           rotY;
};

#endif	/* CAMERA_H */

