/* 
 * File:   Camera.h
 * Author: zisis
 *
 * Created on April 13, 2014, 5:00 PM
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    Camera(const int width, const int height);
    Camera(const Camera& orig);
    void setPosition(const glm::vec3& position);
    void move(const glm::vec3& offset);
    void rotate(float yAngle);
    const glm::mat4 getMatrix();
    float getRotation() const;
    const glm::mat4 getProjection(bool is3D);
    virtual ~Camera();
private:
    glm::vec3       position;
    glm::mat4       matrix_initial;
    glm::mat4       mv_rot_camera;
    glm::mat4       proj_matrix;
    glm::mat4       ortho_matrix;
    float           rotY;
};

#endif	/* CAMERA_H */

